#pragma once
#include "dataPool.h"

namespace prism {
    namespace scene {
        struct RegisteredPool {
            using DeleterFunc = void(*)(void*);
            std::unique_ptr<void, DeleterFunc> ptr;

            RegisteredPool() noexcept : ptr(nullptr, nullptr) {}

            template<typename Handle>
            DataPool<Handle>* get() const {
                return static_cast<DataPool<Handle>*>(ptr.get());
            }

            template<typename Handle>
            static RegisteredPool make(DataPool<Handle>* p) {
                RegisteredPool result;
                result.ptr = std::unique_ptr<void, DeleterFunc>(
                    static_cast<void*>(p),
                    [](void* p) {
                        delete static_cast<DataPool<Handle>*>(p);
                    }
                );
                return result;
            }
        };

        template<typename T>
        struct is_data_handle : std::false_type {};

        template<typename DataType, typename TagType>
        struct is_data_handle<DataHandle<DataType, TagType>> : std::true_type {};
    }
}