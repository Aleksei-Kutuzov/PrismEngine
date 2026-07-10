#include "textureStorage.h"
#include "logger.h"

void prism::PGC::L1::TextureStorage::createImpl() {
	loader = new L2::TextureLoader(context, settings);
	data.push_back(loader->loadColor(assets::TextureColor{ {251, 126, 253}, TextureType::ALBEDO }));
}

prism::TextureId prism::PGC::L1::TextureStorage::load(assets::AssetSpec assetSpec) {
	for (size_t i = 0; i < data.size(); i++)
	{
		if (data[i].assetSpec == assetSpec) return i;
	}
	
	Texture texture = std::visit(prism::assets::overloaded{ 
		[this](assets::TexturePath i) { return loader->loadTexture(i); },
		[this](assets::TextureColor f) { return loader->loadColor(f); },
		[](auto& bad) -> Texture {throw std::runtime_error("Unexpected texture asset type");}
	}, assetSpec);

	auto id = pool.newId();

	if (id + 1 > data.size()) data.push_back(std::move(texture)); 
	else data[id] = std::move(texture);
	isActual = false;
	return id;
}

prism::PGC::Texture& prism::PGC::L1::TextureStorage::getData(TextureId id) {
	if (id != INVALID_TEXTURE_ID) {
		try {
			return data.at(id);
		}
		catch (const std::out_of_range& e) {
			 logger::logError(logger::Error::RUNTIME_ERROR, std::string(e.what()));
		}
	}
}

void prism::PGC::L1::TextureStorage::unload(TextureId id) {
	loader->cleanup(&getData(id));
	pool.delId(id);
};


void prism::PGC::L1::TextureStorage::update() {
	if (isActual) return ;

	if (this->context->textureDescriptorSet == VK_NULL_HANDLE) return;

	std::vector<std::pair<uint32_t, VkDescriptorImageInfo>> validTextures;
	for (uint32_t i = 0; i < data.size(); i++) {
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
};

void prism::PGC::L1::TextureStorage::clear() {
	for (uint32_t i = INVALID_TEXTURE_ID + 1; i < data.size(); i++) {
		auto& texture = data[i];
		if (texture.image != VK_NULL_HANDLE) {
			loader->cleanup(&texture);
		}
	}
};

void prism::PGC::L1::TextureStorage::cleanupImpl() {
	if (this->context->textureDescriptorSetLayout != VK_NULL_HANDLE) {
		vkDestroyDescriptorSetLayout(this->context->device, this->context->textureDescriptorSetLayout, nullptr);
		this->context->textureDescriptorSetLayout = VK_NULL_HANDLE;
	}
};