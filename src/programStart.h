#pragma once

// #include <iostream>
#include <filesystem>
#include <list>
#include <tymoshConsole.h>

const std::string windowTitle = "pixelWarrior";
const std::list<std::string> authors {"coder - tymoshh", "second graphic designer - swagrid"};
const std::list<std::string> credits {"sdl2 - https://github.com/libsdl-org", "learned partially from - https://www.youtube.com/@TheBuilder", "huge thanks for fixing bullets - https://github.com/nevemlaci", "eric skiff - background music", "gun upgrade sound - floraphonic on pixabay", "gun failed upgrade sound - pixabay"};

const std::list<std::string> sdlDlls {"SDL2.dll", "SDL2_image.dll", "SDL2_ttf.dll", "SDL2_mixer.dll"};
const std::list<std::string> resourceFiles {"AK47.png", "background.png", "bullet.png", "hero.png", "tower.png", "zombie.png", "EricSkiff_Underclocked.wav", "gunUpgradeSound.wav", "gunUpgradeFailSound.wav", "shootSound.wav"};

// checking some stuff
void startupChecker() {
    // checking for sdl2 dlls
    for (std::string sdlDll : sdlDlls) {
        if (!std::filesystem::exists(sdlDll)) {
            tCon.tPrint("missing dll : " + sdlDll, 2);
            tCon.tExit();
        }
    }
    tCon.tPrint("found all sdl2 dlls", 1);
    // checking if res folder exists
    if (!std::filesystem::exists("res")) {
        tCon.tPrint("missing folder : res", 2);
        tCon.tExit();
    }
    tCon.tPrint("found res folder", 1);
    // checking for resource files
    for (std::string resourceFile : resourceFiles) {
        if (!std::filesystem::exists("res/" + resourceFile)) {
            tCon.tPrint("missing resource file : " + resourceFile, 2);
            tCon.tExit();
        }
    }
    tCon.tPrint("all resources found", 1);
    // end
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
