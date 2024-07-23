#pragma once

#include <iostream>
#include <ctime>
// #include <random>

void mySrander() {
    srand(time(NULL));
}

int randInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}