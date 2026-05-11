#pragma once
#include "dataPool.h"
#include "material.h"

namespace prism {
	namespace scene {
		struct MaterialTag {};
		using MaterialComponent = DataHandle<prism::renderer::Material, MaterialTag>;
		using MaterialDataPool = prism::scene::DataPool<prism::scene::MaterialComponent>;
	}
}