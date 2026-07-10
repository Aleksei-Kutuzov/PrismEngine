#pragma once
#include <unordered_map>
#include "pgcResourceStorage.h"
#include "textureLoader.h"
#include "assetSpec.h"
#include "idPool.h"

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

	PGC::L2::TextureLoader* loader;

	std::vector<Texture> data;
	prism::utils::IdPool<TextureId, INVALID_TEXTURE_ID + 1, INVALID_TEXTURE_ID> pool;
	bool isActual;
};

END_NAMESPACE_DECLARATION