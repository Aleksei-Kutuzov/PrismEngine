#pragma once
#include "pgcResourceStorage.h"
#include "textureLoader.h"
#include <unordered_map>

DECLARE_PGC_LAYER_INSTANCE(L1)
class TextureStorage : public Storage<TextureId, Texture, PGC::L2::TextureLoader, TextureStorage> {
public:
	void createImpl();
	TextureId loadImpl(Texture textureData);
	void unloadImpl(TextureId id);
	void updateImpl();
	void clearImpl();
	void cleanupImpl();
};
END_NAMESPACE_DECLARATION