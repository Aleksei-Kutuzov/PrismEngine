#pragma once
#include <unordered_map>
#include <set>
#include <typeindex>
#include <memory>
#include <algorithm>
#include <iterator>
#include <vector>
#include "entity.h"
#include "registerPool.h"

namespace prism {
    namespace scene {
        /// @brief Менеджер для управления компонентами сущностей
        /// @details Обеспечивает хранение, добавление, удаление и поиск компонентов
        ///          Компоненты хранятся в плотных массивах (cache-friendly) с использованием
        ///          техники "sparse set" для быстрого доступа. Это обеспечивает отличную
        ///          локальность данных при массовой обработке.
        class ComponentManager
        {
        public:
            ComponentManager() = default;

            /// @brief Добавляет компонент к сущности
            /// @tparam T Тип компонента
            /// @param entityId Идентификатор сущности
            /// @param component Компонент для добавления (может быть lvalue или rvalue)
            /// @return true если компонент успешно добавлен, false в противном случае
            /// @details @details Если компонент у сущности уже существует, он будет заменён.
            ///          Благодаря perfect forwarding избегаются лишние копирования.
            template<typename T>
            bool addComponent(Entity entityId, T&& component) {
               auto& storage = getComponentStorage<std::decay_t<T>>();
				storage.addComponent(entityId, std::forward<T>(component));

                if constexpr (is_data_handle<std::decay<T>>::value) notifyPoolAdded(component);
                return true;
            }

            /// @brief Удаляет компонент у сущности
            /// @tparam T Тип компонента
            /// @param entityId Идентификатор сущности
            /// @return true если компонент существовал и был удален, false в противном случае
            template<typename T>
            bool removeComponent(Entity entityId) {
                if constexpr (is_data_handle<std::decay<T>>::value) {
                    if (auto* component = getComponent<T>(entityId)) notifyPoolRemoved(*component);
                }

                ComponentStorage<T>& storage = getComponentStorage<T>();
				return storage.removeComponent(entityId);
            }

            /// @brief Проверяет, есть ли у сущности компонент типа T
            template<typename T>
            bool hasComponent(Entity entityId) const {
                const ComponentStorage<T>* storage = getComponentStorageConst<T>();
                return storage ? storage->hasComponent(entityId) : false;
            }

            /// @brief Получает указатель на компонент сущности
            /// @tparam T Тип компонента
            /// @param entityId Идентификатор сущности
            /// @return Указатель на компонент или nullptr, если компонент не найден
            template<typename T>
            T* getComponent(Entity entityId) {
                ComponentStorage<T>& storage = getComponentStorage<T>();
				return storage.getComponent(entityId);
            }

            /// @brief Получает все сущности, имеющие компонент указанного типа
            /// @tparam T Тип компонента
            ///  @return Константная ссылка на * *вектор * *сущностей с компонентом.
            ///         Вектор является частью внутреннего хранилища и обладает отличной
            ///         локальностью данных. Время жизни ссылки ограничено временем жизни
            ///         менеджера, но она остаётся валидной при добавлении/удалении других
            ///         сущностей (кроме удаления последней сущности с компонентом T).
            template<typename T>
            const std::vector<Entity>& getEntitiesWith() const {
                static const std::vector<Entity> empty;
                const ComponentStorage<T>* storage = getComponentStorageConst<T>();
                return storage ? storage->entities : empty;
            }

            /// @brief Структура для прямого доступа к внутренним векторам компонентов и сущностей
            /// @details Позволяет эффективно итерировать по компонентам без повторных поисков.
            template<typename T>
            struct StorageView {
                const std::vector<T>& components; ///< Плотный массив компонентов
                const std::vector<Entity>& entities; ///< Соответствующие сущности
            };

            /// @brief Возвращает view на хранилище компонентов типа T
            /// @return StorageView, содержащий ссылки на внутренние векторы.
            ///         Если хранилище не создано, возвращает view с пустыми векторами.
            template<typename T>
            StorageView<T> view() const {
                const auto* storage = getComponentStorageConst<T>();
                if (storage) {
                    return { storage->components, storage->entities };
                }
                else {
                    static const std::vector<T> emptyComp;
                    static const std::vector<Entity> emptyEnt;
                    return { emptyComp, emptyEnt };
                }
            }

            /// @brief Получает все сущности, имеющие все указанные типы компонентов
            /// @tparam ComponentTypes Типы компонентов для поиска
            /// @return Вектор сущностей, содержащих все запрошенные компоненты
            /// @details Выполняет пересечение множеств сущностей для каждого типа компонента
            ///          Порядок сущностей сохраняется из наименьшего вектора-кандидата.
            ///          Вектор не содержит дубликатов.
            template<typename... ComponentTypes>
            std::vector<Entity> getEntitiesWithAll() const {
                if constexpr (sizeof...(ComponentTypes) == 0) return {};
                else {
                    // Собираем векторы сущностей для каждого типа
                    std::vector<const std::vector<Entity>*> entityVectors;
                    (entityVectors.push_back(&getEntitiesWith<ComponentTypes>()), ...);

                    // Выбираем самый маленький вектор для итерации
                    auto smallestIt = std::min_element(entityVectors.begin(), entityVectors.end(),
                        [](const auto* a, const auto* b) { return a->size() < b->size(); });
                    const auto& smallestVec = **smallestIt;

                    std::vector<Entity> result;
                    result.reserve(smallestVec.size());
                    for (Entity e : smallestVec) {
                        if ((hasComponent<ComponentTypes>(e) && ...)) {
                            result.push_back(e);
                        }
                    }
                    return result;
                }
            }

            /// @brief Удаляет все компоненты у сущности
            /// @param entityId Идентификатор сущности
            void removeAllComponents(Entity entityId);

