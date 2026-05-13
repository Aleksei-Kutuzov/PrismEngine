#include <string>
#include <cctype>
#include <array>
#include <iomanip>
#include <sstream>
#include "resourcesPath.h"


namespace prism {
    namespace PGC {
        bool isColorPath(const std::filesystem::path& p)
        {
            std::string str = p.generic_string();
            const std::string prefix = "color://";
            if (str.size() != prefix.size() + 8) return false;
            if (str.compare(0, prefix.size(), prefix) != 0) return false;

            for (size_t i = prefix.size(); i < str.size(); ++i) {
                if (!std::isxdigit(static_cast<unsigned char>(str[i]))) return false;
            }
            return true;
        }

        std::filesystem::path colorToPath(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        {
            std::ostringstream oss;
            oss << "color://"
                << std::hex << std::uppercase << std::setfill('0')
                << std::setw(2) << static_cast<int>(r)
                << std::setw(2) << static_cast<int>(g)
                << std::setw(2) << static_cast<int>(b)
                << std::setw(2) << static_cast<int>(a);
            return std::filesystem::path(oss.str());
        }

        std::array<unsigned char, 4> pathToColor(const std::filesystem::path& p)
        {
            static std::array<unsigned char, 4> color{};

            std::string str = p.generic_string();
            const size_t prefix_len = 8;
            const std::string hex = str.substr(prefix_len, 8);

            for (int i = 0; i < 4; ++i) {
                std::string byteStr = hex.substr(i * 2, 2);
                color[i] = static_cast<unsigned char>(std::stoi(byteStr, nullptr, 16));
            }
            return color;
        }

    }
}