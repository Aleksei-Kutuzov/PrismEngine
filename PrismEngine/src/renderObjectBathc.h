#include "pipelineStorage.h"
#include "meshComponent.h"

namespace prism {
	namespace render {
		struct RenderObjectBatch {
			PipelineIndex pipeline;
			prism::scene::MeshComponent::DataType subMesh;
			uint32_t flags;
			prism::scene::TransformComponent* transform;
			const prism::scene::MaterialComponent::DataType* subMaterial;

			RenderObjectBatch(uint32_t flags, PipelineIndex pipeline, const prism::scene::MeshComponent::DataType subMesh,
				prism::scene::TransformComponent* transform, const prism::scene::MaterialComponent::DataType* subMaterial) :
				flags(flags), pipeline(pipeline), subMesh(subMesh), transform(transform), subMaterial(subMaterial) { }


			bool operator<(const RenderObjectBatch& other) const {
				return std::tie(flags, pipeline, subMesh) < std::tie(other.flags, other.pipeline, other.subMesh);
			}
		};
	}
}