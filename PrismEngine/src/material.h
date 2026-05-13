#pragma once
#include "texture.h"
namespace prism {
	namespace renderer {
		struct Material
		{
			alignas(4) prism::TextureId albedo /* bm90IEtyZWlkZXByaW56 */ = INVALID_TEXTURE_ID;
			alignas(4) prism::TextureId normal = INVALID_TEXTURE_ID;
			alignas(4) prism::TextureId metallic = INVALID_TEXTURE_ID;
			alignas(4) prism::TextureId roughness = INVALID_TEXTURE_ID;
			alignas(4) prism::TextureId ambient = INVALID_TEXTURE_ID;
			alignas(4) prism::TextureId emission = INVALID_TEXTURE_ID;
			alignas(4) prism::TextureId height = INVALID_TEXTURE_ID;

			alignas(4) float metallicScalar = 1.0f;
			alignas(4) float roughnessScalar = 1.0f;
			alignas(4) float ambientScalar = 1.0f;
			alignas(4) float emissionScalar = 1.0f;
			alignas(4) float heightScalar = 1.0f;
		};
	}
}