#version 450

layout(binding = 0) uniform CameraUBO {
    mat4 view; mat4 proj; mat4 viewProj;
    vec3 cameraPos; vec3 ambientColor; float ambientIntensity;
    uint pointLightCount; uint directionalLightCount;
} camera;

struct ObjectData {
    mat4 model; mat4 normals;
    uint albedoTextureIndex, normalTextureIndex, metallicTextureIndex;
    uint roughnessTextureIndex, ambientTextureIndex, emissionTextureIndex, heightTextureIndex;
    float metallicScalar, roughnessScalar, emissionScalar, heightScalar;
};

layout(std430, binding = 1) readonly buffer ObjectSSBO { ObjectData objects[]; } ssbo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;
layout(location = 4) in vec4 inTang;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;
layout(location = 3) out vec3 fragPos;
layout(location = 4) out vec4 fragTang;
layout(location = 5) out flat uint fragAlbedoTextureIndex;
layout(location = 6) out flat uint fragNormalTextureIndex;
layout(location = 7) out flat uint fragMetallicTextureIndex;
layout(location = 8) out flat uint fragRoughnessTextureIndex;
layout(location = 9) out flat uint fragAmbientTextureIndex;
layout(location = 10) out flat uint fragEmissionTextureIndex;
layout(location = 11) out flat uint fragHeightTextureIndex;
layout(location = 12) out flat float fragMetallicScalar;
layout(location = 13) out flat float fragRoughnessScalar;
layout(location = 14) out flat float fragEmissionScalar;
layout(location = 15) out flat float fragHeightScalar;

void main() {
    ObjectData object = ssbo.objects[gl_InstanceIndex];
    vec4 worldPos = object.model * vec4(inPosition, 1.0);
    gl_Position = camera.viewProj * worldPos;

    fragColor = inColor;
    fragTexCoord = inTexCoord;
    fragAlbedoTextureIndex = object.albedoTextureIndex;
    fragNormalTextureIndex = object.normalTextureIndex;
    fragMetallicTextureIndex = object.metallicTextureIndex;
    fragRoughnessTextureIndex = object.roughnessTextureIndex;
    fragAmbientTextureIndex = object.ambientTextureIndex;
    fragEmissionTextureIndex = object.emissionTextureIndex;
    fragHeightTextureIndex = object.heightTextureIndex;
    fragMetallicScalar = object.metallicScalar;
    fragRoughnessScalar = object.roughnessScalar;
    fragEmissionScalar = object.emissionScalar;
    fragHeightScalar = object.heightScalar;
    fragNormal = mat3(object.normals) * inNormal;
    fragPos = worldPos.xyz;
    fragTang = inTang;

#ifdef DEBUG_VERTEX_COLOR
    // Пример отладки: принудительная перекраска для проверки работы вершинного шейдера
    fragColor = vec3(0.0, 1.0, 0.0); 
#endif
}