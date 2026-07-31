#include "PrismEngine.h"
#include <timeResource.h>
#include <inputResource.h>
#include <inputSystem.h>
#include "entity.h"
#include "../examples.h"



namespace materials {
    using namespace prism::scene;
    class FlyCameraSystem : public prism::scene::ISystem {
    public:
        FlyCameraSystem(Scene* scene) : scene(scene) {}

        // Вызовется при первом кадре 
        void start() override {
            SDL_SetRelativeMouseMode(SDL_TRUE);
        }

        void update() override {
            auto entities = scene->getEntitiesWithAll<TransformComponent, CameraComponent>();
            InputResource* input = scene->getResource<InputResource>();

            for (auto entity : entities) {
                TransformComponent* transform = scene->getComponent<TransformComponent>(entity);
                CameraComponent* camera = scene->getComponent<CameraComponent>(entity);

                if (!camera->isActive) continue;

                // Обработка мыши
                int mouseX, mouseY;
                SDL_GetRelativeMouseState(&mouseX, &mouseY);

                float sensitivity = 0.1f;
                camera->look.x += mouseX * sensitivity;
                camera->look.y -= mouseY * sensitivity;

                if (camera->look.y > 89.0f) camera->look.y = 89.0f;
                if (camera->look.y < -89.0f) camera->look.y = -89.0f;

                // Движение относительно камеры
                float speed = 5.0f * scene->getResource<TimeResource>()->unscaledDeltaTime;
                if (input->getKeyState(KeyCode::LeftControl) == HELD) speed *= 3.0f;

                // Вычисляем направление камеры
                glm::vec3 front;
                front.x = cos(glm::radians(camera->look.x)) * cos(glm::radians(camera->look.y));
                front.y = sin(glm::radians(camera->look.y));
                front.z = sin(glm::radians(camera->look.x)) * cos(glm::radians(camera->look.y));
                front = glm::normalize(front);

                glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

                if (scene->hasResource<InputResource>()) {
                    // Движение - применяем к правильным координатам
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
                    if (input->getKeyState(KeyCode::Space) == HELD) transform->pos.y += speed;
                    if (input->getKeyState(KeyCode::LeftShift) == HELD) transform->pos.y -= speed;
                }
            }
        }

    private:
        Scene* scene;
    };
    class LightSwayingSystem : public prism::scene::ISystem {
    public:
        LightSwayingSystem(Scene* scene) : scene(scene) {}

        void update() override {
            auto entities = scene->getEntitiesWithAll<PointLightComponent>();
            
            for (auto entity : entities) {
                scene->getComponent<PointLightComponent>(entity)->pos.x +=  0.5 * sin(4 * scene->getResource<TimeResource>()->time);
                scene->getComponent<PointLightComponent>(entity)->pos.z += 0.5 * cos(4 * scene->getResource<TimeResource>()->time);
            }                                                                       
        }                                                                           
                                                                                    
    private:                                                                        
        Scene* scene;                                                               
    };



    const std::string EXAMPLE_NAME = "materials";
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;

    using namespace prism::scene;

    Entity create3DObject(Scene& scene,
        const MeshComponent& mesh,
        const MaterialComponent& material,
        Position position = { 0, 0, 0 },
        Scale scale = { 1, 1, 1 }) {
        Entity entity = scene.createEntity();
        scene.addComponent(entity, TransformComponent{
            position,           // Позиция в мире
            {0, 0, 0},          // Начальное вращение (в градусах)
            scale               // Масштаб
            });
        scene.addComponent(entity, mesh);
        scene.addComponent(entity, material);

        return entity;
    }

