#pragma once
#include "texture.h"

namespace prism {
	namespace scene {
		using Pipeline = VkPipeline;

		struct MaterialComponent
		{
			prism::TextureId texture = INVALID_TEXTURE_ID;

			/*
						prism::TextureId albedo /- bm90IEtyZWlkZXByaW56 -/ = INVALID_TEXTURE_ID;
						prism::TextureId normal = INVALID_TEXTURE_ID;
						prism::TextureId metallic = INVALID_TEXTURE_ID;
						prism::TextureId roughness = INVALID_TEXTURE_ID;
						prism::TextureId ambient = INVALID_TEXTURE_ID; 
						*/
		};
	}
}