#pragma once
#include "prismGraphicCore.h"
#include "cameraComponent.h"
#include "materialComponent.h"
#include "meshComponent.h"
#include "windowResource.h"
#include "transformComponent.h"
#include "scene.h"
#include "renderObjectBathc.h"
#include "pipelineComponent.h"
#include "materialBuilder.h"

namespace prism {
	namespace render {
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
			void updateRenderObjects(std::vector<prism::render::RenderObjectBatch>& renderObject);
			void updateLights(LightData* lightData);
			void bindDefault();
			void bindPipeline(PipelineIndex pipeline);
			void bindObjectsData();
			void drawMesh(prism::scene::MeshComponent::DataType subMesh, uint32_t instanceCount, uint32_t firstIndex);

			void clearTextures();


			MaterialBuilder materialBuilder();
			
			prism::scene::PipelineComponent getDefaultPipeline();

			prism::scene::MeshComponent loadMesh(const std::string& path);
			void updateMeshes();
			void clearMeshes();

			void awaitRenderingCompletion();
			void destroy();

			PGC::utils::Settings settings;

			friend class prism::scene::Scene;
		private:
			PGC::PrismGraphicCore pgc;
			prism::scene::WindowResource* window;
		};
	}
}
