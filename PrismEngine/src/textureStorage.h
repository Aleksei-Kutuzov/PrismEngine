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
	uint32_t getId(TextureId id);
	void clearImpl();
	void cleanupImpl();
	std::filesystem::path getPathForId(std::filesystem::path path, TextureType type = TextureType::ALBEDO);
};
END_NAMESPACE_DECLARATION