            /// @brief Регистрирует пул данных для типа хендла
            /// @tparam Handle Тип хендла: DataHandle<DataType, TagType>
            /// @details Создаёт и владеет пулом автоматически.
            ///          Повторная регистрация того же TagType игнорируется.
            template<typename Handle>
            void registerDataPool() {
                using Tag = typename Handle::TagType;
                auto typeIdx = std::type_index(typeid(Tag));

                if (dataPools.find(typeIdx) != dataPools.end()) {
                    return;
                }

                auto* pool = new DataPool<Handle>();

                dataPools.try_emplace(typeIdx, RegisteredPool::make(pool));
            }

            template<typename Handle>
            Handle addDataToPool(const typename Handle::DataType* data, uint16_t size) {
                if (DataPool<Handle>* pool = getPool<Handle>()) {
                    return pool->add(data, size);
                }
                return Handle::invalid();
            }

            template<typename Handle, std::size_t N>
            Handle addDataToPool(const std::array<typename Handle::DataType, N>& data) {
                if (DataPool<Handle>* pool = getPool<Handle>()) {
                    return pool->add(data);
                }
                return Handle::invalid();
            }

            /// @brief Получает данные из зарегистрированного пула
            /// @tparam Handle Тип хендла
            /// @param handle Хендл на данные
            /// @param outSize Выходной параметр: размер массива
            template<typename Handle>
            const typename Handle::DataType* getDataFromPool(Handle handle, uint16_t& outSize) const {
                outSize = 0;
                return getPool<Handle>()->get(handle, outSize);
            }

            template<typename Handle>
            void clearDataPool() { 
                getPool<Handle>()->cleanup();
            }

        private:
            /// @brief Базовый интерфейс хранилища компонентов
            struct IComponentStorage {
                virtual ~IComponentStorage() = default;

                /// @brief Удаляет все компоненты сущности из хранилища
                /// @param entityId Идентификатор сущности
                virtual void removeEntity(Entity entityId) = 0;
            };

            /// @brief Конкретная реализация хранилища для типа компонента
            /// @tparam T Тип компонента
            template<typename T>
            struct ComponentStorage : public IComponentStorage {
                /// @brief Плотный массив компонентов
                std::vector<T> components;

                // @brief Сущности, соответствующие компонентам
                std::vector<Entity> entities;

                // @brief Позиция в массивах
                std::unordered_map<Entity, size_t> entityToIndex;

                template<typename U>
                void addComponent(Entity entity, U&& component) {
                    auto it = entityToIndex.find(entity);
                    if (it != entityToIndex.end()) {
                        components[it->second] = std::forward<U>(component);
                        return;
                    }
                    size_t index = components.size();
                    components.push_back(std::forward<U>(component));
                    entities.push_back(entity);
                    entityToIndex[entity] = index;
                }

                bool removeComponent(Entity entity) {
                    auto it = entityToIndex.find(entity);
                    if (it == entityToIndex.end()) return false;

                    size_t index = it->second;
                    size_t lastIndex = components.size() - 1;

                    if (index != lastIndex) {
                        components[index] = std::move(components[lastIndex]);
                        entities[index] = entities[lastIndex];
                        entityToIndex[entities[index]] = index;
                    }

                    components.pop_back();
                    entities.pop_back();
                    entityToIndex.erase(it);
                    return true;
                }

                T* getComponent(Entity entity) {
                    auto it = entityToIndex.find(entity);
                    if (it == entityToIndex.end()) return nullptr;
                    return &components[it->second];
                }

                bool hasComponent(Entity entity) const {
                    return entityToIndex.find(entity) != entityToIndex.end();
                }

                void removeEntity(Entity entityId) override {
                    removeComponent(entityId);
                }
            };

            /// @brief Получает или создаёт хранилище для конкретного типа компонента
            /// @tparam T Тип компонента
            /// @return Ссылка на хранилище компонентов типа T
            template<typename T>
            ComponentStorage<T>& getComponentStorage() {
                auto typeIndex = std::type_index(typeid(T));
                auto it = componentStorages.find(typeIndex);
                if (it == componentStorages.end()) {
                    auto storage = std::make_unique<ComponentStorage<T>>();
                    auto* ptr = storage.get();
                    componentStorages[typeIndex] = std::move(storage);
                    return *ptr;
                }
                return static_cast<ComponentStorage<T>&>(*it->second);
            }

            template<typename T>
            const ComponentStorage<T>* getComponentStorageConst() const {
                auto typeIndex = std::type_index(typeid(T));
                auto it = componentStorages.find(typeIndex);
                if (it == componentStorages.end()) return nullptr;
                return static_cast<const ComponentStorage<T>*>(it->second.get());
            }

            template<typename Handle>
            DataPool<Handle>* getPool() {
                static_assert(is_data_handle<Handle>::value,"Handle must be DataHandle<DataType, TagType>");

                using Tag = typename Handle::TagType;
                auto it = dataPools.find(std::type_index(typeid(Tag)));
                if (it == dataPools.end()) return nullptr;
                return it->second.get<Handle>();
            }

            template<typename Handle>
            const DataPool<Handle>* getPool() const {
                static_assert(is_data_handle<Handle>::value, "Handle must be DataHandle<DataType, TagType>");
                using Tag = typename Handle::TagType;
                auto it = dataPools.find(std::type_index(typeid(Tag)));
                if (it == dataPools.end()) return nullptr;
                return it->second.template get<Handle>();
            }

            // Карта "тип -> хранилище"
            std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> componentStorages;
            std::unordered_map<std::type_index, RegisteredPool> dataPools;
        };
    }
}
