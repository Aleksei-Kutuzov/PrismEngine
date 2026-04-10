#pragma once
#include "registryComponentTemplate.h"

namespace prism {
	namespace scene {
		struct MeshTag {};
		using MeshComponent = RegistryComponentTemplate<MeshTag>;
	}
}