#pragma once
#include <string>
#include <optional>
#include <vector>
#include <filesystem>
#include <array>
#include "scene.h"
#include "meshComponent.h"
#include "materialComponent.h"
#include "textureStorage.h"
#include "assetSpec.h"

namespace prism {
    namespace render {

        /**
         * @class MaterialBuilder
         * @brief Конструктор материалов с поддержкой цепочечных вызовов (Builder Pattern).
         *
         * Позволяет гибко настраивать PBR-материалы:
         * - Текстуры: Albedo, Normal, Metallic, Roughness, AO, Emission, Height
         * - Скалярные множители для каждого канала
         * - Поддержку нескольких субматериалов (для много-подмешевых объектов)
         * - Глобальные модификаторы, применяемые ко всем субматериалам
         * - Загрузку сплошных цветов через std::array<unsigned char, 4>
         *
         * @par Поддерживаемые форматы:
         * - Обычные пути: `"textures/brick_albedo.png"`
         * - Прямая передача цвета: `albedo(0, {95, 23, 243, 255})`
         *
         * @par Пример использования:
         * @code
         * auto material = renderer.materialBuilder()
         *     .forMesh(meshComponent)
         *     .albedo(0, "textures/brick_albedo.png")
         *     .normal(0, "textures/brick_normal.png")
         *     .metallic(0, 0.8f)
         *     .roughness(0, 0.4f)
         *     .emission(1, {255, 112, 52})       // Оранжевое свечение без файла
         *     .height(0, 0.5f)                   // Параллакс-смещение
         *     .complete();
         * @endcode
         *
         * @note Все скалярные значения автоматически ограничиваются диапазоном [0.0; 1.0]
         * @note Глобальные скаляры умножаются на локальные при финализации через complete()
         * @see MaterialComponent, TextureStorage, Renderer::materialBuilder()
         */
        struct MaterialBuilder {

            /**
             * @struct MaterialData
             * @brief Внутреннее описание параметров одного субматериала.
             *
             * Хранит пути к текстурам и скалярные множители для PBR-каналов.
             * Используется только внутри MaterialBuilder.
             */
            struct MaterialData {
                std::optional<assets::AssetSpec> albedo;    ///< @brief Спецификация текстуры альбедо (базовый цвет, sRGB)
                std::optional<assets::AssetSpec> normal;    ///< @brief Спецификация к карте нормалей (линейное пространство)
                std::optional<assets::AssetSpec> metallic;  ///< @brief Спецификация к карте металличности (одноканальная, линейная)
                std::optional<assets::AssetSpec> roughness; ///< @brief Спецификация к карте шероховатости (одноканальная, линейная)
                std::optional<assets::AssetSpec> ambient;   ///< @brief Спецификация к карте Ambient Occlusion (одноканальная)
                std::optional<assets::AssetSpec> emission;  ///< @brief Спецификация к карте эмиссии (sRGB, HDR-значения возможны)
                std::optional<assets::AssetSpec> height;    ///< @brief Спецификация к карте высоты (для паралакс-маппинга/тесселяции)

                float metallicScalar = 1.0f;   ///< @brief Множитель металличности [0.0–1.0] для данного субматериала
                float roughnessScalar = 1.0f;  ///< @brief Множитель шероховатости [0.0–1.0] для данного субматериала
                float ambientScalar = 1.0f;    ///< @brief Множитель AO [0.0–1.0] для данного субматериала
                float emissionScalar = 1.0f;   ///< @brief Множитель интенсивности эмиссии [0.0–1.0] для данного субматериала
                float heightScalar = 1.0f;     ///< @brief Множитель высоты [0.0–1.0] для данного субматериала
            };

            /// @name Внутреннее состояние
            /// @{
            std::vector<MaterialData> materialsData; ///< Массив данных по субматериалам (индексируется по ID)
            /// @}

            /// @name Глобальные модификаторы (применяются ко всем субматериалам)
            /// @{
            float globalMetallicScalar = 1.0f;    ///< @brief Глобальный множитель металличности [0.0–1.0]
            float globalRoughnessScalar = 1.0f;   ///< @brief Глобальный множитель шероховатости [0.0–1.0]
            float globalEmissionScalar = 1.0f;    ///< @brief Глобальный множитель эмиссии [0.0–1.0]
            float globalAmbientScalar = 1.0f;     ///< @brief Глобальный множитель Ambient Occlusion [0.0–1.0]
            float globalHeightScalar = 1.0f;      ///< @brief Глобальный множитель высоты [0.0–1.0]
            /// @}

