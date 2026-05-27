#include <memory>
#include "textureStorage.h"
#include "textureLoader.h"

using BaseStorage = prism::PGC::L1::Storage < prism::TextureId, prism::PGC::Texture, prism::PGC::L2::TextureLoader, prism::PGC::L1::TextureStorage> ;

void prism::PGC::L1::TextureStorage::createImpl() {
    BaseStorage::createImpl();
    data.push_back(PGC::Texture{});
}

prism::TextureId prism::PGC::L1::TextureStorage::loadImpl(Texture textureData) {
    if (textureData.image == VK_NULL_HANDLE) {
        return INVALID_TEXTURE_ID;
    }

    uint32_t index = getNextAvailableIndex();
    textureData.bindlessIndex = index;
    pathToId.emplace(getPathForId(textureData.path, textureData.type), index);
    if (index >= data.size()) {
        data.push_back(textureData);
    } else {
        data[index] = textureData;
    }

    return index;
}

std::filesystem::path prism::PGC::L1::TextureStorage::getPathForId(std::filesystem::path path, TextureType type)
{
    std::string suffix = "@" + std::to_string(static_cast<int>(getFormatFromType(type)));
    path += suffix;
    return path;
}

void prism::PGC::L1::TextureStorage::unloadImpl(TextureId id)
{
    if (id == INVALID_TEXTURE_ID || id >= data.size()) return ;  
    
    auto& tex = data[id];
    if (tex.image != VK_NULL_HANDLE) {
        auto key = getPathForId(tex.path, tex.type);
        pathToId.erase(key);
        loader->cleanup(&tex);
    }

    freeIndices.push_back(id);
}

void prism::PGC::L1::TextureStorage::cleanupImpl()
{
    
    if (this->context->textureDescriptorSetLayout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(this->context->device, this->context->textureDescriptorSetLayout, nullptr);
        this->context->textureDescriptorSetLayout = VK_NULL_HANDLE;
    }

}

void prism::PGC::L1::TextureStorage::updateImpl()
{
    if (this->context->textureDescriptorSet == VK_NULL_HANDLE) return;

    std::vector<std::pair<uint32_t, VkDescriptorImageInfo>> validTextures;
    for (uint32_t i = INVALID_TEXTURE_ID + 1; i < data.size(); i++) {
        if (data[i].image != VK_NULL_HANDLE) {
            VkDescriptorImageInfo imageInfo{};
            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            imageInfo.imageView = data[i].imageView;
            imageInfo.sampler = data[i].sampler;
            validTextures.emplace_back(i, imageInfo);
        }
    }

    if (validTextures.empty()) return;

    std::vector<VkWriteDescriptorSet> descriptorWrites;
    descriptorWrites.reserve(validTextures.size());

    for (const auto& [index, imageInfo] : validTextures) {
        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = this->context->textureDescriptorSet;
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = index;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pImageInfo = &imageInfo;

        descriptorWrites.push_back(descriptorWrite);
    }


    vkUpdateDescriptorSets(this->context->device,
        static_cast<uint32_t>(descriptorWrites.size()),
        descriptorWrites.data(), 0, nullptr);
}

uint32_t prism::PGC::L1::TextureStorage::getId(TextureId id)
{
    return id;
}

void prism::PGC::L1::TextureStorage::clearImpl()
{
    for (uint32_t i = INVALID_TEXTURE_ID + 1; i < data.size(); i++) {
        auto& texture = data[i];
        if (texture.image != VK_NULL_HANDLE) {
            loader->cleanup(&texture);
        }
    }
}
