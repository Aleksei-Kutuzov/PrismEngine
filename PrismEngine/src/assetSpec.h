#pragma once
#include <cstdint>
#include <filesystem>
#include <variant>
#include <array>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtc/matrix_transform.hpp>

namespace prism {
	namespace PGC {
		enum class TextureType : uint8_t {
			ALBEDO,   // RGBA
			NORMAL,   // RGBA UNORM
			MRAOH,     // RGBA UNORM (R=Metallic, G=Roughness, B=AO, A=Height)
			EMISSION,  // RGBA UNORM
		};

		struct MeshTransform {
			glm::vec3 position = { 0.f, 0.f , 0.f };
			glm::quat rotation;
			glm::vec3 scale = { 1.f, 1.f, 1.f };

			bool operator==(const MeshTransform& other) const;
			bool operator!=(const MeshTransform& other) const;
		};
	}

	namespace assets {
		struct TexturePath {
			std::filesystem::path path;
			prism::PGC::TextureType type;

			bool operator==(const TexturePath& other) const;
		};
			
		struct TextureColor {
			std::array<uint8_t, 4> color;
			prism::PGC::TextureType type;

			bool operator==(const TextureColor& other) const;
		};
		
		struct MeshPath {
			std::filesystem::path path;
			std::string linkName;
			prism::PGC::MeshTransform transform;

			bool operator==(const MeshPath& other) const;

			bool onlyTransformDiff(const MeshPath& other) const;
		};
		
		struct MeshCube {
			prism::PGC::MeshTransform transform;
			bool operator==(const MeshCube& other) const;
			bool onlyTransformDiff(const MeshCube& other) const;
		};
		
		struct MeshPlane {
			prism::PGC::MeshTransform transform;
			bool operator==(const MeshPlane& other) const;
			bool onlyTransformDiff(const MeshPlane& other) const;
		};

		struct MeshGrid {
			uint16_t subdivisionsX;
			uint16_t subdivisionsZ;
			uint16_t repeatTextureX;
			uint16_t repeatTextureZ;

			prism::PGC::MeshTransform transform;

			bool operator==(const MeshGrid& other) const;
			bool onlyTransformDiff(const MeshGrid& other) const;
		};

		struct MeshIcoSphere {
			uint8_t subdivisions;
			prism::PGC::MeshTransform transform;

			bool operator==(const MeshIcoSphere& other) const;
			bool onlyTransformDiff(const MeshIcoSphere& other) const;
		};

		struct MeshUvSphere {
			uint16_t subdivisionsVert;
			uint16_t subdivisionsHoriz;
			prism::PGC::MeshTransform transform;

			bool operator==(const MeshUvSphere& other) const;
			bool onlyTransformDiff(const MeshUvSphere& other) const;
		};

	    
		using AssetSpec = std::variant<std::monostate, TexturePath, TextureColor, MeshPath, MeshCube, MeshPlane, MeshGrid, MeshIcoSphere, MeshUvSphere>;

		template<class... Ts>
		struct overloaded : Ts... {
			using Ts::operator()...;
		};

		template<class... Ts>
		overloaded(Ts...) -> overloaded<Ts...>;
	}
}