            /// @name Зависимости
            /// @{
            prism::scene::Scene& scene;              ///< @brief Ссылка на сцену для управления пулом компонентов
            prism::PGC::L1::TextureStorage& storage; ///< @brief Ссылка на хранилище текстур для загрузки/кэширования
            /// @}

            /**
             * @brief Конструктор MaterialBuilder.
             *
             * @warning Не создавайте экземпляр напрямую — используйте Renderer::materialBuilder()
             * @param scene Ссылка на активную сцену.
             * @param storage Ссылка на менеджер текстур.
             */
            MaterialBuilder(prism::scene::Scene& scene, prism::PGC::L1::TextureStorage& storage);

            /// @name Настройка структуры материала
            /// @{

            /**
             * @brief Устанавливает количество субматериалов.
             *
             * Вызывается автоматически при использовании forMesh(), но может быть задан явно
             * для материалов, не привязанных к конкретному мешу.
             *
             * @param size Количество субматериалов (должно быть > 0).
             * @return Ссылка на текущий объект для цепочечных вызовов.
             * @warning Перезаписывает существующие данные при уменьшении размера.
             */
            MaterialBuilder& size(uint16_t size);

            /**
             * @brief Автоматически определяет количество субматериалов по данным меша.
             *
             * Извлекает количество материалов из MeshComponent через Scene::getDataFromPool()
             * и вызывает size() для подготовки билдера к настройке соответствующего числа субматериалов.
             *
             * @param mesh Ссылка на компонент меша, к которому применяется материал.
             * @return Ссылка на текущий объект для цепочечных вызовов.
             * @note Принимает ссылку для избежания копирования компонента.
             * @see MeshComponent, Scene::getDataFromPool()
             */
            MaterialBuilder& forMesh(prism::scene::MeshComponent& mesh);

            /**
             * @brief Автоматически определяет количество субматериалов по сущности (Entity).
             *
             * Удобная перегрузка для работы с системой сущностей: автоматически извлекает
             * MeshComponent из указанной сущности и делегирует вызов forMesh(MeshComponent&).
             *
             * @param entity Сущность, содержащая компонент MeshComponent.
             * @return Ссылка на текущий объект для цепочечных вызовов.
             * @warning Убедитесь, что сущность действительно имеет компонент MeshComponent,
             *          иначе поведение неопределено.
             * @see Scene::getComponent(), forMesh(prism::scene::MeshComponent&)
             */
            MaterialBuilder& forMesh(prism::scene::Entity entity);

            /// @}

            /// @}

            /// @name Копирование данных из существующих материалов
            /// @{

            /**
             * @brief Полностью копирует параметры всех субматериалов из другого материала.
             *
             * Копирует пути к текстурам и значения скаляров для каждого субматериала.
             * Глобальные модификаторы текущего билдера не изменяются.
             *
             * @param material Исходный MaterialComponent для копирования.
             * @return Ссылка на текущий объект для цепочечных вызовов.
             * @warning Требуется, чтобы размеры материалов совпадали (или был вызван size()/forMesh() заранее).
             */
            MaterialBuilder& copyAll(prism::scene::MaterialComponent material);

            /**
             * @brief Копирует параметры одного конкретного субматериала.
             *
             * @param material Исходный MaterialComponent.
             * @param subMaterialId Индекс субматериала в исходном материале.
             * @return Ссылка на текущий объект для цепочечных вызовов.
             * @warning Убедитесь, что текущий билдер имеет достаточный размер (size() >= subMaterialId + 1).
             */
            MaterialBuilder& copy(prism::scene::MaterialComponent material, uint16_t subMaterialId);

            /// @}

            /// @name Настройка текстур
            /// @{

            /**
             * @brief Устанавливает текстуру альбедо для субматериала.
             * @param subMaterialId Индекс субматериала (0-based).
             * @param filename Путь к файлу текстуры.
             * @return Ссылка на текущий объект для цепочечных вызовов.
             * @note Текстура будет загружена в хранилище при вызове complete().
             * @see albedo(uint16_t, std::array<unsigned char, 4>)
             */
            MaterialBuilder& albedo(uint16_t subMaterialId, std::filesystem::path filename);

