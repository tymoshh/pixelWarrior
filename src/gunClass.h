#pragma once

#include <iostream>

#include <cmath>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"



namespace gunNs {



// texture
SDL_Texture* gunTexture;

// sounds
Mix_Chunk* shootSound;
Mix_Chunk* upgradeSound;
Mix_Chunk* upgradeSoundFail;

// size
const int GUN_HEIGHT = 35;
const int GUN_WIDTH = 85;



class gunClass {
    private:
        // rect
        SDL_Rect gunRect;
        // angle
        double gunAngle = 0;
        // gun power
        int gunPower = 1;
        int gunUpgradeCost = 64;
    public:
        // ctor or setupper
        gunClass() {
            // position
            gunRect.x = 480;
            gunRect.y = 270;
            // set height and width
            gunRect.h = GUN_HEIGHT;
            gunRect.w = GUN_WIDTH;
            // set texture
        }
        // upgrade gun
        bool upgradeGun(int *buyerBalance) {
            if (*buyerBalance >= gunUpgradeCost) {
                gunPower++;
                *buyerBalance -= gunUpgradeCost;
                gunUpgradeCost = gunUpgradeCost * 2;
                return true;
            } else {
                return false;
            }
        }
        int getPower() {
            return gunPower;
        }
        // osition and angle
        void setPos(int x, int y) {
            gunRect.x = x;
            gunRect.y = y;
        }
        int getX(int xModifier = 0) {
            return gunRect.x + xModifier;
        }
        int getY(int yModifier= 0) {
            return gunRect.y + yModifier;
        }
        void setAngle(double targetAngle) {
            gunAngle = targetAngle;
        }
        double getAngle(double angleModifier = 0) {
            return gunAngle + angleModifier;
        }
        // get rect
        SDL_Rect* getRect() {
            return &gunRect;
        }
};

// initiation
gunClass myGun;

}