    int materialsDemo(int targetFps) {
        prism::init();

        prism::basePath = EXAMPLE_NAME;

        // Создаем сцену для хранения всех объектов
        Scene scene;

        // Создаем ресурс окна для отображения 3D графики
        WindowResource window = WindowResource::CreateCentered("The solar system model", WINDOW_WIDTH, WINDOW_HEIGHT);
        scene.setResource<WindowResource>(window);

        // Создаем рендерер
        prism::render::Renderer renderer;

        // Линкуем рендедер с сцену
        prism::linker.link(&renderer, &scene);

        // setDefaultSettings требует слинкованную с рендером сцену, содержашую ресурс окна
        renderer.setDefaultSettings();

        // Указываем пути к шейдерам (программы для видеокарты)
        renderer.settings.defaultPipeline.shaders = {
            "vert.spv",
            //"vert_debug.spv",
            "frag.spv",
            //"frag_debug_normals.spv",
            //"frag_debug_uv.spv",
            //"frag_debug_mrao.spv",
            //"frag_debug_lighting.spv",
            //"frag_debug_pom.spv",
            EXAMPLE_NAME + "/shaders/"
        };

        renderer.init();

        // ========== ШАГ 2: ЗАГРУЗКА РЕСУРСОВ ==========

        // Загружаем 3D модель призмы из файла
        MeshComponent prismMesh = renderer.meshBuilder()
            .size(1)
            .cube(0)//, "neoncube.obj")
            //.icoSphere(0, 8)
            .scale(0, {2.5f, 2.5f, 2.5f})
            .position(0, { 0.5f, 0.f, 0.5f })
            .complete();

        MeshComponent sphereMesh = renderer.meshBuilder()
            .size(1)
            .model(0, "sphere.obj")
            .complete();

        MeshComponent planeeMesh = renderer.meshBuilder()
            .size(1)
            .model(0, "flur.obj")
            //.plane(0)
            //.grid(0, 15, 15, 1, 1)
            //.icoSphere(0, 1)
            .scale(0, { 5.f, 5.f, 5.f })
            .complete();

        // Загружаем материал для призмы
        MaterialComponent rustMaterial = renderer.materialBuilder()
            .size(1)
            .albedo(0, "worn-rusted-painted-ue/worn-rusted-painted_albedo.png") 
            .normal(0, "worn-rusted-painted-ue/worn-rusted-painted_normal-dx.png")
            .metallic(0, "worn-rusted-painted-ue/worn-rusted-painted_metallic.png")
            .roughness(0, "worn-rusted-painted-ue/worn-rusted-painted_roughness.png")
            .ambientOcclusion(0, "worn-rusted-painted-ue/worn-rusted-painted_ao.png")
            .height(0, "worn-rusted-painted-ue/worn-rusted-painted_height.png")
            .complete();

        MaterialComponent stoneMaterial = renderer.materialBuilder()
            .size(1)
            .albedo(0, "sloppy-mortar-stone-wall-ue/sloppy-mortar-stone-wall_albedo.png")
            .normal(0, "sloppy-mortar-stone-wall-ue/sloppy-mortar-stone-wall_normal-dx.png")
            .metallic(0, "sloppy-mortar-stone-wall-ue/sloppy-mortar-stone-wall_metallic.png")
            .roughness(0, "sloppy-mortar-stone-wall-ue/sloppy-mortar-stone-wall_roughness.png")
            .ambientOcclusion(0, "sloppy-mortar-stone-wall-ue/sloppy-mortar-stone-wall_ao.png")
            .height(0, "sloppy-mortar-stone-wall-ue/sloppy-mortar-stone-wall_height.png")
            .complete();

        /*MaterialComponent flurMaterial = renderer.materialBuilder()
            .size(1)
            .albedo(0, "speckled-granite-tiles-ue/speckled-granite-tiles_albedo.png")
            .normal(0, "speckled-granite-tiles-ue/speckled-granite-tiles_normal-dx.png")
            .metallic(0, "speckled-granite-tiles-ue/speckled-granite-tiles_metallic.png")
            .roughness(0, "speckled-granite-tiles-ue/speckled-granite-tiles_roughness.png")
            .ambientOcclusion(0, "speckled-granite-tiles-ue/speckled-granite-tiles_ao.png")
            .height(0, "speckled-granite-tiles-ue/speckled-granite-tiles_height.png")
            .complete();*/

        MaterialComponent flurMaterial = renderer.materialBuilder()
            .size(1)
            .albedo(0, "Abstract_011_SD/Abstract_011_basecolor.jpg")
            .normal(0, "Abstract_011_SD/Abstract_011_normal.jpg")
            .metallic(0, "Abstract_011_SD/Abstract_011_metallic.jpg")
            .roughness(0, "Abstract_011_SD/Abstract_011_roughness.jpg")
            .ambientOcclusion(0, "Abstract_011_SD/Abstract_011_ambientOcclusion.jpg")
            .height(0, "Abstract_011_SD/Abstract_011_height.png")
            .complete();

        // Обновляем меши в рендерере (применяем загруженные ресурсы)
        renderer.updateMeshes();

        // ========== ШАГ 3: НАСТРОЙКА СИСТЕМ И РЕСУРСОВ ==========

        // Добавляем ресурс времени
        TimeResource timeRes{};
        timeRes.setFPSCap(targetFps);
        timeRes.setScale(0.5f);

        scene.setResource<TimeResource>(timeRes);

        scene.setResource<InputResource>(InputResource{});
        scene.registerSystem<InputSystem>(&scene); // Нужна для обновления состояний окна и ввода

        // Добавляем систему обновления времени
        scene.registerSystem<TimeSystem>(&scene);

        // Регистрируем систему рендеринга (отвечает за отрисовку)
        scene.registerSystem<RenderSystem>(&scene);

        scene.registerSystem<FlyCameraSystem>(&scene);
        scene.registerSystem<LightSwayingSystem>(&scene);

        // Регистрируем нашу кастомную систему вращения

        // ========== ШАГ 4: СОЗДАНИЕ КАМЕРЫ ==========

        // Камера - глаза пользователя в 3D мире
        Entity camera = scene.createEntity();
        Entity libght = scene.createEntity();

        scene.addComponent(libght, PointLightComponent{ {-3.f, 9.5f, 0.f}, {0.5, 1.0f, 0.8f}, 50.f, 20.f });

        // Позиционируем камеру так, чтобы хорошо видеть сцену
        scene.addComponent(camera, TransformComponent{
            {0, 2, 10},     // Камера смотрит на сцену сверху и сзади
            {0, 0, 0},
            {1, 1, 1}
            });

        // Настраиваем параметры камеры
        CameraComponent cameraConfig{};
        cameraConfig.isActive = true;    // Делаем эту камеру активной
        cameraConfig.fovy = 45.0f;       // Угол обзора (поле зрения)
        cameraConfig.zNear = 0.1f;       // Ближняя плоскость отсечения
        cameraConfig.zFar = 100.0f;      // Дальняя плоскость отсечения
        cameraConfig.look = { -90.f, -15.f, 0.0f };

        scene.addComponent(camera, cameraConfig);

        // ========== ШАГ 5: СОЗДАНИЕ ОБЪЕКТОВ СЦЕНЫ ==========

        // Создаем центральную призму
        create3DObject(scene, prismMesh, rustMaterial,
            { 0, 3.5, 3 },     // Позиция в центре
            { 1, 1, 1 });    // Полный размер

        // Создаем меньшую призму справа
        create3DObject(scene, prismMesh, stoneMaterial,
            { 3, 4, 0 },     // Смещена вправо
            { 1.5, 1.5, 1.5 }); // Вдвое меньше

        // Создаем меньшую призму слева  
        create3DObject(scene, planeeMesh, flurMaterial,
            { 0, 0, 0 },    
            { 1, 1, 1 }); 

        // ========== ШАГ 7: ГЛАВНЫЙ ЦИКЛ ПРИЛОЖЕНИЯ ==========
        // Главный цикл - выполняется пока окно не закрыто
        while (!scene.getResource<WindowResource>()->isClose()) {
            // Обновляем сцену (вызываем все системы)
            scene.update();
            // prism::logger::info("FPS:" + std::to_string(scene.getResource<TimeResource>()->getCurrentFPS()));
        }

        // ========== ШАГ 8: КОРРЕКТНОЕ ЗАВЕРШЕНИЕ ==========

        // Очищаем ресурсы рендерера
        renderer.destroy();

        return 0;
    }

}