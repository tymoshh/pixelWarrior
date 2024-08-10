#pragma once

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

namespace heroNs {



// texture
SDL_Texture* heroTexture;

// size
const int HERO_HEIGHT = 75;
const int HERO_WIDTH = 75;



class heroClass {
    private:
        // rect
        SDL_Rect heroRect;
        // balance
        int heroBalance = 0;
    public:
        // rect or constructor what you like
        heroClass() {
            heroRect.x = 480;
            heroRect.y = 270;
            heroRect.h = HERO_HEIGHT;
            heroRect.w = HERO_WIDTH;
        }
        // position itp
        void moveHero(int targetMoveX, int targetMoveY) {
            heroRect.x += targetMoveX;
            heroRect.y += targetMoveY;
        }
        int getX() {
            return heroRect.x;
        }
        int getY() {
            return heroRect.y;
        }
        // balance
        void addBalance(int targetAddAmount = 1) {
            heroBalance += targetAddAmount;
        }
        int getBalance() {
            return heroBalance;
        }
        int* getBalancePointer() {
            return &heroBalance;
        }
        // get rect
        SDL_Rect* getRect() {
            return &heroRect;
        }
};

// rotation bool
SDL_RendererFlip heroRotation = SDL_FLIP_NONE;

// rendering text
std::string heroBalContent;
SDL_Color heroBalColor = {53, 53, 53, 255};
SDL_Surface* heroBalSurface;
SDL_Texture* heroBalTexture;
SDL_Rect heroBalRect = {40, 40, 0, 32};

// initiation
heroClass myHero;

}
