#version 450
#extension GL_EXT_nonuniform_qualifier : enable

layout(set = 1, binding = 0) uniform sampler2D textures[];

layout(binding = 0) uniform CameraUBO {
    mat4 view; mat4 proj; mat4 viewProj;
    vec3 cameraPos; vec3 ambientColor; float ambientIntensity;
    uint pointLightCount; uint directionalLightCount;
} camera;

// ─── Структуры источников света (должны совпадать с C++!) ───
struct PointLight {
    vec3 pos;       // 12 bytes
    float _pad1;    // 4 bytes padding (alignas(16) для Position)
    vec3 color;     // 12 bytes
    float _pad2;    // 4 bytes padding (alignas(16) для ColorRGB)
    float intensity;// 4 bytes
    float radius;   // 4 bytes
    // Итого: 40 bytes + 8 bytes padding до кратности 16 = 48 bytes в массиве
};

struct DirectionalLight {
    vec3 direction; // offset 0
    float _pad1;    // offset 12 (padding для выравнивания следующего vec3)
    vec3 color;     // offset 16
    float intensity;// offset 28
};

// ─── SSBO для источников света ───
layout(std430, binding = 2) readonly buffer PointLightsSSBO {
    PointLight lights[];
} pointLights;

layout(std430, binding = 3) readonly buffer DirectionalLightsSSBO {
    DirectionalLight lights[];
} directionalLights;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in vec3 fragPos;
layout(location = 4) in vec4 fragTang;
layout(location = 5) in flat uint fragAlbedoTextureIndex;
layout(location = 6) in flat uint fragNormalTextureIndex;
layout(location = 7) in flat uint fragMetallicTextureIndex;
layout(location = 8) in flat uint fragRoughnessTextureIndex;
layout(location = 9) in flat uint fragAmbientTextureIndex;
layout(location = 10) in flat uint fragEmissionTextureIndex;
layout(location = 11) in flat uint fragHeightTextureIndex;
layout(location = 12) in flat float fragMetallicScalar;
layout(location = 13) in flat float fragRoughnessScalar;
layout(location = 14) in flat float fragAmbientScalar;
layout(location = 15) in flat float fragEmissionScalar;
layout(location = 16) in flat float fragHeightScalar;

layout(location = 0) out vec4 outColor;

//<MATH
// --- Constants ---
const float PI = 3.14159265359;

// --- 1. Normal Distribution Function (GGX / Trowbridge-Reitz) ---
// Определяет размер блика. Чем меньше roughness, тем острее пик.
float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a      = roughness * roughness;
    float a2     = a * a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

// --- 2. Geometry Function (Schlick-GGX) ---
// Учитывает само-затенение микрограней.
float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0; // Прямое преобразование для прямых источников света

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

// --- Geometry Function (Smith method) ---
// Комбинирует затенение от источника света (L) и от взгляда (V)
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1  = GeometrySchlickGGX(NdotV, roughness);
    float ggx2  = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

// --- 3. Fresnel Effect (Schlick approximation) ---
// Определяет соотношение отраженного и преломленного света.
// F0 - это отражательная способность при нормальном падении (perpendicular incidence).
vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
//>MATH


struct LightResult {
    vec3 color;
};

LightResult calculateLight(
    vec3 L,
    vec3 lightColor, 
    float lightIntensity, 
    float attenuation,
    vec3 N, vec3 V, 
    vec3 albedo, 
    float metallic, 
    float roughness, 
    vec3 F0) {
    LightResult result;
    result.color = vec3(0.0);

    vec3 H = normalize(V + L);
    
    // --- Cook-Torrance BRDF components ---
    float NDF = DistributionGGX(N, H, roughness);   
    float G   = GeometrySmith(N, V, L, roughness);      
    vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
        
    // Specular calculation
    vec3 numerator    = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
    vec3 specular     = numerator / denominator;
        
    // Energy conservation (kS + kD = 1)
    vec3 kS = F;
    vec3 kD = (vec3(1.0) - kS);
    kD *= 1.0 - metallic;
    
    // Lambertian diffuse + Specular
    float NdotL = max(dot(N, L), 0.0);
    
    result.color = (kD * albedo / PI + specular) * lightColor * lightIntensity * attenuation * NdotL;
    
    return result;
}


vec4 getTexture(uint id, vec2 uv, float scalar) {
    vec4 r = texture(textures[nonuniformEXT(id)], uv);
	r.rgb *= scalar;
	return r;
}

