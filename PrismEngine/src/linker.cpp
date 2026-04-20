#include "linker.h"

void prism::Linker::clear() {
	map_.clear();
}

void prism::Linker::insert_(void* source, std::type_index target_type, void* target)
{
	map_[Key{ source, target_type }] = target;
}

void prism::Linker::erase_(void* source, std::type_index target_type, void* expected_target)
{
	auto it = map_.find(Key{ source, target_type });
	if (it != map_.end() && it->second == expected_target) {
		map_.erase(it);
	}
}

prism::Linker::~Linker()
{
	clear();
}

namespace prism {
	Linker linker;
}