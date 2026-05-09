#pragma once
#include "utils.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"
#include "pathes.h"

DECLARE_PGC_LAYER_INSTANCE(L1)
template<typename DataId, typename Data, typename Loader, typename Derived>
class Storage : public L1_Object<Derived> {
public:
	void createImpl() {
		loader = new Loader(context, settings);
		derived().createImpl();
	};
	
	DataId load(std::filesystem::path path) {
		auto it = pathToId.find(path);
		if (it != pathToId.end()) return it->second;

		needUpdate = true;
		return derived().loadImpl(loader->load(path, prism::rootPath));
	};
	void unload(DataId id) { derived().unloadImpl(id); };
	
	Data& get(DataId id) { return data[id]; };
	
	void update() { if (needUpdate) { derived().updateImpl(); needUpdate = false; } };
	void clear() { derived().clearImpl(); };
	
	void cleanupImpl() {
		derived().cleanupImpl();
		

		data.clear();
		pathToId.clear();
		freeIndices.clear();

		if (loader) {
			delete loader;
			loader = nullptr;
		}
	};

protected:
	uint32_t getNextAvailableIndex() {
		if (!freeIndices.empty()) {
			uint32_t index = freeIndices.back();
			freeIndices.pop_back();
			return index;
		}

		return static_cast<uint32_t>(data.size());
	};

	std::unordered_map<std::filesystem::path, DataId> pathToId;
	std::vector<Data> data;
	std::vector<uint32_t> freeIndices;
	Loader* loader = nullptr;
	bool needUpdate = false;
};
END_NAMESPACE_DECLARATION