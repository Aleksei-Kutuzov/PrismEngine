#pragma once
#include <stack>


namespace prism {
	namespace utils {
		template<typename IdType, IdType FirstId, IdType InvalidId>
		class IdPool
		{
		public:
			IdType newId();
			void delId(IdType id);

		private:
			
			IdType nextId = FirstId;
			std::stack<IdType> freeIds;
		};
		template<typename IdType, IdType FirstId, IdType InvalidId>
		inline IdType IdPool<IdType, FirstId, InvalidId>::newId()
		{
			if constexpr (InvalidId < FirstId) {
				if (freeIds.empty()) return nextId++;
				IdType r = freeIds.top();
				freeIds.pop();
				return r;
			} else {
				if (freeIds.empty()) {
					if (nextId == InvalidId) nextId++;
					return nextId++;
				};
				IdType r = freeIds.top();
				freeIds.pop();
				return r;
			}
			
		}
		template<typename IdType, IdType FirstId, IdType InvalidId>
		inline void IdPool<IdType, FirstId, InvalidId>::delId(IdType id)
		{
			if (id != InvalidId) freeIds.push(id);
		}
	}
}