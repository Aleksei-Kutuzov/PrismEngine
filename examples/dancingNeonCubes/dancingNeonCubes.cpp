#include "PrismEngine.h"
#include <inputSystem.h>
#include <timeResource.h>
#include "../examples.h"
#include <cmath>
#include <iostream>

namespace dancingNeonCubes {

    // =========================================================================
    // КОНСТАНТЫ
    // =========================================================================
    constexpr std::string_view EXAMPLE_NAME = "dancingNeonCubes";
    constexpr std::string_view WINDOW_TITLE = "Dancing Neon Cubes - Geometric Ballet";
    constexpr int WINDOW_WIDTH = 1200;
    constexpr int WINDOW_HEIGHT = 800;
    constexpr float PI = 3.14159265359f;

    using namespace prism::scene;

    // =========================================================================
    // КОМПОНЕНТЫ
    // =========================================================================

    /**
     * @brief Теговый компонент для маркировки танцующих кубов.
     * В ECS пустые структуры (tag components),
     * так как они не занимают памяти и позволяют быстро фильтровать сущности.
     */
    struct NeonTagComponent {};

    // =========================================================================
    // СИСТЕМЫ
    // =========================================================================

    /**
     * @brief Система сложного вращения.
     * Создает красивый геометрический "танец" объектов на основе тригонометрических функций.
     */
    class DancingNeonCubesSystem : public ISystem {
    public:
        explicit DancingNeonCubesSystem(Scene* scene) : scene_(scene) {}

        void update() override {
            const auto* timeRes = scene_->getResource<TimeResource>();
            if (!timeRes) return;

            const float time = static_cast<float>(timeRes->time);
            const float deltaTime = timeRes->deltaTime;

            const auto entities = scene_->getEntitiesWithAll<NeonTagComponent, TransformComponent, MeshComponent>();
            const size_t entityCount = entities.size();

            if (entityCount == 0) return;

            size_t i = 0;
            for (auto entity : entities) {
                auto* transform = scene_->getComponent<TransformComponent>(entity);
                if (!transform) continue;

                // Каждый объект получает уникальное поведение на основе своего индекса
                const float phase = (static_cast<float>(i) / static_cast<float>(entityCount)) * 2.0f * PI;

                // Сложное движение по орбите
                const float orbitRadius = 30.0f + std::sin(time * 0.5f + phase) * 1.0f;
                transform->pos.x = orbitRadius * std::cos(time + phase);
                transform->pos.z = orbitRadius * std::sin(time * 1.5f + phase);
                transform->pos.y = std::sin(time * 2.0f + phase) * 1.5f;

                // Многоосевое вращение
                transform->rot.x += 45.0f * deltaTime * std::sin(phase);
                transform->rot.y += 60.0f * deltaTime * std::cos(phase * 1.3f);
                transform->rot.z += 30.0f * deltaTime * std::sin(phase * 0.7f);

                // Пульсирующий масштаб
                const float pulse = 0.7f + std::sin(time * 3.0f + phase) * 0.3f;
                transform->scale = { pulse, pulse, pulse };

                i++;
            }
        }

    private:
        Scene* scene_;
    };

    // =========================================================================
    // ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
    // =========================================================================

    /**
     * @brief Создает круг из кубов.
     */
    void createNeonCubeCircle(Scene& scene,
        const MeshComponent& mesh,
        const MaterialComponent& material,
        int count,
        float radius)
    {
        for (int i = 0; i < count; ++i) {
            const float angle = (static_cast<float>(i) / static_cast<float>(count)) * 2.0f * PI;

            const Position position = {
                std::cos(angle) * radius,
                0.0f,
                std::sin(angle) * radius
            };

            Entity cube = scene.createEntity();

            scene.addComponent(cube, TransformComponent{
                position,
                {0.0f, 0.0f, 0.0f},
                {0.1f, 0.1f, 0.1f}
                });

            scene.addComponent(cube, mesh);
            scene.addComponent(cube, material);
            scene.addComponent(cube, NeonTagComponent{}); // Маркируем сущность для системы
        }
    }

    /**
     * @brief Создает фоновую плоскость (задний план).
     */
    void createBackground(Scene& scene,
        const MeshComponent& mesh,
        const MaterialComponent& material)
    {
        Entity background = scene.createEntity();

        scene.addComponent(background, mesh);
        scene.addComponent(background, material);
        scene.addComponent(background, TransformComponent{
            {0.0f, -4.0f, 5.0f},    // Позиция
            {0.0f, 90.0f, 0.0f},    // Поворот
            {29.0f, 1.0f, 31.0f}    // Масштаб
            });
    }

