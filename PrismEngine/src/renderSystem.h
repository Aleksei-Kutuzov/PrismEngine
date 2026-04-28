#pragma once
#include "scene.h"
#include "renderer.h"


namespace prism {
	namespace scene {
        class RenderSystem : public ISystem {
        public:
            RenderSystem(Scene* scene) : scene(scene) {}
            void start() override;
            void update() override;

        private:
            prism::scene::Scene* scene;
            prism::render::Renderer* renderer;
        };
	}
}