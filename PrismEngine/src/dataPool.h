#pragma once
#include <cstring>
#include <stack>
#include <vector>
#include "dataHandle.h"

namespace prism {
    namespace scene {
		template <typename Handle>
		class DataPool {
		public:

            using DataType = typename Handle::DataType;
            using TagType = typename Handle::TagType;
            using HandleType = Handle;

            struct Item {
                DataType* data = nullptr;
                uint16_t size = 0;
                uint16_t refCount = 0;
                bool isActive = false;

                Item() = default;

                void cleanup() {
                    if (data) { free(data); data = nullptr; }
                }
            };

            struct Stats {
                size_t totalAllocations = 0;
                size_t totalMemory = 0;
                size_t activeItems = 0;
                size_t freeIds = 0;
            };

            template <std::size_t N>
            HandleType add(const std::array<DataType, N>& data) {
                return add(data.data(), static_cast<uint16_t>(N));
            }

            HandleType add(const DataType* data, uint16_t size) {
                if (!data || size == 0) return HandleType::invalid();
                
                auto* newData = static_cast<DataType*>(malloc(size * sizeof(DataType)));

                if (!newData) return HandleType::invalid();
                
                uint32_t id = getNextId();

                memcpy(newData, data, size * sizeof(DataType));

                auto& item = items[id];
                item.data = newData;
                item.size = size;
                item.refCount = 0;
                item.isActive = true;
                activeCount++;
                stats.totalAllocations++;
                stats.totalMemory += size * sizeof(DataType);

                return HandleType{id};
            }

            const DataType* get(HandleType handle, uint16_t& outSize) const {
                outSize = 0;
                if (!handle.isValid() || handle.id >= items.size()) return nullptr;
                
                const auto& item = items[handle.id];
                if (!item.isActive) return nullptr;

                outSize = items[handle.id].size;
                return items[handle.id].data;
            }

            void addRef(uint32_t id) {
                if (id < items.size() && items[id].isActive) {
                    items[id].refCount++;
                }
            }

            void addRef(HandleType handle) {
                if (handle.isValid()) addRef(handle.id);
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
                    stats.totalMemory -= items[id].size * sizeof(DataType);
                    freeIds.push(id);
                }
            }

            void remove(HandleType handle) {
                if (handle.isValid()) remove(handle.id);
            }

            void forceRemove(HandleType handle) {
                if (handle.isValid() && handle.id < items.size() && items[handle.id].isActive) {
                    items[handle.id].refCount = 1;
                    remove(handle);
                }
            }

            Stats getStats() const {
                Stats res = stats;
                res.activeItems = activeCount;
                res.freeIds = freeIds.size();
                return res;
            }

            void cleanup() {
                for (auto& item : items) item.cleanup();
                items.clear();
                while (!freeIds.empty()) freeIds.pop();
                activeCount = 0;
                maxId = 0;
                stats = Stats{};
            }

            ~DataPool() {
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