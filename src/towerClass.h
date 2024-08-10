#pragma once

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

namespace towerNs {



// texture
SDL_Texture* towerTexture;

// size
const int TOWER_HEIGHT = 75;
const int TOWER_WIDTH = 75;

// position
const int TOWER_X = 480;
const int TOWER_Y = 100;

class towerClass {
    private:
        // frect
        SDL_FRect towerFRect;
        // hp
        float towerHp;
    public:
        // set up or ctor
        towerClass() {
            // frect stuff
            towerFRect.x = TOWER_X;
            towerFRect.y = TOWER_Y;
            towerFRect.h = TOWER_HEIGHT;
            towerFRect.w = TOWER_WIDTH;
            // hp
            towerHp = 100;
        }
        // hit tower
        void hitTower(bool *isDebugMode) {
            if (!(*isDebugMode)) {
                towerHp -= 0.0166666666666667;
            }
        }
        // is tower dead
        bool isTowerDead() {
            if (towerHp <= 0) {
                return true;
            } else {
                return false;
            }
        }
        // get position
        int getX() {
            return towerFRect.x + 30;
        }
        int getY() {
            return towerFRect.y + 50;
        }
        // get frect
        SDL_FRect* getFRect() {
            return &towerFRect;
        }
        // get hp for debug stuff
        float getHp() {
            return towerHp;
        }
    };

// outputting hp and stuff about it
std::string towerHpContent;
SDL_Color towerHpColor = {53, 53, 53, 255};
SDL_Surface* towerHpSurface;
SDL_Texture* towerHpTexture;
SDL_Rect towerHpRect = {TOWER_X, TOWER_Y - 20, 0, 20};

// initialize
towerClass myTower;



}