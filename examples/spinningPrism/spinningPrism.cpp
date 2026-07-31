#include "PrismEngine.h"
#include "../examples.h"
#include <iostream>

namespace spinningPrism {

    // =========================================================================
    // КОНСТАНТЫ
    // =========================================================================
    constexpr std::string_view EXAMPLE_NAME = "spinningPrism";
    constexpr std::string_view WINDOW_TITLE = "Spinning Prism Demo";
    constexpr float ROTATION_SPEED = 45.0f; // градусов в секунду
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;
    constexpr int TARGET_FPS = 60;

    using namespace prism::scene;

    // =========================================================================
    // СИСТЕМЫ
    // =========================================================================

    /**
     * @brief Система вращения.
     * Автоматически вращает все объекты, имеющие компоненты Transform и Mesh.
     * Демонстрирует принцип работы систем в ECS-архитектуре.
     */
    class RotationSystem : public ISystem {
    public:
        explicit RotationSystem(Scene* scene) : scene_(scene) {}

        void update() override {
            if (!scene_) return;

            // Получаем все сущности, имеющие и Transform, и Mesh компоненты
            const auto rotatingObjects = scene_->getEntitiesWithAll<TransformComponent, MeshComponent>();
            const auto* timeRes = scene_->getResource<TimeResource>();

            if (!timeRes) return;

            const float deltaRotation = ROTATION_SPEED * timeRes->deltaTime;

            // Вращаем каждый объект вокруг оси Y
            for (auto entity : rotatingObjects) {
                if (auto* transform = scene_->getComponent<TransformComponent>(entity)) {
                    transform->rot.y += deltaRotation;
                }
            }
        }

    private:
        Scene* scene_;
    };

    // =========================================================================
    // ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
    // =========================================================================

    /**
     * @brief Создает 3D-объект с заданными параметрами.
     * Объект собирается из компонентов.
     */
    Entity create3DObject(Scene& scene,
        const MeshComponent& mesh,
        const MaterialComponent& material,
        Position position = { 0.0f, 0.0f, 0.0f },
        Scale scale = { 1.0f, 1.0f, 1.0f })
    {
        Entity entity = scene.createEntity();

        // Добавляем компонент трансформации (позиция, вращение, масштаб)
        scene.addComponent(entity, TransformComponent{
            position,           // Позиция в мире
            {0.0f, 0.0f, 0.0f}, // Начальное вращение (в градусах)
            scale               // Масштаб
            });

        // Добавляем компонент меша (геометрия объекта)
        scene.addComponent(entity, mesh);

        // Добавляем компонент материала (внешний вид и текстуры)
        scene.addComponent(entity, material);

        return entity;
    }

    // =========================================================================
    // ТОЧКА ВХОДА ПРИМЕРА
    // =========================================================================

