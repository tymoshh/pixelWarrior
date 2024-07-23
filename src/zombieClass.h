#pragma once

#include <iostream>

#include <vector>

#include "myRandom.h"

#include "SDL.h"
#include "SDL_image.h"

namespace zombieNs {



// texure
SDL_Texture* zombieTexture;

// size
const int ZOMBIE_HEIGHT = 50;
const int ZOMBIE_WIDTH = 36;

// spawn chance
int ZOMBIE_SPAWN_CHANCE = 100;

class zombieClass {
    private:
        // frect
        SDL_FRect zombieFRect;
        // hp
        int zombieHp = 10;
        // sdl flip value
        SDL_RendererFlip zombieFlip = SDL_FLIP_NONE;
    public:
        // ctor or setupper
        zombieClass(int targetPosX) {
            zombieFRect.x = targetPosX;
            zombieFRect.y = 440;
            zombieFRect.h = ZOMBIE_HEIGHT;
            zombieFRect.w = ZOMBIE_WIDTH;
        }
        ~zombieClass() {
            // just destroy
        }
        // move zombie
        bool refreshZombie(float towerPosX, float towerPosY) { // returns true if zombie is dead
            // x
            if (zombieFRect.x < towerPosX) {
                zombieFRect.x += 0.5;
                zombieFlip = SDL_FLIP_NONE;
            } else if (zombieFRect.x > towerPosX) {
                zombieFRect.x -= 0.5;
                zombieFlip = SDL_FLIP_HORIZONTAL;
            }
            // y
            if (zombieFRect.y < towerPosY) {
                zombieFRect.y += 1;
            } else if (zombieFRect.y > towerPosY) {
                zombieFRect.y -= 1;
            }
            // checking if zombie is dead
            if (zombieHp <= 0) {
                return true;
            } else {
                return false;
            }
        }
        // hit zombie with a bullet
        void hitZombie(int hitDamage) {
            zombieHp -= hitDamage;
        }
        // return rect
        SDL_FRect* getFRect() {
            return &zombieFRect;
        }
        // get flip
        SDL_RendererFlip getFlip() {
            return zombieFlip;
        }
    };

// vector that stores all the zombies
std::vector<zombieClass> zombieVector;

// vector that stores indexes of zombies to be deleted
std::vector<int> zombiesToDelete;

// sdl ifs bruh
SDL_bool doesCollideWithBullet;
SDL_bool doesCollideWithTower;

// zombie tick counte
int zombieTickCounter = 0;

// if zombie dead bool
bool isZombieDead;

// iterator, something like i in a for loop
int zombieIterator;

// spawner function
void spawnZombie() {
        int zombieSpawnX = randInt(100, 960 - 100);
        zombieClass tempZombie(zombieSpawnX);
        zombieVector.push_back(tempZombie);
        tempZombie.~zombieClass();
}
// spawn loop
void zombieSpawnLoop() {
    if (randInt(1, 10000) <= ZOMBIE_SPAWN_CHANCE) {
        spawnZombie();
    }
}

}