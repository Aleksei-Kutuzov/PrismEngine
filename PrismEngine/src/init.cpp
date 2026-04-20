#include "init.h"

void prism::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	isInit = true;
}