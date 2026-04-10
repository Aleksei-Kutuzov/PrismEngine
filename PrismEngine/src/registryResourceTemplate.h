#pragma once
#include <stack>
#include <vector>
#include "meshComponent.h"
#include "registryComponentTemplate.h"
#include "scene.h"

namespace prism {
    namespace render {
		template <typename T, typename Tag>
		class RegistryResourceTemplate {
		public:
            struct Item {
                T* data = nullptr;
                uint16_t size = 0;
                uint16_t refCount = 0;
                bool isActive = false;

                Item() = default;
            };

            struct Stats {
                size_t totalAllocations = 0;
                size_t totalMemory = 0;
                size_t activeItems = 0;
                size_t freeIds = 0;
            };

            template <std::size_t N>
            scene::RegistryComponentTemplate<Tag> add(const std::array<T, N>& data) {
                return add(data.data(), static_cast<uint16_t>(data.size()));
            }

            scene::RegistryComponentTemplate<Tag> add(const T* data, uint16_t size) {
                if (!data || size == 0) return { scene::INVALID_REGISTRY_ID };
                
                T* newData = static_cast<T*>(malloc(size * sizeof(T)));

                if (!newData) return { scene::INVALID_REGISTRY_ID };
                
                uint32_t id = getNextId();

                memcpy(newData, data, size * sizeof(T));

                auto& item = items[id];
                item.data = newData;
                item.size = size;
                item.refCount = 0;
                item.isActive = true;
                activeCount++;
                stats.totalAllocations++;
                stats.totalMemory += size * sizeof(T);

                return { id };
            }

            const T* get(scene::RegistryComponentTemplate<Tag> component, uint16_t& outSize) const {
                if (component.id >= items.size() || !items[component.id].isActive) {
                    outSize = 0;
                    return nullptr;
                }
                outSize = items[component.id].size;
                return items[component.id].data;
            }

            void addRef(uint32_t id) {
                if (id < items.size() && items[id].isActive) {
                    items[id].refCount++;
                }
            }

            void remove(uint32_t id) {
                if (id >= items.size() || !items[id].isActive) return;

                items[id].refCount--;
                if (items[id].refCount == 0) {
                    free(items[id].data);
                    items[id].data = nullptr;
                    items[id].isActive = false;
                    activeCount--;
                    stats.totalAllocations--;
                    stats.totalMemory -= items[id].size * sizeof(T);
                    freeIds.push(id);
                }
            }

            Stats getStats() const {
                Stats res = stats;
                res.activeItems = activeCount;
                res.freeIds = freeIds.size();
                return stats;
            }

            void cleanup() {
                for (auto& item : items) {
                    if (item.isActive && item.data) {
                        free(item.data);
                    }
                }
                items.clear();
                freeIds = std::stack<uint32_t>();
                activeCount = 0;
            }

            ~RegistryResourceTemplate() {
                cleanup();
            }

		private:
            uint32_t getNextId() {
                if (!freeIds.empty()) {
                    uint32_t id = freeIds.top();
                    freeIds.pop();
                    return id;
                }

                uint32_t id = maxId;

                maxId++;

                if (id >= items.size()) {
                    items.resize(maxId);
                }

                return id;
            }

            std::vector<Item> items;
            std::stack<uint32_t> freeIds;
            uint32_t maxId = 0;
            size_t activeCount = 0;
            Stats stats;
		};

    }
}