#include "init.h"
#include "pathes.h"
#include "logger.h"
#include <SDL.h>

void prism::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	char* basePath = SDL_GetBasePath();
	if (basePath) {
		rootPath = std::filesystem::path(basePath);
		SDL_free(basePath);
	}
	else {
		logger::logError(logger::Error::ERROR_GETTING_BASE_PATH, SDL_GetError());
	}

	texturesDir = std::filesystem::path("textures");
	modelsDir = std::filesystem::path("models");
	shadersDir = std::filesystem::path("shaders");

	isInit = true;
}