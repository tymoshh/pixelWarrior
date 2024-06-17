#pragma once

#include <iostream>

class ansiCodes {
    public:
        // reset
        const std::string reset = "\033[0m";
        // bolds
        const std::string red_bold = "\033[1m\033[31m";
        const std::string green_bold = "\033[1m\033[32m";
        const std::string blue_bold = "\033[1m\033[034m";
};
ansiCodes tAnsi;

class tymoshConsole {
    public:
        void tPause() {
            std::cout << "press enter to continue ..." << std::endl;
            std::cin.ignore();
        }
        void tExit() {
            std::cout << std::endl;
            tPause();
            exit(0);
        }
        void tPrint(const std::string msg, const int type = 0, const bool doEndl = true) {
            std::string header = "";
            switch(type) {
                case 1: // 1 : check
                    header = tAnsi.green_bold + "check" + tAnsi.reset + " : ";
                    break;
                case 2: // 2 : error
                    header = tAnsi.red_bold + "error" + tAnsi.reset + " : ";
                    break;
                case 3: // 3 : info
                    header = tAnsi.blue_bold + "info" + tAnsi.reset + " : ";
                    break;
            }
            // doEndl true or false
            if (doEndl) {
                std::cout << "[ " << "CONSOLE" << " ] " << header << msg << std::endl;
            } else {
                std::cout << "[ " << "CONSOLE" << " ] " << header << msg;
            }
        }
};
tymoshConsole tCon;