            /**
             * @brief Устанавливает сплошной цвет альбедо через RGBA-массив.
             * @param subMaterialId Индекс субматериала.
             * @param rgba Массив из 4 байт {R, G, B, A} в диапазоне [0–255].
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& albedo(uint16_t subMaterialId, std::array<unsigned char, 4> rgba);

            /**
             * @brief Устанавливает карту нормалей для субматериала.
             * @param subMaterialId Индекс субматериала.
             * @param filename Путь к файлу текстуры.
             * @return Ссылка на текущий объект.
             * @note Ожидается текстура в формате нормалей (tangent space, DirectX-конвенция).
             */
            MaterialBuilder& normal(uint16_t subMaterialId, std::filesystem::path filename);

            /**
             * @brief Устанавливает сплошной цвет для карты нормалей (редко используется).
             * @param subMaterialId Индекс субматериала.
             * @param rgba Массив {R, G, B, A}, обычно {128, 128, 255, 255} для "нейтральной" нормали.
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& normal(uint16_t subMaterialId, std::array<unsigned char, 4> rgba);

            /**
             * @brief Устанавливает комбинированную MRAO-текстуру для субматериала.
             *
             * MRAO = Metallic (R), Roughness (G), Ambient Occlusion (B).
             * Один вызов устанавливает пути для трёх каналов одновременно.
             *
             * @param subMaterialId Индекс субматериала.
             * @param filename Путь к MRAO-текстуре.
             * @return Ссылка на текущий объект.
             * @note Если нужны отдельные текстуры — используйте metallic()/roughness()/ambientOcclusion() раздельно.
             * @see metallic(), roughness(), ambientOcclusion()
             */
            MaterialBuilder& mrao(uint16_t subMaterialId, std::filesystem::path filename);

            /**
             * @brief Устанавливает сплошной цвет для MRAO-текстуры.
             * @param subMaterialId Индекс субматериала.
             * @param rgba Массив {Metallic, Roughness, AO, unused}.
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& mrao(uint16_t subMaterialId, std::array<unsigned char, 4> rgba);

            /**
             * @brief Устанавливает комбинированную MRAOH-текстуру (Metallic, Roughness, AO, Height).
             *
             * MRAOH = Metallic (R), Roughness (G), Ambient Occlusion (B), Height (A).
             * Один вызов устанавливает пути для четырёх каналов одновременно.
             *
             * @param subMaterialId Индекс субматериала.
             * @param filename Путь к MRAOH-текстуре.
             * @return Ссылка на текущий объект.
             * @note Эквивалентно последовательному вызову mrao() + height() с одним файлом.
             */
            MaterialBuilder& mraoh(uint16_t subMaterialId, std::filesystem::path filename);

            /**
             * @brief Устанавливает сплошной цвет для MRAOH-текстуры.
             * @param subMaterialId Индекс субматериала.
             * @param rgba Массив {Metallic, Roughness, AO, Height}.
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& mraoh(uint16_t subMaterialId, std::array<unsigned char, 4> rgba);

            /// @}

            /// @name Настройка металличности (Metallic)
            /// @{

            /**
             * @brief Устанавливает текстуру металличности для субматериала.
             * @param subMaterialId Индекс субматериала.
             * @param filename Путь к одноканальной текстуре.
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& metallic(uint16_t subMaterialId, std::filesystem::path filename);

            /**
             * @brief Устанавливает скалярное значение металличности для субматериала.
             * @param subMaterialId Индекс субматериала.
             * @param metallic Значение в диапазоне [0.0–1.0] (0 = диэлектрик, 1 = металл).
             * @return Ссылка на текущий объект.
             * @note Значение будет ограничено std::clamp(0.0, 1.0) при финализации.
             */
            MaterialBuilder& metallic(uint16_t subMaterialId, float metallic);

            /**
             * @brief Устанавливает глобальное значение металличности для всех субматериалов.
             * @param metallic Глобальный множитель [0.0–1.0].
             * @return Ссылка на текущий объект.
             * @note Умножается на локальные значения при вызове complete().
             */
            MaterialBuilder& metallic(float metallic);

            /// @}

            /// @name Настройка шероховатости (Roughness)
            /// @{

            /**
             * @brief Устанавливает текстуру шероховатости для субматериала.
             * @param subMaterialId Индекс субматериала.
             * @param filename Путь к одноканальной текстуре.
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& roughness(uint16_t subMaterialId, std::filesystem::path filename);

            /**
             * @brief Устанавливает скалярное значение шероховатости для субматериала.
             * @param subMaterialId Индекс субматериала.
             * @param roughness Значение в диапазоне [0.0–1.0] (0 = зеркальная, 1 = матовая).
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& roughness(uint16_t subMaterialId, float roughness);

            /**
             * @brief Устанавливает глобальное значение шероховатости для всех субматериалов.
             * @param roughness Глобальный множитель [0.0–1.0].
             * @return Ссылка на текущий объект.
             * @note Умножается на локальные значения при вызове complete().
             */
            MaterialBuilder& roughness(float roughness);

