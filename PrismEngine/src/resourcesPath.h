#pragma once
#include <filesystem>

namespace prism {
	namespace PGC {
		// Проверка, является ли путь цветом в формате "color://RRGGBBAA"
		bool isColorPath(const std::filesystem::path& p);

		// Преобразование RGBA в путь вида "color://RRGGBBAA"
		std::filesystem::path colorToPath(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

		// Извлечение RGBA из пути-цвета.
		std::array<unsigned char, 4> pathToColor(const std::filesystem::path& p);
	}
}