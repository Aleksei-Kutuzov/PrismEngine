#include "PrismEngine.h"
#include "entity.h"
#include <inputResource.h>
#include <inputSystem.h>
#include <timeResource.h>
#include "../examples.h"

#include <cmath>
#include <iostream>

namespace solarSystem {

    // =========================================================================
    // КОНСТАНТЫ
    // =========================================================================
    constexpr std::string_view EXAMPLE_NAME = "solarSystem";
    constexpr std::string_view WINDOW_TITLE = "The Solar System Model";
    constexpr int WINDOW_WIDTH = 1200;
    constexpr int WINDOW_HEIGHT = 800;

    using namespace prism::scene;

    // =========================================================================
    // КОМПОНЕНТЫ
    // =========================================================================

    /**
     * @brief Компонент небесного тела.
     * Хранит данные для орбитального движения и вращения вокруг своей оси.
     */
    struct PlanetaryBodyComponent {
        Entity parent = INVALID_ENTITY_ID; // Сущность-родитель для центра орбиты
        float orbitRadius = 0.0f;          // Радиус орбиты
        float orbitalSpeed = 0.0f;         // Скорость движения по орбите (градусов/секунду)
        float orbitAngle = 0.0f;           // Текущий угол на орбите
        float rotationSpeed = 0.0f;        // Скорость вращения вокруг своей оси (градусов/секунду)
    };

    // =========================================================================
    // СИСТЕМЫ
    // =========================================================================

    /**
     * @brief Система планетарного движения.
     * Обновляет позиции и вращения небесных тел на основе их орбитальных параметров.
     */
    class PlanetarySystem : public ISystem {
    public:
        explicit PlanetarySystem(Scene* scene) : scene_(scene) {}

        void update() override {
            const auto* timeRes = scene_->getResource<TimeResource>();
            if (!timeRes) return;

            const float dt = timeRes->deltaTime;
            const auto entities = scene_->getEntitiesWithAll<TransformComponent, PlanetaryBodyComponent>();

            for (auto entity : entities) {
                auto* transform = scene_->getComponent<TransformComponent>(entity);
                auto* planetary = scene_->getComponent<PlanetaryBodyComponent>(entity);

                if (!transform || !planetary) continue;

                // Вращение вокруг собственной оси
                transform->rot.y += planetary->rotationSpeed * dt;

                // Движение по орбите
                planetary->orbitAngle += planetary->orbitalSpeed * dt;

                // Вычисляем позицию на круговой орбите
                glm::vec3 centerPos{ 0.0f, 0.0f, 0.0f };
                if (planetary->parent != INVALID_ENTITY_ID) {
                    if (auto parentTransform = scene_->getComponent<TransformComponent>(planetary->parent)) {
                        centerPos.x = parentTransform->pos.x;
                        centerPos.y = parentTransform->pos.y;
                        centerPos.z = parentTransform->pos.z; 
                    }
                }

                const float rad = glm::radians(planetary->orbitAngle);
                transform->pos.x = centerPos.x + planetary->orbitRadius * std::cos(rad);
                transform->pos.z = centerPos.z + planetary->orbitRadius * std::sin(rad);
            }
        }

    private:
        Scene* scene_;
    };

    /**
     * @brief Система управления камерой от первого лица (Fly Camera).
     */
    class FlyCameraSystem : public ISystem {
    public:
        explicit FlyCameraSystem(Scene* scene) : scene_(scene) {}

        void start() override {
            // SDL_SetRelativeMouseMode(SDL_TRUE); // Раскомментируйте, если требуется захват мыши
        }

