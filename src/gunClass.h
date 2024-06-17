#include <iostream>

#include <cmath>

#include "SDL.h"
#include "SDL_image.h"

class gun {
    private:
        // rect
        SDL_Rect gunRect;
        // texture
        SDL_Texture* gunTexture;
        // angle
        double gunAngle = 0;
    public:
        // texture
        void setTexture(SDL_Texture* targetTexture) {
            gunTexture = targetTexture;
        }
        SDL_Texture* getTexture() {
            return gunTexture;
        }
        // position and angle
        void setPos(int x, int y) {
            gunRect.x = x;
            gunRect.y = y;
        }
        int getX() {
            return gunRect.x;
        }
        int getY() {
            return gunRect.y;
        }
        void setAngle(double targetAngle) {
            gunAngle = targetAngle;
        }
        double getAngle() {
            return gunAngle;
        }
        // rect
        void setupRect() {
            gunRect.x = 480+5;
            gunRect.y = 270+35;
            gunRect.h = 35;
            gunRect.w = 85;
        }
        void setRect(int targetX, int targetY) {
            gunRect.x = targetX;
            gunRect.y = targetY;
        }
        SDL_Rect getRect() {
            return gunRect;
        }

};