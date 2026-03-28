#include <iostream>
#include <string>
#include "examples.h"


int main(int argc, char* argv[]) {
    int targetFps = 60;
    // Если есть аргумент командной строки, используем его
    if (argc > 2) {
        targetFps = atoi(argv[2]);
    }

    if (argc > 1) {
        std::string demoName = argv[1];
        if (demoName == "spinningPrismDemo") {
            return spinningPrism::spinningPrismDemo(targetFps);
        }
        else if (demoName == "dancingNeonCubesDemo") {
            return dancingNeonCubes::dancingNeonCubesDemo(targetFps);
        }
        else if (demoName == "solarSystemDemo") {
            return solarSystem::solarSystemDemo(targetFps);
        }
        else if (demoName == "materialsDemo") {
            return materials::materialsDemo(targetFps);
        }
        else {
            std::cout << "Unknown demo: " << demoName << std::endl;
            return 1;
        }
    }
    
    
    // Иначе спросим пользователя
    std::cout << "Select demo (1 or 2, 3, 4): ";
    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        return spinningPrism::spinningPrismDemo(targetFps);
    case 2:
        return dancingNeonCubes::dancingNeonCubesDemo(targetFps);
    case 3:
        return solarSystem::solarSystemDemo(targetFps);
    case 4:
        return materials::materialsDemo(targetFps);
    default:
        std::cout << "Invalid choice." << std::endl;
        return 1;
    }
}