        void update() override {
            if (!scene_) return;

            auto* input = scene_->getResource<InputResource>();
            const auto* timeRes = scene_->getResource<TimeResource>();

            if (!input || !timeRes) return;

            const float dt = timeRes->unscaledDeltaTime;
            const auto entities = scene_->getEntitiesWithAll<TransformComponent, CameraComponent>();

            for (auto entity : entities) {
                auto* transform = scene_->getComponent<TransformComponent>(entity);
                auto* camera = scene_->getComponent<CameraComponent>(entity);

                if (!transform || !camera || !camera->isActive) continue;

                // Обработка вращения камеры мышью
                const float sensitivity = 0.1f;
                camera->look.x += static_cast<float>(input->getMouseDeltaX()) * sensitivity;
                camera->look.y -= static_cast<float>(input->getMouseDeltaY()) * sensitivity;

                // Ограничение угла обзора по вертикали (чтобы избежать инверсии)
                camera->look.y = std::clamp(camera->look.y, -89.0f, 89.0f);

                // Скорость перемещения
                float speed = 5.0f * dt;
                if (input->getKeyState(KeyCode::LeftControl) == HELD) {
                    speed *= 3.0f;
                }

                // Вычисление векторов направления
                const float radX = glm::radians(camera->look.x);
                const float radY = glm::radians(camera->look.y);

                glm::vec3 front;
                front.x = std::cos(radX) * std::cos(radY);
                front.y = std::sin(radY);
                front.z = std::sin(radX) * std::cos(radY);
                front = glm::normalize(front);

                const glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

                // Обработка перемещения (WASD + Space + Shift)
                if (input->getKeyState(KeyCode::W) == HELD) {
                    transform->pos.x += front.x * speed;
                    transform->pos.y += front.y * speed;
                    transform->pos.z += front.z * speed;
                }
                if (input->getKeyState(KeyCode::S) == HELD) {
                    transform->pos.x -= front.x * speed;
                    transform->pos.y -= front.y * speed;
                    transform->pos.z -= front.z * speed;
                }
                if (input->getKeyState(KeyCode::A) == HELD) {
                    transform->pos.x -= right.x * speed;
                    transform->pos.z -= right.z * speed;
                }
                if (input->getKeyState(KeyCode::D) == HELD) {
                    transform->pos.x += right.x * speed;
                    transform->pos.z += right.z * speed;
                }
                if (input->getKeyState(KeyCode::Space) == HELD) {
                    transform->pos.y += speed;
                }
                if (input->getKeyState(KeyCode::LeftShift) == HELD) {
                    transform->pos.y -= speed;
                }
            }
        }

    private:
        Scene* scene_;
    };

    // =========================================================================
    // ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
    // =========================================================================

    void createSkybox(Scene& scene, const MeshComponent& mesh, const MaterialComponent& material) {
        Entity skybox = scene.createEntity();
        scene.addComponent(skybox, mesh);
        scene.addComponent(skybox, material);
        scene.addComponent(skybox, TransformComponent{
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {120.0f, 120.0f, 120.0f}
            });
    }

    void createCamera(Scene& scene, const TransformComponent& transform, const CameraComponent& cameraConfig) {
        Entity camera = scene.createEntity();
        scene.addComponent(camera, transform);
        scene.addComponent(camera, cameraConfig);
    }

    Entity createPlanet(Scene& scene, prism::render::Renderer& renderer, std::string_view name,
        float orbitRadius, float orbitalSpeed, float rotationSpeed,
        Entity parent = INVALID_ENTITY_ID)
    {
        Entity planet = scene.createEntity();

        scene.addComponent(planet, renderer.meshBuilder()
            .size(1)
            .model(0, std::string(name) + ".obj")
            .complete());

        // Примечание: заменено .forMesh(planet) на .size(1) для соответствия стандартному API билдера,
        // как в предыдущих примерах. Если .forMesh() является обязательным в вашей версии движка, верните его.
        scene.addComponent(planet, renderer.materialBuilder()
            .size(1)
            .albedo(0, std::string(name) + ".png")
            .complete());

        scene.addComponent(planet, TransformComponent{
            {0.0f, 0.0f, 0.0f},
            {90.0f, 0.0f, 0.0f},
            {300.0f, 300.0f, 300.0f} // Масштаб планет (оставлен как в оригинале)
            });

        scene.addComponent(planet, PlanetaryBodyComponent{
            parent, orbitRadius, orbitalSpeed, 0.0f, rotationSpeed
            });

        return planet;
    }

    // =========================================================================
    // ТОЧКА ВХОДА ПРИМЕРА
    // =========================================================================

