#pragma once
#include "prismGraphicCore.h"
#include "cameraComponent.h"
#include "materialComponent.h"
#include "meshComponent.h"
#include "windowResource.h"
#include "transformComponent.h"
#include "scene.h"

namespace prism {
	namespace render {
		struct InstanceData
		{
			prism::scene::TransformComponent* transform;
			prism::scene::MaterialComponent* texture;
		};

		struct LightData {
			std::vector<scene::PointLightComponent> pointLights;
			std::vector<scene::DirectionalLightComponents> directionalLights;
		};

	   class Renderer
	   {
	   public:
			Renderer() : window(nullptr) {};
			void setDefaultSettings();
			void init();
			~Renderer();

			bool isRenderingActive();
			void beginFrame();
			void beginRender();
			void endRender();
			void endFrame();
			void updateCamera(prism::scene::TransformComponent* transform, prism::scene::CameraComponent* camera);
			void updateInstances(std::vector<InstanceData> instanceData);
			void updateLights(LightData* lightData);
			void bindDefault();
			void bindObjectsData();
			void drawMesh(prism::scene::MeshComponent mesh, uint32_t instanceCount, uint32_t firstIndex);

			TextureId addTexture(const std::string& texturePath);
			bool removeTexture(TextureId texture);
			void remodeMaterial(scene::MaterialComponent material);
			void clearTextures();

			prism::scene::MeshComponent loadMesh(const std::string& path);
			const uint32_t* getMeshSubMeshes(prism::scene::MeshComponent mesh, uint16_t& outCount) const;
			void updateMeshes();
			void clearMeshes();

			void awaitRenderingCompletion();
			void destroy();

			PGC::utils::Settings settings;

			friend class prism::scene::Scene;
		private:

			prism::scene::MeshDataPool* meshDataPool;

			PGC::PrismGraphicCore pgc;
			prism::scene::WindowResource* window;
		};
	}
}
