#pragma once
#include "pgcResourceStorage.h"
#include "textureLoader.h"
#include "assetSpec.h"
#include <unordered_map>

DECLARE_PGC_LAYER_INSTANCE(L1)

class TextureStorage : public L1_Object<TextureStorage> {
public:
	void createImpl();
	TextureId load(assets::AssetSpec assetSpec);
	Texture& getData(TextureId id);
	//void reload(assets::AssetSpec assetSpec, TextureId id);
	void unload(TextureId id);
	void update();
	void clear();
	void cleanupImpl();

private:
	TextureId addId();
	void delId(TextureId id);

	PGC::L2::TextureLoader* loader;

	std::vector<Texture> data;
	std::stack<TextureId> freeIds;
	TextureId nextId = INVALID_TEXTURE_ID + 1;
	bool isActual;
};

END_NAMESPACE_DECLARATION