            /// @}

            /// @name Настройка Ambient Occlusion (AO)
            /// @{

            /**
             * @brief Устанавливает текстуру Ambient Occlusion для субматериала.
             * @param subMaterialId Индекс субматериала.
             * @param filename Путь к одноканальной AO-текстуре.
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& ambientOcclusion(uint16_t subMaterialId, std::filesystem::path filename);

            /**
             * @brief Устанавливает скалярное значение АО для субматериала.
             * @param subMaterialId Индекс субматериала.
             * @param ambient Множитель интенсивности затенения [0.0–1.0].
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& ambientOcclusion(uint16_t subMaterialId, float ambient);

            /**
             * @brief Устанавливает глобальное значение АО для всех субматериалов.
             * @param ambient Глобальный множитель [0.0–1.0].
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& ambientOcclusion(float ambient);

            /// @}

            /// @name Настройка эмиссии (Emission)
            /// @{

            /**
             * @brief Устанавливает текстуру эмиссии для субматериала.
             * @param subMaterialId Индекс субматериала.
             * @param filename Путь к текстуре свечения.
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& emission(uint16_t subMaterialId, std::filesystem::path filename);

            /**
             * @brief Устанавливает сплошной цвет эмиссии через RGBA-массив.
             * @param subMaterialId Индекс субматериала.
             * @param rgba Массив {R, G, B, A}, где RGB задаёт цвет свечения.
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& emission(uint16_t subMaterialId, std::array<unsigned char, 4> rgba);

            /**
             * @brief Устанавливает скалярную интенсивность эмиссии для субматериала.
             * @param subMaterialId Индекс субматериала.
             * @param emission Множитель яркости [0.0–1.0].
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& emission(uint16_t subMaterialId, float emission);

            /**
             * @brief Устанавливает глобальную интенсивность эмиссии для всех субматериалов.
             * @param emission Глобальный множитель [0.0–1.0].
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& emission(float emission);

            /// @}

            /// @name Настройка высоты (Height/Displacement)
            /// @{

            /**
             * @brief Устанавливает текстуру высоты для субматериала.
             *
             * Используется для паралакс-маппинга, тесселяции или дисплейсмент-маппинга.
             *
             * @param subMaterialId Индекс субматериала.
             * @param filename Путь к одноканальной высоте-текстуре.
             * @return Ссылка на текущий объект.
             * @note Значения высоты обычно интерпретируются как: 0 = минимум, 255 = максимум смещения.
             */
            MaterialBuilder& height(uint16_t subMaterialId, std::filesystem::path filename);

            /**
             * @brief Устанавливает скалярное значение высоты для субматериала.
             * @param subMaterialId Индекс субматериала.
             * @param height Множитель высоты [0.0–1.0] (0 = нет смещения, 1 = полное смещение).
             * @return Ссылка на текущий объект.
             */
            MaterialBuilder& height(uint16_t subMaterialId, float height);

            /**
             * @brief Устанавливает глобальное значение высоты для всех субматериалов.
             * @param height Глобальный множитель [0.0–1.0].
             * @return Ссылка на текущий объект.
             * @note Умножается на локальные значения при вызове complete().
             */
            MaterialBuilder& height(float height);

            /// @}

            /**
             * @brief Финализирует настройку и создаёт MaterialComponent.
             *
             * Выполняет:
             * 1. Загрузку всех указанных текстур/цветов через TextureStorage
             * 2. Применение глобальных и локальных скаляров (с std::clamp[0.0; 1.0])
             * 3. Обновление кэша хранилища текстур (storage.update())
             * 4. Добавление готового материала в пул компонентов сцены
             *
             * @return Созданный MaterialComponent, готовый к назначению на рендер-объекты.
             * @warning После вызова complete() билдер можно повторно использовать,
             *          но предыдущие настройки будут сброшены при новых вызовах сеттеров.
             * @see MaterialComponent, TextureStorage::update(), PGC::colorToPath()
             */
            prism::scene::MaterialComponent complete();
        };

    } // namespace render
} // namespace prism