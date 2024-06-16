#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "tymoshConsole.h"
#include "programStart.h"
#include "heroClass.h"

using namespace std;



// window title
// already declared in programstart

// speed multiplier
const int SPEED_MULTIPLIER = 5;

// screen size
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;

// fps cap
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;
Uint32 FRAME_START;
int FRAME_TIME;


int main(int argc, char* argv[]) {
    // welcome
    welcomeFunction();
    // startup checker
    startupChecker();
    
    // init sdl
    SDL_Init(SDL_INIT_EVERYTHING);

    // sdl window and renderer
    SDL_Window* myWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* myRenderer = SDL_CreateRenderer(myWindow, -1, 0);;
    SDL_Event myEvent;

    // start my hero
    hero myHero;
    myHero.setRect();
    
    // loading textures
    SDL_Texture* heroLeft = IMG_LoadTexture(myRenderer, "res/heroLeft.png");
    SDL_Texture* heroRight = IMG_LoadTexture(myRenderer, "res/heroRight.png");
    SDL_Texture* backgroundTexture = IMG_LoadTexture(myRenderer, "res/background.png");

    // set background color to black and clear it
    SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);
    SDL_RenderClear(myRenderer);

    // share the renderer to the window idk
    SDL_RenderPresent(myRenderer);

    char heroRotation = ' ';
    bool quit = false;

    while(!quit) {
        // fps cap part 1
        FRAME_START = SDL_GetTicks();

        // sdl event
        while(SDL_PollEvent(&myEvent)) {
            if(myEvent.type == SDL_QUIT) { // handle closing window
                quit = true;
            }
            else if(myEvent.type == SDL_KEYDOWN) { // handle keys
                // w
                if(myEvent.key.keysym.sym == SDLK_w) {
                    myHero.moveHero(SPEED_MULTIPLIER * 0, SPEED_MULTIPLIER * -1);
                }
                // a
                if(myEvent.key.keysym.sym == SDLK_a) {
                    if(heroRotation != 'a') {
                        myHero.setTexture(heroLeft);
                        heroRotation = 'a';
                    }
                    myHero.moveHero(SPEED_MULTIPLIER * -1, SPEED_MULTIPLIER * 0);
                }
                // s
                if(myEvent.key.keysym.sym == SDLK_s) {
                    myHero.moveHero(SPEED_MULTIPLIER * 0, SPEED_MULTIPLIER * 1);
                }
                // d
                if(myEvent.key.keysym.sym == SDLK_d) {
                    if(heroRotation != 'd') {
                        myHero.setTexture(heroRight);
                        heroRotation = 'd';
                    }
                    myHero.moveHero(SPEED_MULTIPLIER * 1, SPEED_MULTIPLIER * 0);
                }
            }
        }

        SDL_RenderClear(myRenderer);
        
        SDL_Rect tmpHeroRect = myHero.getRect(); 
        SDL_RenderCopy(myRenderer, backgroundTexture, NULL, NULL);
        SDL_RenderCopy(myRenderer, myHero.getTexture(), NULL, &tmpHeroRect);

        SDL_RenderPresent(myRenderer);

        // printing hero cords
        // cout << myHero.getX() << " " << myHero.getY() << endl;

        // fps cap part 2
        FRAME_TIME = SDL_GetTicks() - FRAME_START;
        if (FRAME_DELAY > FRAME_TIME) {
            SDL_Delay(FRAME_DELAY - FRAME_TIME);
        }

    }

    return 0;
}