#pragma once
#include <filesystem>
#include "vulkan/vulkan.h"


namespace prism {
	typedef uint32_t TextureId;
	const TextureId INVALID_TEXTURE_ID = 0;

	namespace PGC {
		enum class TextureType : uint8_t {
			ALBEDO,   // RGBA
			NORMAL,   // RGBA UNORM
			MRAOH,     // RGBA UNORM (R=Metallic, G=Roughness, B=AO, A=Height)
			EMISSION  // RGBA UNORM
		};

		struct Texture
		{
			std::filesystem::path path;
			uint32_t mipLevels = 1;

			TextureType type = TextureType::ALBEDO;
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