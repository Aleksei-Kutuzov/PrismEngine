#pragma once
#include "utils.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"
#include <unordered_map>

DECLARE_PGC_LAYER_INSTANCE(L1)
template<typename DataId, typename Data, typename Loader, typename Derived>
class Storage : public L1_Object<Derived> {
public:
	void createImpl() {
		this->loader = new Loader(this->context, this->settings);
	};
	
	template<typename... Args>
	DataId load(std::filesystem::path path, Args&&... args) {
		auto it = this->pathToId.find(path);
		if (it != this->pathToId.end()) return it->second;

		this->needUpdate = true;
		return this->derived().loadImpl(this->loader->load(path, std::forward<Args>(args)...));
	};
	void unload(DataId id) { this->derived().unloadImpl(id); };
	
	Data& get(DataId id) { return this->data[id]; };
	
	void update() { if (this->needUpdate) { this->derived().updateImpl(); this->needUpdate = false; } };
	void clear() { 
		this->derived().clearImpl();
		this->data.clear();
		this->pathToId.clear();
		this->freeIndices.clear();
	};
	
	void cleanupImpl() {		
		this->clear();

		if (this->loader) {
			delete this->loader;
			this->loader = nullptr;
		}
	};

protected:
	uint32_t getNextAvailableIndex() {
		if (!this->freeIndices.empty()) {
			uint32_t index = this->freeIndices.back();
			this->freeIndices.pop_back();
			return index;
		}

		return static_cast<uint32_t>(this->data.size());
	};

	std::vector<Data> data;
	std::unordered_map<std::filesystem::path, DataId> pathToId;
	std::vector<uint32_t> freeIndices;
	Loader* loader = nullptr;
	bool needUpdate = false;
};
END_NAMESPACE_DECLARATION