#pragma once
#include <cstdint>
#include <filesystem>
#include <variant>
#include <array>

namespace prism {
	namespace PGC {
		enum class TextureType : uint8_t {
			ALBEDO,   // RGBA
			NORMAL,   // RGBA UNORM
			MRAOH,     // RGBA UNORM (R=Metallic, G=Roughness, B=AO, A=Height)
			EMISSION,  // RGBA UNORM
		};
	}

	namespace assets {
		struct TexturePath {
			std::filesystem::path path;
			prism::PGC::TextureType type;

			bool operator==(const TexturePath& other) const {
				return path == other.path && type == other.type;
			}
		};
			
		struct TextureColor {
			std::array<uint8_t, 4> color;
			prism::PGC::TextureType type;

			bool operator==(const TextureColor& other) const {
				return color == other.color && type == other.type;
			}
		};
		
		using MeshPath = std::filesystem::path;
		
		struct MeshCube {
			bool operator==(const MeshCube&) const { return true; }
		};
		
		struct MeshPlane {
			bool operator==(const MeshPlane&) const { return true; }
		};

		struct MeshGrid {
			uint8_t subdivisionsX;
			uint8_t subdivisionsZ;
			uint8_t repeatTextureX;
			uint8_t repeatTextureZ;

			bool operator==(const MeshGrid& other) const {
				return subdivisionsX == other.subdivisionsX &&
					subdivisionsZ == other.subdivisionsZ &&
					repeatTextureX == other.repeatTextureX &&
					repeatTextureZ == other.repeatTextureZ;
			}
		};

		struct MeshIcoSphere {
			uint8_t subdivisions;

			bool operator==(const MeshIcoSphere& other) const {
				return subdivisions == other.subdivisions;
			}
		};

		struct MeshUvSphere {
			uint8_t subdivisionsVert;
			uint8_t subdivisionsHoriz;

			bool operator==(const MeshUvSphere& other) const {
				return subdivisionsVert == other.subdivisionsVert && subdivisionsHoriz == other.subdivisionsHoriz;
			}
		};

	    
		using AssetSpec = std::variant<TexturePath, TextureColor, MeshPath, MeshCube, MeshPlane, MeshGrid, MeshIcoSphere, MeshUvSphere>;

		template<class... Ts>
		struct overloaded : Ts... {
			using Ts::operator()...;
		};

		template<class... Ts>
		overloaded(Ts...) -> overloaded<Ts...>;
	}
}