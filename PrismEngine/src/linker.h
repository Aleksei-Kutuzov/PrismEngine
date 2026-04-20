#pragma once
#include <memory>
#include <typeindex>
#include <utility>
#include <vector>
#include <unordered_map>
namespace prism {
	/**
	 * @class Linker
	 * @brief Типобезопасный менеджер двунаправленных связей между объектами.
	 *
	 * Позволяет связывать произвольные объекты разных типов без создания жёстких
	 * зависимостей, наследования или владения памятью. Каждая связь является
	 * двунаправленной: объект `A` находит `B`, а `B` находит `A`.
	 *
	 * @b Особенности:
	 * - Один объект может иметь связь максимум с одним объектом заданного типа.
	 * - Хранит только сырые указатели. Не продлевает время жизни объектов.
	 * - Все операции поиска выполняются за O(1) в среднем.
	 * - Поддерживает массовое отключение связей (`detach`) для безопасного удаления объектов.
	 *
	 * @warning Не потокобезопасен. При конкурентном вызове `link`/`unlink`/`detach`/`clear`
	 *          из нескольких потоков требуется внешняя синхронизация (например, `std::mutex`).
	 * @warning Использование висячих указателей (объект удалён, но не отвязан) ведёт к UB.
	 *
	 * @example
	 * @code
	 * // Привязка
	 * prism::linker.link(scene_ptr, renderer_ptr);
	 *
	 * // Поиск
	 * auto* r = prism::linker.find<Scene, Renderer>(scene_ptr);
	 * if (r) r->submit(scene_ptr);
	 *
	 * // Удаление одной связи
	 * prism::linker.unlink(scene_ptr, renderer_ptr);
	 * 
	 * // Удаление всех связей при уничтожении объекта
	 * prism::linker.detach(scene_ptr);
	 * @endcode
	 */
	class Linker {
	public:
		Linker() = default;
		~Linker();

		/**
		 * @brief Устанавливает двунаправленную связь между двумя объектами.
		 *
		 * Если хотя бы один из объектов уже имеет связь с целевым типом,
		 * операция игнорируется.
		 *
		 * @tparam A Тип первого объекта
		 * @tparam B Тип второго объекта
		 * @param a Указатель на первый объект (может быть `nullptr`)
		 * @param b Указатель на второй объект (может быть `nullptr`)
		 * @complexity O(1) в среднем
		 */
		template<typename A, typename B>
		void link(A* a, B* b) {
			if (!a || !b) return;

			if (find<A, B>(a) != nullptr || find<B, A>(b) != nullptr) {
				return;
			}

			insert_(a, typeid(B), b);
			insert_(b, typeid(A), a);
		}

		/**
		 * @brief Разрывает конкретную двунаправленную связь между двумя объектами.
		 *
		 * Безопасна даже если связь не существует. Проверяет совпадение указателей
		 * перед удалением, чтобы избежать случайного стирания других записей.
		 *
		 * @tparam A Тип первого объекта
		 * @tparam B Тип второго объекта
		 * @param a Указатель на первый объект
		 * @param b Указатель на второй объект
		 * @complexity O(1) в среднем
		 */
		template<typename A, typename B>
		void unlink(A* a, B* b) {
			if (!a || !b) return;
			erase_(a, typeid(B), b);
			erase_(b, typeid(A), a);
		}

		/**
		 * @brief Мгновенно разрывает ВСЕ связи указанного объекта.
		 *
		 * Идеально подходит для вызова в деструкторах или при выгрузке сцены.
		 * Автоматически находит все привязанные к `obj` объекты любого типа
		 * и удаляет как прямые, так и обратные записи.
		 *
		 * @tparam T Тип объекта, связи которого нужно очистить
		 * @param obj Указатель на объект
		 * @complexity O(N), где N — количество связей у данного объекта
		 */
		template<typename T>
		void detach(T* obj) {
			if (!obj) return;

			std::vector<std::pair<void*, std::type_index>> targets;
			targets.reserve(map_.size() / 2);

			for (auto it = map_.begin(); it != map_.end(); ) {
				if (it->first.ptr == obj) {
					targets.emplace_back(it->second, it->first.target_type);
					it = map_.erase(it);
				}
				else {
					++it;
				}
			}

			for (const auto& p : targets) {
				erase_(p.first, typeid(T), obj);
			}
		}

		/**
		 * @brief Находит объект, связанный с данным экземпляром.
		 *
		 * Возвращает указатель на связанный объект типа `B`, привязанный к `a`.
		 * Если связи нет или `a == nullptr`, возвращает `nullptr`.
		 *
		 * @tparam A Тип исходного объекта
		 * @tparam B Тип искомого объекта
		 * @param a Указатель на исходный объект
		 * @return B* Указатель на связанный объект или nullptr
		 * @complexity O(1) в среднем
		 */
		template<typename A, typename B>
		B* find(A* a) {
			if (!a) return nullptr;

			auto it = map_.find(Key{ a, typeid(B) });
			if (it != map_.end()) {
				return static_cast<B*>(it->second);
			}
			return nullptr;
		}

		/**
		 * @brief Полностью очищает все зарегистрированные связи.
		 * @note Не вызывает деструкторы объектов. Только забывает о связях.
		 * @complexity O(N), где N — общее количество записей в таблице
		 */
		void clear();


	private:
		struct Key {
			void* ptr;
			std::type_index target_type;

			Key(void* p, std::type_index t) : ptr(p), target_type(t) {}

			bool operator==(const Key& other) const {
				return ptr == other.ptr && target_type == other.target_type;
			}
		};

		struct KeyHash {
			std::size_t operator()(const Key& k) const {
				return std::hash<void*>()(k.ptr) ^
					(std::hash<std::type_index>()(k.target_type) << 1);
			}
		};

		std::unordered_map<Key, void*, KeyHash> map_;

		void insert_(void* source, std::type_index target_type, void* target);
		void erase_(void* source, std::type_index target_type, void* expected_target);
	};

	/**
	 * @brief Глобальный экземпляр менеджера связей.
	 *
	 * 
	 * Используется как единая точка доступа для связывания конечных точек движка друг с другом.
	 *
	 * @note Не рекомендуется использовать в конструкторах других глобальных объектов
	 *       из-за неопределённого порядка статической инициализации в C++.
	 */
	extern Linker linker;
}