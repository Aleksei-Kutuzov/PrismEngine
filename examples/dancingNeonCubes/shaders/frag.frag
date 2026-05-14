#version 450
#extension GL_EXT_nonuniform_qualifier : enable

layout(set = 1, binding = 0) uniform sampler2D textures[];

layout(binding = 0) uniform CameraUBO {
    mat4 view;
    mat4 proj;
    mat4 viewProj;
    vec3 cameraPos;
    vec3 ambientColor;
    float ambientIntensity;
    uint pointLightCount;
    uint directionalLightCount;
} camera;

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
    float radius;
};

layout(std430, binding = 2) readonly buffer PointLightsSSBO {
    PointLight lights[];
} pointLights;

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
};

layout(std430, binding = 3) readonly buffer DirectionalLightsSSBO {
    DirectionalLight lights[];
} directionalLights;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in vec3 fragPos;

layout(location = 4) in flat uint fragAlbedoTextureIndex;
layout(location = 5) in flat uint fragNormalTextureIndex;
layout(location = 6) in flat uint fragMetallicTextureIndex;
layout(location = 7) in flat uint fragRoughnessTextureIndex;
layout(location = 8) in flat uint fragAmbientTextureIndex;
layout(location = 9) in flat uint fragEmissionTextureIndex;
layout(location = 10) in flat uint fragHeightTextureIndex;

layout(location = 11) in flat float fragMetallicScalar;
layout(location = 12) in flat float fragRoughnessScalar;
layout(location = 13) in flat float fragEmissionScalar;
layout(location = 14) in flat float fragHeightScalar;


layout(location = 0) out vec4 outColor;

vec4 sampleTexture(uint textureIndex, vec2 uv, vec3 fc) {
    if (textureIndex == 0u) {
        return vec4(fc, 1.0);
    }

    return texture(textures[nonuniformEXT(textureIndex)], uv);
}

void main() {
    vec4 albedo = sampleTexture(fragAlbedoTextureIndex, fragTexCoord, fragColor);

    outColor = albedo.rgba;
}