#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

class hero {
    private:
        // create rect
        SDL_Rect heroRect;
        // texture
        SDL_Texture* heroTexture;
    public:
        // position itp
        void moveHero(int xMod, int yMod) {
            heroRect.x += xMod;
            heroRect.y += yMod;
        }
        int getX() {
            return heroRect.x;
        }
        int getY() {
            return heroRect.y;
        }
        // texture
        void setTexture(SDL_Texture* targetTexture) {
            heroTexture = targetTexture;
        }
        SDL_Texture* getTexture() {
            return heroTexture;
        }
        // rect
        void setupRect() {
            heroRect.x = 480;
            heroRect.y = 270;
            heroRect.w = 75;
            heroRect.h = 75;
        }
        SDL_Rect getRect() {
            return heroRect;
        }
};