    /**
     * @brief Демонстрация вращающейся призмы - первый пример для движка PrismEngine.
     *
     * Этот пример показывает:
     * 1. Как инициализировать движок и создать окно.
     * 2. Как работать с архитектурой ECS (Entity-Component-System).
     * 3. Как создавать и настраивать 3D-объекты.
     * 4. Как использовать системы для добавления поведения.
     */
    int spinningPrismDemo(int targetFps = TARGET_FPS) {

        // ========== ШАГ 1: ИНИЦИАЛИЗАЦИЯ ДВИЖКА ==========
        prism::init();
        prism::basePath = std::string(EXAMPLE_NAME);

        Scene scene;

        // Создаем ресурс окна для отображения 3D-графики
        WindowResource window = WindowResource::CreateCentered(
            WINDOW_TITLE.data(),
            WINDOW_WIDTH,
            WINDOW_HEIGHT
        );
        scene.setResource<WindowResource>(window);

        // Создаем и настраиваем рендерер
        prism::render::Renderer renderer;
        prism::linker.link(&renderer, &scene);

        // setDefaultSettings требует слинкованную с рендером сцену, содержащую ресурс окна
        renderer.setDefaultSettings();

        // Указываем пути к шейдерам (программы для видеокарты)
        renderer.settings.defaultPipeline.shaders = {
            "vert.spv",
            "frag.spv",
            std::string(EXAMPLE_NAME) + "/shaders/"
        };
        renderer.init();

        // ========== ШАГ 2: ЗАГРУЗКА РЕСУРСОВ ==========

        // Загружаем 3D-модель призмы из файла
        MeshComponent prismMesh = renderer.meshBuilder()
            .size(1)
            .model(0, "prism.obj")
            .complete();

        // Загружаем материал для призмы
        MaterialComponent prismMaterial = renderer.materialBuilder()
            .size(1)
            .albedo(0, "prismfasetexturex.png")
            .complete();

        // Применяем загруженные ресурсы в рендерере
        renderer.updateMeshes();

        // ========== ШАГ 3: НАСТРОЙКА СИСТЕМ И РЕСУРСОВ ==========

        // Ресурс времени
        TimeResource timeRes{};
        timeRes.setFPSCap(targetFps);
        scene.setResource<TimeResource>(timeRes);

        // Ресурс и система ввода (нужна для обновления состояний окна и ввода)
        scene.setResource<InputResource>(InputResource{});
        scene.registerSystem<InputSystem>(&scene);

        // Система обновления времени
        scene.registerSystem<TimeSystem>(&scene);

        // Наша кастомная система вращения
        scene.registerSystem<RotationSystem>(&scene);

        // Система рендеринга (отвечает за отрисовку, должна быть после обновления логики)
        scene.registerSystem<RenderSystem>(&scene);

        // ========== ШАГ 4: СОЗДАНИЕ КАМЕРЫ ==========

        Entity camera = scene.createEntity();

        // Позиционируем камеру так, чтобы хорошо видеть сцену
        scene.addComponent(camera, TransformComponent{
            {0.0f, 2.0f, 10.0f}, // Камера смотрит на сцену сверху и сзади
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f}
            });

        // Настраиваем параметры камеры
        CameraComponent cameraConfig{};
        cameraConfig.isActive = true;      // Делаем эту камеру активной
        cameraConfig.fovy = 45.0f;         // Угол обзора (поле зрения)
        cameraConfig.zNear = 0.1f;         // Ближняя плоскость отсечения
        cameraConfig.zFar = 100.0f;        // Дальняя плоскость отсечения
        cameraConfig.look = { -90.0f, -15.0f, 0.0f }; // Углы Эйлера

        scene.addComponent(camera, cameraConfig);

        // ========== ШАГ 5: СОЗДАНИЕ ОБЪЕКТОВ СЦЕНЫ ==========

        // Центральная призма
        create3DObject(scene, prismMesh, prismMaterial,
            { 0.0f, 0.0f, 0.0f },     // Позиция в центре
            { 1.0f, 1.0f, 1.0f });    // Полный размер

        // Меньшая призма справа
        create3DObject(scene, prismMesh, prismMaterial,
            { 3.0f, 0.0f, 0.0f },     // Смещена вправо
            { 0.5f, 0.5f, 0.5f });    // Вдвое меньше

        // Меньшая призма слева
        create3DObject(scene, prismMesh, prismMaterial,
            { -3.0f, 0.0f, 0.0f },    // Смещена влево
            { 0.5f, 0.5f, 0.5f });    // Вдвое меньше

        // ========== ШАГ 6: ИНФОРМАЦИЯ ДЛЯ ПОЛЬЗОВАТЕЛЯ ==========

        std::cout << "=== PrismEngine: Spinning Prism Demo ===" << std::endl;
        std::cout << "All prisms automatically rotate at a speed of "
            << ROTATION_SPEED << " degrees per second." << std::endl;
        std::cout << "Close the window to exit." << std::endl;

        // ========== ШАГ 7: ГЛАВНЫЙ ЦИКЛ ПРИЛОЖЕНИЯ ==========

        WindowResource* windowRes = scene.getResource<WindowResource>();

        while (windowRes && !windowRes->isClose()) {
            scene.update();
        }

        // ========== ШАГ 8: КОРРЕКТНОЕ ЗАВЕРШЕНИЕ ==========

        renderer.destroy();
        return 0;
    }

} // namespace spinningPrism