#pragma once
#include "dataPool.h"

namespace prism {
    namespace scene {
        struct RegisteredPool {
            void* ptr = nullptr;

            template<typename Handle>
            DataPool<Handle>* get() const {
                return static_cast<DataPool<Handle>*>(ptr);
            }

            template<typename Handle>
            static RegisteredPool make(DataPool<Handle>* p) {
                return { static_cast<void*>(p) };
            }
        };

        template<typename T>
        struct is_data_handle : std::false_type {};

        template<typename DataType, typename TagType>
        struct is_data_handle<DataHandle<DataType, TagType>> : std::true_type {};
    }
}