vec4 getMraoh(uint idM, float scalarM, uint idR, float scalarR, uint idAO, float scalarAo, uint idH, float scalarH, vec2 uv) {
	vec4 result;
	result.r = getTexture(idM, uv, scalarM).r;
	result.g = getTexture(idR, uv, scalarR).g;
	result.b = getTexture(idAO, uv, scalarAo).b;
	result.a = getTexture(idH, uv, scalarH).a;
	return result;
}

vec3 getNormal(uint id, vec2 uv, vec3 fragNormal, vec4 fragTangent) {
    vec3 normalMap = getTexture(id, uv, 2.0).rgb - 1.0;

    vec3 T = normalize(fragTangent.xyz);
    vec3 N = normalize(fragNormal);

    T = normalize(T - dot(T, N) * N);

    vec3 B = cross(N, T) * fragTangent.w;
    
    mat3 TBN = mat3(T, B, N);
    
    return normalize(TBN * normalMap);
}


vec3 tonemapACES(vec3 x) {
    // Approximation of ACES filmic tone mapping
    float a = 2.51f;
    float b = 0.03f;
    float c = 2.43f;
    float d = 0.59f;
    float e = 0.14f;
    return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}


void main() {
    // ========================================================================
    // 1. ПОДГОТОВКА ГЕОМЕТРИИ И TBN-МАТРИЦЫ
    // ========================================================================
    
    // Базовые векторы в мировом пространстве
    vec3 N_world = normalize(fragNormal);
    vec3 V_world = normalize(camera.cameraPos - fragPos);
    
    // Строим касательный базис (TBN) для нормал-маппинга и POM
    vec3 T = normalize(fragTang.xyz);
    vec3 B = cross(N_world, T) * fragTang.w; // handedness из MikkTSpace
    mat3 TBN = mat3(T, B, N_world);
    
    // Вектор взгляда в касательном пространстве (нужен для POM)
    vec3 viewDirTangent = normalize(TBN * V_world);
    
    // ========================================================================
    // 2. PARALLAX OCCLUSION MAPPING (вычисляем ДО сэмплинга текстур!)
    // ========================================================================
    
    vec2 pomUV = fragTexCoord; // По умолчанию — исходные UV
    
    // Применяем POM только если есть карта высот и масштаб > 0
    if (fragHeightTextureIndex > 0u && fragHeightScalar > 0.001) {
        // === Ray Marching (грубый поиск) ===
        float minLayers = 8.0;
        float maxLayers = 32.0;
        // Больше слоёв под острыми углами взгляда
        float numLayers = mix(maxLayers, minLayers, abs(viewDirTangent.z));
        float layerDepth = 1.0 / numLayers;
        
        // Шаг смещения UV на один слой
        vec2 deltaUV = viewDirTangent.xy * fragHeightScalar / (viewDirTangent.z * numLayers);
        
        vec2 currentUV = fragTexCoord;
        float currentDepth = 0.0;
        
        // Идём по лучу, пока не найдём пересечение с поверхностью
        while (currentDepth < 1.0) {
            currentDepth += layerDepth;
            currentUV -= deltaUV;
            
            float currentHeight = texture(textures[nonuniformEXT(fragHeightTextureIndex)], currentUV).a;
            if (currentDepth >= currentHeight) break;
        }
        
        // === Binary Search (уточнение, 2 итерации) ===
        vec2 prevUV = currentUV + deltaUV;
        for (int i = 0; i < 2; i++) {
            float afterH = texture(textures[nonuniformEXT(fragHeightTextureIndex)], currentUV).a;
            float beforeH = texture(textures[nonuniformEXT(fragHeightTextureIndex)], prevUV).a;
            
            float weight = (currentDepth - afterH) / ((currentDepth - afterH) - (currentDepth - layerDepth - beforeH));
            weight = clamp(weight, 0.0, 1.0);
            
            vec2 newUV = mix(prevUV, currentUV, weight);
            prevUV = currentUV;
            currentUV = newUV;
            layerDepth *= 0.5;
        }
        
        pomUV = currentUV;
        
        // === Смягчение на силуэте (против артефактов) ===
        float silhouetteFade = smoothstep(0.1, 0.3, abs(dot(N_world, V_world)));
        pomUV = mix(fragTexCoord, pomUV, silhouetteFade);
    }
    
    // ========================================================================
    // 3. СЭМПЛИНГ ТЕКСТУР (все по pomUV!)
    // ========================================================================
    
    // Albedo
    vec4 albedoTex = getTexture(fragAlbedoTextureIndex, pomUV, 1.0);
    vec3 albedo = albedoTex.rgb;
    
    // MRAO: Metallic(R), Roughness(G), AO(B), Height(A)
    vec4 mraoh = getMraoh(
        fragMetallicTextureIndex, fragMetallicScalar,
        fragRoughnessTextureIndex, fragRoughnessScalar,
        fragAmbientTextureIndex, fragAmbientScalar,
        fragHeightTextureIndex, fragHeightScalar,
        pomUV
    );
    float metallic = mraoh.r;
    float roughness = mraoh.g;
    float ao = mraoh.b;
    
    // Normal map (обязательно по pomUV!)
    vec3 normalTangent = getNormal(fragNormalTextureIndex, pomUV, fragNormal, fragTang);
    vec3 N = normalize(normalTangent); // Обновляем нормаль после POM
    
    // Emission (опционально)
    vec3 emission = vec3(0.0);
    if (fragEmissionTextureIndex > 0u) {
        emission = getTexture(fragEmissionTextureIndex, pomUV, fragEmissionScalar).rgb;
    }
    
    // ========================================================================
    // 4. PBR: ПОДГОТОВКА МАТЕРИАЛА
    // ========================================================================
    
    // F0: диэлектрики (0.04) или металлы (albedo)
    vec3 F0 = mix(vec3(0.04), albedo, metallic);
    
    // Вектор взгляда (уже в мировом, но для BRDF можно использовать и в тангентном)
    vec3 V = normalize(V_world);

    vec3 Lo = vec3(0.0); // Accumulated light
    
    
    // ========================================================================
    // 5. ОСВЕЩЕНИЕ: Directional Lights
    // ========================================================================
    for (uint i = 0; i < camera.directionalLightCount; ++i) {
        DirectionalLight light = directionalLights.lights[i];
        
        // direction: КУДА светит → инвертируем для вектора К источнику
        vec3 L = normalize(-light.direction);
        
        LightResult res = calculateLight(
            L, light.color, light.intensity, 1.0,
            N, V, albedo, metallic, roughness, F0
        );
        Lo += res.color;
    }
    
    float maxLightInfluence = 0.0; // Накопитель для амбиента

    // ========================================================================
    // 6. ОСВЕЩЕНИЕ: Point Lights
    // ========================================================================
    for (uint i = 0; i < camera.pointLightCount; ++i) {
        PointLight light = pointLights.lights[i];
        
        vec3 lightPos = light.pos;
        vec3 L = normalize(lightPos - fragPos);
        float dist = length(lightPos - fragPos);
        
        // Физическое затухание 
        float attenuation = 1.0 / (dist * dist + 0.01);

        float radiusFalloff = smoothstep(light.radius, light.radius * 0.8, dist);
        attenuation *= radiusFalloff;
        
        // Накапливаем МАКСИМАЛЬНОЕ влияние света для амбиента
        // Учитываем и расстояние, и интенсивность источника
        float influence = attenuation * light.intensity;
        maxLightInfluence = max(maxLightInfluence, influence);

        LightResult res = calculateLight(
            L, light.color, light.intensity, attenuation,
            N, V, albedo, metallic, roughness, F0
        );
        Lo += res.color;
    }
    
    // ========================================================================
    // 7. AMBIENT + EMISSION + ФИНАЛЬНАЯ СБОРКА
    // ========================================================================
    
    float ambientVisibility = clamp(maxLightInfluence * 10.0, 0.03, 1.0);

    if (camera.directionalLightCount > 0u) {
        ambientVisibility = 1.0; // DirLight = глобальный свет, амбиент не затухает
    }

    vec3 ambient = camera.ambientColor * camera.ambientIntensity * albedo * ao * ambientVisibility;
    
    // Суммируем: окружение + прямое освещение + эмиссия
    // Эмиссия добавляется ДО тонмаппинга, чтобы яркие источники "пересвечивали" корректно
    vec3 color = ambient + Lo + emission;
    
    // Tonemapping: ACES для киношного контраста
    color = tonemapACES(color);
    
    // Gamma correction: конвертация в sRGB для монитора
    color = pow(color, vec3(1.0 / 2.2));
    
    // Вывод
    //outColor = vec4(color, 1.0);
    outColor = vec4(color , 1.0);
}