    // =========================================================================
    // ТОЧКА ВХОДА ПРИМЕРА
    // =========================================================================

    /**
     * @brief Демонстрация танцующих неоновых кубов.
     */
    int dancingNeonCubesDemo(int targetFps = 60) {
        prism::init();
        prism::basePath = std::string(EXAMPLE_NAME);

        Scene scene;

        // Создаем ресурс окна
        WindowResource window = WindowResource::CreateCentered(
            WINDOW_TITLE.data(),
            WINDOW_WIDTH,
            WINDOW_HEIGHT
        );
        window.setResizable(true);
        scene.setResource<WindowResource>(window);

        // Создаем и настраиваем рендерер
        prism::render::Renderer renderer;
        prism::linker.link(&renderer, &scene); // Сначала рендерер, потом сцена

        renderer.setDefaultSettings();
        renderer.settings.defaultPipeline.shaders = {
            "vert.spv",
            "frag.spv",
            std::string(EXAMPLE_NAME) + "/shaders/"
        };
        renderer.init();

        std::cout << "Loading example: " << EXAMPLE_NAME << std::endl;

        // =========================================================================
        // ЗАГРУЗКА РЕСУРСОВ
        // =========================================================================

        MeshComponent cubeMesh = renderer.meshBuilder()
            .size(1)
            .model(0, "neoncube.obj")
            .complete();

        MeshComponent planeMesh = renderer.meshBuilder()
            .size(1)
            .model(0, "plane.obj")
            .complete();

        renderer.updateMeshes();

        MaterialComponent cubeMaterial = renderer.materialBuilder()
            .size(1)
            .albedo(0, "neoncube.png")
            .complete();

        MaterialComponent backMaterial = renderer.materialBuilder()
            .size(1)
            .albedo(0, "back.jpeg")
            .complete();

        // =========================================================================
        // НАСТРОЙКА СИСТЕМ И РЕСУРСОВ
        // =========================================================================

        TimeResource timeRes{};
        timeRes.setFPSCap(targetFps);
        scene.setResource<TimeResource>(timeRes);
        scene.setResource<InputResource>(InputResource{});

        // Порядок регистрации систем важен: сначала логика, потом рендеринг
        scene.registerSystem<TimeSystem>(&scene);
        scene.registerSystem<InputSystem>(&scene);
        scene.registerSystem<DancingNeonCubesSystem>(&scene);
        scene.registerSystem<RenderSystem>(&scene);

        // =========================================================================
        // СОЗДАНИЕ КАМЕРЫ
        // =========================================================================

        Entity camera = scene.createEntity();
        scene.addComponent(camera, TransformComponent{
            {0.0f, 50.0f, 5.0f},    // Позиция камеры (высоко сверху)
            {0.0f, 0.0f, 0.0f},     // Поворот по умолчанию
            {1.0f, 1.0f, 1.0f}      // Масштаб
            });

        CameraComponent cameraConfig{};
        cameraConfig.isActive = true;
        cameraConfig.fovy = 60.0f;
        cameraConfig.zNear = 0.1f;
        cameraConfig.zFar = 300.0f;
        cameraConfig.look = { 0.0f, -90.0f, 0.0f }; // Смотрим строго вниз

        scene.addComponent(camera, cameraConfig);

        // =========================================================================
        // СОЗДАНИЕ ОБЪЕКТОВ СЦЕНЫ
        // =========================================================================

        // Создаем 12 кубов по кругу
        createNeonCubeCircle(scene, cubeMesh, cubeMaterial, 12, 4.0f);

        // Создаем фоновую плоскость
        createBackground(scene, planeMesh, backMaterial);

        // =========================================================================
        // ИНФОРМАЦИЯ ДЛЯ ПОЛЬЗОВАТЕЛЯ И ГЛАВНЫЙ ЦИКЛ
        // =========================================================================

        std::cout << "=== Dancing Neon Cubes - Geometric Ballet ===" << std::endl;
        std::cout << "Watch the cubes dance in harmonic patterns!" << std::endl;
        std::cout << "Each cube has its own unique movement and rotation." << std::endl;

        const auto* windowRes = scene.getResource<WindowResource>();
        while (windowRes && !windowRes->isClose()) {
            scene.update();
        }

        renderer.destroy();
        return 0;
    }

} // namespace dancingNeonCubes