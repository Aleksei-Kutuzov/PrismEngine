#pragma once


class PipelineBuilder {
public:
    PipelineBuilder();
    PipelineBuilder(PipelineComponent pipeline);
    PipelineBuilder(PipelinePreset pipeline);
    PipelineShaderStagesBuilder& beginShaderStages();
    PipelineInputAssemblyBuilder& beginInputAssembly();
    PipelineTessellationBuilder& beginTessellation();
    PipelineViewportBuilder& beginViewport();
    PipelineRasterizationBuilder& beginRasterization();
    PipelineMultisampleBuilder& beginMultisample();
    PipelineDepthStencilBuilder& beginDepthStencil();
    PipelineColorBlendBuilder& beginColorBlend();

    PipelineComponent complete();
};

class PipelineShaderStagesBuilder {
    PipelineShaderStagesBuilder& count(uint32_t count);
    PipelineShaderStagesBuilder& shader(uint32_t index, StageType type, AssetSpec assetSpec);
    PipelineShaderStagesBuilder& entryPoint(uint32_t index, const char* entryPoint);

    PipelineShaderStagesBuilder& specializationConstantCount(uint32_t index, uint32_t size);
    PipelineShaderStagesBuilder& specializationConstantInfo(uint32_t index, uint32_t constantIndex, uint32_t constantID, uint32_t offset, uint32_t size);
    PipelineShaderStagesBuilder& specializationConstantData(uint32_t index, uint32_t constantIndex, const void* data, size_t size);

    PipelineBuilder& end();
};

class PipelineInputAssemblyBuilder {
    PipelineInputAssemblyBuilder& topology(PrimitiveTopology topology);
    PipelineInputAssemblyBuilder& primitiveRestart(bool enable);

    PipelineBuilder& end();
};

class PipelineTessellationBuilder {
    PipelineTessellationBuilder& patchControlPoints(uint32_t count);

    PipelineBuilder& end();
};

class PipelineViewportBuilder {
    PipelineViewportBuilder& count(uint32_t count);
    PipelineViewportBuilder& viewport(uint32_t viewportIndex, float x, float y, float width, float height, float minDepth, float maxDepth);
    PipelineViewportBuilder& scissor(uint32_t viewportIndex, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    PipelineBuilder& end();
};

class PipelineRasterizationBuilder {
    PipelineRasterizationBuilder& depthClamp(bool enable);
    PipelineRasterizationBuilder& rasterizerDiscard(bool enable);
    PipelineRasterizationBuilder& polygonMode(PolygonMode mode);
    PipelineRasterizationBuilder& cullMode(CullMode mode);
    PipelineRasterizationBuilder& frontFace(FrontFace frontFace);
    PipelineRasterizationBuilder& depthBias(bool enable);
    PipelineRasterizationBuilder& depthBiasConstantFactor(float factor);
    PipelineRasterizationBuilder& depthBiasClamp(float clamp);
    PipelineRasterizationBuilder& depthBiasSlopeFactor(float factor);
    PipelineRasterizationBuilder& lineWidth(float width);

    PipelineBuilder& end();
};


class PipelineMultisampleBuilder {
    PipelineMultisampleBuilder& sampleShading(bool enable);
    PipelineMultisampleBuilder& rasterizationSamples(SampleCount count);
    PipelineMultisampleBuilder& minSampleShading(float value);
    PipelineMultisampleBuilder& alphaToCoverage(bool enable);
    PipelineMultisampleBuilder& alphaToOne(bool enable);

    PipelineBuilder& end();
};

class PipelineDepthStencilBuilder {
    PipelineDepthStencilBuilder& depthTest(bool enable);
    PipelineDepthStencilBuilder& depthWrite(bool enable);
    PipelineDepthStencilBuilder& depthCompareOp(CompareOp CompareOp);
    PipelineDepthStencilBuilder& depthBoundsTest(bool enable);
    PipelineDepthStencilBuilder& minDepthBounds(float value);
    PipelineDepthStencilBuilder& maxDepthBounds(float value);
    PipelineDepthStencilBuilder& stencilTest(bool enable);
    PipelineDepthStencilBuilder& stencilFront(StencilOp failOp, StencilOp passOp, StencilOp depthFailOp, CompareOp compareOp);
    PipelineDepthStencilBuilder& stencilFrontMasks(uint32_t  compareMask, uint32_t writeMask, uint32_t reference);
    PipelineDepthStencilBuilder& stencilBack(StencilOp failOp, StencilOp passOp, StencilOp depthFailOp, CompareOp compareOp);
    PipelineDepthStencilBuilder& stencilBackMasks(uint32_t  compareMask, uint32_t writeMask, uint32_t reference);

    PipelineBuilder& end();
};

class PipelineColorBlendBuilder {
    PipelineColorBlendBuilder& logicOpEnable(bool enable);
    PipelineColorBlendBuilder& logicOp(LogicOp logicOp);
    PipelineColorBlendBuilder& blending(bool enable);
    PipelineColorBlendBuilder& blendingScrColorFactor(BlendFactor srcColorFactor);
    PipelineColorBlendBuilder& blendingDstColorFactor(BlendFactor dstColorFactor);
    PipelineColorBlendBuilder& blendingColorOp(BlendOp colorOp);
    PipelineColorBlendBuilder& blendingSrcAlphaFactor(BlendFactor srcAlphaFactor);
    PipelineColorBlendBuilder& blendingDstAlphaFactor(BlendFactor dstAlphaFactor);
    PipelineColorBlendBuilder& blendingAlphaOp(BlendOp alphaOp);
    PipelineColorBlendBuilder& blendingColorWriteMask(ColorComponent colorWriteMask);

    PipelineBuilder& end();
};