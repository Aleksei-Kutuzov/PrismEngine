#include "texture.h"

VkFormat prism::PGC::getFormatFromType(prism::PGC::TextureType type) {
	switch (type) {
	case prism::PGC::TextureType::ALBEDO:   return VK_FORMAT_R8G8B8A8_SRGB;
	case prism::PGC::TextureType::NORMAL:
	case prism::PGC::TextureType::MRAOH:
	case prism::PGC::TextureType::EMISSION: return VK_FORMAT_R8G8B8A8_UNORM;
	default:                                return VK_FORMAT_R8G8B8A8_SRGB;
	}
}

VkDeviceSize prism::PGC::getSizeFromFormat(VkFormat format) {
	switch (format) {
	case VK_FORMAT_R8G8B8A8_SRGB:   return 4;
	case VK_FORMAT_R8G8B8A8_UNORM:  return 4;
	default: return 4;
		// ну да, 4 :)
	}
}
