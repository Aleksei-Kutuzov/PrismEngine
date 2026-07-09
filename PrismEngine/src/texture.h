#pragma once
#include <filesystem>
#include "vulkan/vulkan.h"
#include "assetSpec.h"


namespace prism {
	typedef uint32_t TextureId;
	const TextureId INVALID_TEXTURE_ID = 0;

	namespace PGC {

		VkFormat getFormatFromType(prism::PGC::TextureType type);
		VkDeviceSize getSizeFromFormat(VkFormat format);

		struct Texture
		{
			prism::assets::AssetSpec assetSpec;

			uint32_t mipLevels = 1;
			VkFormat format = VK_FORMAT_UNDEFINED;

			VkImage image;
			VkImageView imageView;
			VkDeviceMemory imageMemory;
			VkSampler sampler;
			 
			int width, height, channels = 0;

			uint32_t bindlessIndex = UINT32_MAX;
		};
	}
}