    int solarSystemDemo(int targetFps = 60) {
        prism::init();
        prism::basePath = std::string(EXAMPLE_NAME);

        Scene scene;
        scene.setResource<WindowResource>(WindowResource::CreateCentered(
            WINDOW_TITLE.data(), WINDOW_WIDTH, WINDOW_HEIGHT
        ));

        prism::render::Renderer renderer;
        prism::linker.link(&renderer, &scene); // Стандартный порядок: рендерер, затем сцена

        renderer.setDefaultSettings();
        renderer.settings.defaultPipeline.shaders = {
            "vert.spv",
            "frag.spv",
            std::string(EXAMPLE_NAME) + "/shaders/"
        };
        renderer.init();

        // =========================================================================
        // ЗАГРУЗКА РЕСУРСОВ
        // =========================================================================

        MeshComponent skyboxMesh = renderer.meshBuilder()
            .size(1)
            .model(0, "skybox2.obj")
            .complete();

        MaterialComponent skyboxMaterial = renderer.materialBuilder()
            .size(1)
            .albedo(0, "lambert1_emissive.jpeg")
            .complete();

        // =========================================================================
        // СОЗДАНИЕ ОБЪЕКТОВ СЦЕНЫ
        // =========================================================================

        Entity sun = createPlanet(scene, renderer, "Sun", 0.0f, 0.0f, 0.0f);
        createPlanet(scene, renderer, "Mercury", 100.0f, 15.0f, 8.0f);
        createPlanet(scene, renderer, "Venus", 150.0f, 12.0f, 6.0f);

        Entity earth = createPlanet(scene, renderer, "Earth", 200.0f, 10.0f, 10.0f);
        createPlanet(scene, renderer, "Moon", 15.0f, 30.0f, 5.0f, earth); // Луна привязана к Земле

        createPlanet(scene, renderer, "Mars", 250.0f, 8.0f, 9.0f);
        createPlanet(scene, renderer, "Jupiter", 350.0f, 5.0f, 15.0f);

        Entity saturn = createPlanet(scene, renderer, "Saturn", 450.0f, 4.0f, 12.0f);
        createPlanet(scene, renderer, "SaturnRing", 0.0f, 0.0f, 8.0f, saturn);

        Entity uranus = createPlanet(scene, renderer, "Uranus", 550.0f, 3.0f, 10.0f);
        createPlanet(scene, renderer, "UranusRing", 0.0f, 0.0f, 6.0f, uranus);

        // Обновляем меши в рендерере после создания всех объектов
        renderer.updateMeshes();

        // =========================================================================
        // НАСТРОЙКА СИСТЕМ И РЕСУРСОВ
        // =========================================================================

        TimeResource timeRes{};
        timeRes.setFPSCap(targetFps);
        scene.setResource<TimeResource>(timeRes);
        scene.setResource<InputResource>(InputResource{});

        // Порядок важен: сначала ввод и время, затем логика (камера, планеты), и только потом рендеринг
        scene.registerSystem<TimeSystem>(&scene);
        scene.registerSystem<InputSystem>(&scene);
        scene.registerSystem<FlyCameraSystem>(&scene);
        scene.registerSystem<PlanetarySystem>(&scene);
        scene.registerSystem<RenderSystem>(&scene);

        // =========================================================================
        // КАМЕРА И ФОН
        // =========================================================================

        CameraComponent cameraConfig{};
        cameraConfig.isActive = true;
        cameraConfig.fovy = 60.0f;
        cameraConfig.zNear = 0.1f;
        cameraConfig.zFar = 1200.0f;
        cameraConfig.look = { 0.0f, -90.0f, 0.0f }; // Смотрим вниз под углом

        createCamera(scene,
            TransformComponent{ {0.0f, 150.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f} },
            cameraConfig
        );

        createSkybox(scene, skyboxMesh, skyboxMaterial);

        // =========================================================================
        // ГЛАВНЫЙ ЦИКЛ
        // =========================================================================

        const auto* windowRes = scene.getResource<WindowResource>();
        while (windowRes && !windowRes->isClose()) {
            scene.update();
        }

        renderer.destroy();
        return 0;
    }

} // namespace solarSystem