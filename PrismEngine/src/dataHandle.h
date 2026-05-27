#pragma once
#include <cstdint>


namespace prism {
    namespace scene {
        constexpr uint32_t INVALID_DATA_HANDLE = UINT32_MAX;

        /// @brief Хендл на данные в пуле
        /// @tparam DataType Тип хранимых данных (например SubMesh или SubMaterial)
        /// @tparam TagType Уникальный маркер для различения пулов одного типа данных
        template<typename DataType_, typename TagType_>
        struct DataHandle {
            uint32_t id = INVALID_DATA_HANDLE;

            using DataType = DataType_;
            using TagType = TagType_;

            DataHandle() = default;
            explicit DataHandle(uint32_t i) : id(i) {}

            bool isValid() const { return id != INVALID_DATA_HANDLE; }
            explicit operator bool() const { return isValid(); }

            static DataHandle invalid() {
                return DataHandle<DataType, TagType>(INVALID_DATA_HANDLE);
            }

            bool operator==(const DataHandle& other) const { return id == other.id; }
            bool operator!=(const DataHandle& other) const { return id != other.id; }
        };
    }
}