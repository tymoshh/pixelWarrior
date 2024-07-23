#pragma once

#include <iostream>

#include <vector>

#include "SDL.h"
#include "SDL_image.h"

namespace bulletNs {



// texture
SDL_Texture* bulletTexture;

// size
const float BULLET_HEIGHT = 8.0;
const float BULLET_WIDTH = 16.0;



class bulletClass {
    private:
        // frect
        SDL_FRect bulletFRect;
        // velocity
        float bulletVelX;
        float bulletVelY;
        // bullet angle
        double bulletAngle;
        // power
        int bulletPower;
    public:
        // set up or ctor
        bulletClass(float targetVelX, float targetVelY, int targetPosX, int targetPosY, double targetAngle, int targetPower) {
            // velocity
            bulletVelX = targetVelX;
            bulletVelY = targetVelY;
            // angle
            bulletAngle = targetAngle;
            // frect stuff
            bulletFRect.x = targetPosX;
            bulletFRect.y = targetPosY;
            bulletFRect.h = BULLET_HEIGHT;
            bulletFRect.w = BULLET_WIDTH;
            // power
            bulletPower = targetPower;
            }
        ~bulletClass() {
            // destroy object
        }
        // check if not out of the screen
        bool isOnScreen() {
            if(bulletFRect.x < 0.0 || bulletFRect.x > 960.0) {
                return false;
            }
            if(bulletFRect.y < 0.0 || bulletFRect.y > 540.0) {
                return false;
            }
            return true;
        }
        // refresh
        void refreshPosition() {
            bulletFRect.x += bulletVelX;
            bulletFRect.y += bulletVelY;
        }
        // get power
        int getPower() {
            return bulletPower;   
        }
        // get pointer to the rect
        SDL_FRect* getFRect() {
            return &bulletFRect;
        }
        // get angle
        double getAngle() {
            return bulletAngle;
        }
};

// vector that stores all the bullets
std::vector<bulletClass> bulletVector;

// vector that stores indexes of bullets to be deleted
std::vector<int> bulletsToDelete;

// indexer, something like i in a for loop
int bulletIterator;

// two floats responsible for setting velocity using gun angle
float tmpBulletVelX;
float tmpBulletVelY;

}
