#include <iostream>

#include <vector>

#include "SDL.h"
#include "SDL_image.h"

std::vector<bullet*> bulletsVector;

class bullet {
    private:
        // velocity
        int velX;
        int velY;
        // bullet angle
        double angle;
        // position
        SDL_Rect bulletRect;
    public:
        // constructor and destructor
        bullet(int targetVelX, int targetVelY, int targetPosX, int targetPosY, double targetAngle) {
            bulletsVector.push_back(this);
            velX = targetVelX;
            velY = targetVelY;
            bulletRect.x = targetPosX;
            bulletRect.y = targetPosY;
            bulletRect.h = 16;
            bulletRect.w = 9;
            angle = targetAngle;
        }
        ~bullet() {
            bulletsVector.erase(std::find(bulletsVector.begin(), bulletsVector.end(), this));
        }
        // check if not out of the screen
        bool isOnScreen() {
            if(bulletRect.x < 0 || bulletRect.x > 960) {
                return false;
            }
            if(bulletRect.y < 0 || bulletRect.y > 540) {
                return false;
            }
            return true;
        }
        // refresh
        void bulletRefresh() {
            bulletRect.x += velX;
            bulletRect.y += velY;
            if(!isOnScreen()) {
                bullet::~bullet();
            }
        }
        SDL_Rect getRect() {
            return bulletRect;
        }
        double getAngle() {
            return angle;
        }
};
