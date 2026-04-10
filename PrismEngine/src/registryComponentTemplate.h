#pragma once


namespace prism {
    namespace scene {
        constexpr uint32_t INVALID_REGISTRY_ID = UINT32_MAX;

        template <typename RegistryTag>
        struct RegistryComponentTemplate { uint32_t id = INVALID_REGISTRY_ID; };
    }
}