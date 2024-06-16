#include <iostream>
#include <filesystem>
#include <list>
#include <tymoshConsole.h>

const std::string windowTitle = "pixelWarrior";
const std::list<std::string> authors {"tymosh - https://github.com/tymoshh"};
const std::list<std::string> credits {"sdl2 - https://github.com/libsdl-org", "i learned from - https://www.youtube.com/@TheBuilder"};

// checking some stuff
void startupChecker() {
    if (std::filesystem::exists("SDL2.dll") && std::filesystem::exists("SDL2_image.dll")) {
        if (std::filesystem::exists("res") && std::filesystem::is_directory("res")) {
            tCon.tPrint("basic components check is done", 1);
        } else {
            tCon.tPrint("lack of components (sdl2 dlls and res dir)", 2);
            tCon.tExit();
        }
    } else {
        tCon.tPrint("lack of components (sdl2 dlls and res dir)", 2);
        tCon.tExit();
    }
    std::cout << std::endl;
    tCon.tPause();
}

// welcome function
void welcomeFunction() {
    std::cout << R"(
       _          _ __    __                _            
 _ __ (_)_  _____| / / /\ \ \__ _ _ __ _ __(_) ___  _ __ 
| '_ \| \ \/ / _ \ \ \/  \/ / _` | '__| '__| |/ _ \| '__|
| |_) | |>  <  __/ |\  /\  / (_| | |  | |  | | (_) | |   
| .__/|_/_/\_\___|_| \/  \/ \__,_|_|  |_|  |_|\___/|_|   
|_|                                                      
    )" << std::endl;
    std::cout << std::endl;
    std::cout << "authors : " << std::endl;
    for (std::string author : authors) {
        std::cout << author << std::endl;
    }
    std::cout << std::endl;
    std::cout << "credits : " << std::endl;
    for (std::string credit : credits) {
        std::cout << credit << std::endl;
    }
    std::cout << std::endl;
    tCon.tPause();
}
