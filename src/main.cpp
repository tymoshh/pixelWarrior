
// by tymosh

// todo
// fix 
// fix zombie deletion system ( it crashes the game )
// remake the controls to allow diagonal move and simualtenously move hero ( not neceserarily )
// add zombie sound effect



// iostream
#include <iostream>

// c++ built-in includess
#include <vector>

// sdl stuff
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

// my own headers
#include "tymoshConsole.h"
#include "programStart.h"
#include "angleCalculator.h"
#include "myRandom.h"

#include "towerClass.h"
#include "heroClass.h"
#include "gunClass.h"
#include "bulletClass.h"
#include "zombieClass.h"

// setting namespace
using namespace std;



// speed multiplier
bool debugMode = false;
const int SPEED_MULTIPLIER = 5;



int main(int argc, char* argv[]) {
    // randomize
    mySrander();
    // welcome
    welcomeFunction();
    // startup checker
    startupChecker();

    // fps cap stuff
    const int MAX_FPS = 60;
    const int FRAME_DELAY = 1000 / MAX_FPS;
    Uint32 FRAME_START;
    int FRAME_TIME;
    
    // init sdl end everything about it
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    // sdl window and renderer
    SDL_Window* myWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    SDL_Renderer* myRenderer = SDL_CreateRenderer(myWindow, -1, 0);;
    SDL_Event myEvent;

    // loading textures
    SDL_Texture* backgroundTexture = IMG_LoadTexture(myRenderer, "res/background.png");
    towerNs::towerTexture = IMG_LoadTexture(myRenderer, "res/tower.png");
    heroNs::heroTexture = IMG_LoadTexture(myRenderer, "res/hero.png");
    gunNs::gunTexture = IMG_LoadTexture(myRenderer, "res/AK47.png");
    bulletNs::bulletTexture = IMG_LoadTexture(myRenderer, "res/bullet.png");
    zombieNs::zombieTexture = IMG_LoadTexture(myRenderer, "res/zombie.png");

    // loading fonts
    TTF_Font* myFont = TTF_OpenFont("res/ThaleahFat.ttf", 24);

    // loading sounds
    Mix_Volume(1, 16);      // music
    Mix_Volume(2, 128);     // gun upgrade sounds
    Mix_Volume(3, 32);      // gun shoot sound
    Mix_Chunk* backgroundMusic = Mix_LoadWAV("res/EricSkiff_Underclocked.wav");
    gunNs::upgradeSound = Mix_LoadWAV("res/gunUpgradeSound.wav");
    gunNs::upgradeSoundFail = Mix_LoadWAV("res/gunUpgradeFailSound.wav");
    gunNs::shootSound = Mix_LoadWAV("res/shootSound.wav");

    // set background color to black and clear it
    SDL_RenderClear(myRenderer);

    // share the renderer to the window idk
    SDL_RenderPresent(myRenderer);

    // score
    int gameScore = 0;

    // mouse cords
    int mouseX;
    int mouseY;

    // loop bool
    bool quit = false;

    // main loop bool
    quit = false;

    while(!quit) {

        // fps cap part 1
        FRAME_START = SDL_GetTicks();

        // music
        if (!Mix_Playing(1)) {
            Mix_PlayChannel(1, backgroundMusic, 0);
        }

        // sdl event
        while (SDL_PollEvent(&myEvent)) {
            if (myEvent.type == SDL_QUIT) { // handle closing window
                quit = true;
            } else if (myEvent.type == SDL_KEYDOWN) { // handle keys
                if (myEvent.key.keysym.sym == SDLK_ESCAPE) {
                    // escape = exit
                    quit = true;
                } else if (myEvent.key.keysym.sym == SDLK_BACKQUOTE) { // debug key
                    cout << endl;
                    cout << "[ DEBUG ]" << endl;
                    cout << "gameScore : " << gameScore << endl;
                    cout << "bulletAmount : " << bulletNs::bulletVector.size() << endl;
                    cout << "zombieAmount : " << zombieNs::zombieVector.size() << endl;
                    cout << endl;
                } else if (myEvent.key.keysym.sym == SDLK_w) {
                    // w
                    heroNs::myHero.moveHero(SPEED_MULTIPLIER * 0, SPEED_MULTIPLIER * -1);
                } else if (myEvent.key.keysym.sym == SDLK_a) {
                    // a
                    heroNs::heroRotation = SDL_FLIP_HORIZONTAL;
                    heroNs::myHero.moveHero(SPEED_MULTIPLIER * -1, SPEED_MULTIPLIER * 0);
                } else if (myEvent.key.keysym.sym == SDLK_s) {
                    // s
                    heroNs::myHero.moveHero(SPEED_MULTIPLIER * 0, SPEED_MULTIPLIER * 1);
                } else if (myEvent.key.keysym.sym == SDLK_d) {
                    // d
                    heroNs::heroRotation = SDL_FLIP_NONE;
                    heroNs::myHero.moveHero(SPEED_MULTIPLIER * 1, SPEED_MULTIPLIER * 0);
                } else if (myEvent.key.keysym.sym == SDLK_u) {
                    // u - gun upgrade
                    if (gunNs::myGun.upgradeGun(heroNs::myHero.getBalancePointer())) {
                        tCon.tPrint("gun upgraded", 3);
                        Mix_PlayChannel(2, gunNs::upgradeSound, 0);
                    } else {
                        tCon.tPrint("unsufficient balance to upgrade gun", 3);
                        Mix_PlayChannel(2, gunNs::upgradeSoundFail, 0);
                    }
                }
            } else if (myEvent.type = SDL_MOUSEBUTTONDOWN) {
                if (myEvent.button.button == SDL_BUTTON_LEFT) { // lmb fire
                    angleToVelocity(gunNs::myGun.getAngle(), &bulletNs::tmpBulletVelX, &bulletNs::tmpBulletVelY);
                    bulletNs::bulletClass tempBullet(bulletNs::tmpBulletVelX * SPEED_MULTIPLIER * 2, bulletNs::tmpBulletVelY * SPEED_MULTIPLIER * 2, gunNs::myGun.getX(40), gunNs::myGun.getY(), gunNs::myGun.getAngle(), gunNs::myGun.getPower());
                    bulletNs::bulletVector.push_back(tempBullet);
                    tempBullet.~bulletClass();
                    if (!Mix_Playing(3)) {
                        Mix_PlayChannel(3, gunNs::shootSound, 0);
                    } 
                }
            }
        }

        // zombie spawner
        zombieNs::zombieTickCounter++;
        if (zombieNs::zombieTickCounter == 600) {
            zombieNs::ZOMBIE_SPAWN_CHANCE += 25;
            zombieNs::zombieTickCounter = 0;
            tCon.tPrint("zombie spawn rate increased to : " + to_string(zombieNs::ZOMBIE_SPAWN_CHANCE) + " / 10 000", 3);
        }
        zombieNs::zombieSpawnLoop();

        // clear renderer
        SDL_RenderClear(myRenderer);
        
        // render background
        SDL_RenderCopy(myRenderer, backgroundTexture, NULL, NULL);

        // for every bullet display and refresh position
        for (bulletNs::bulletClass& bulletInstance : bulletNs::bulletVector) {
            SDL_RenderCopyExF(myRenderer, bulletNs::bulletTexture, NULL, bulletInstance.getFRect(), bulletInstance.getAngle(), NULL, SDL_FLIP_NONE);
            if (!bulletInstance.isOnScreen()) {
                bulletNs::bulletsToDelete.push_back(&bulletInstance);
            }
            // refresh bullet position
            bulletInstance.refreshPosition();
            // for every zombie check if it collides with a bullet
            for (zombieNs::zombieClass& zombieInstance : zombieNs::zombieVector) {
                zombieNs::doesCollideWithBullet = SDL_HasIntersectionF(bulletInstance.getFRect(), zombieInstance.getFRect());
                if (zombieNs::doesCollideWithBullet) {
                    bulletNs::bulletsToDelete.push_back(&bulletInstance);
                    zombieInstance.hitZombie(bulletInstance.getPower());
                    break;
                }
            }
        }
        // deleting bullets that are flagged to delete
        for (bulletNs::bulletClass* bulletPtrToDelete : bulletNs::bulletsToDelete) {
            auto deleteIterator = bulletNs::bulletVector.begin() + (bulletPtrToDelete - &bulletNs::bulletVector[0]);
            bulletNs::bulletVector.erase(deleteIterator);
        }
        bulletNs::bulletsToDelete.clear();

        // render tower and stuff about it
        SDL_RenderCopyF(myRenderer, towerNs::towerTexture, NULL, towerNs::myTower.getFRect());
        for (zombieNs::zombieClass& zombieInstance : zombieNs::zombieVector) {
            zombieNs::doesCollideWithTower = SDL_HasIntersectionF(towerNs::myTower.getFRect(), zombieInstance.getFRect());
            if (zombieNs::doesCollideWithTower) {
                towerNs::myTower.hitTower(&debugMode);
            }
        }
        if (towerNs::myTower.isTowerDead()) {
            quit = true;
        }
        // render tower hp
        towerNs::towerHpContent = to_string(int(towerNs::myTower.getHp()));
        towerNs::towerHpRect.w = towerNs::towerHpContent.length() * towerNs::towerHpRect.h;
        towerNs::towerHpSurface = TTF_RenderText_Solid(myFont, towerNs::towerHpContent.c_str(), towerNs::towerHpColor);
        towerNs::towerHpTexture = SDL_CreateTextureFromSurface(myRenderer, towerNs::towerHpSurface);
        SDL_RenderCopy(myRenderer, towerNs::towerHpTexture, NULL, &towerNs::towerHpRect);

        // zombie stuff and rendering
        for (zombieNs::zombieClass& zombieInstance : zombieNs::zombieVector) {
            zombieNs::isZombieDead = zombieInstance.refreshZombie(towerNs::myTower.getX(), towerNs::myTower.getY());
            SDL_RenderCopyExF(myRenderer, zombieNs::zombieTexture, NULL, zombieInstance.getFRect(), 0, NULL, zombieInstance.getFlip());
            if (zombieNs::isZombieDead) {
                zombieNs::zombiesToDelete.push_back(&zombieInstance);
            }
        }
        // deleting zombies that are flagged to delete
        for (zombieNs::zombieClass* zombiePtrToDelete : zombieNs::zombiesToDelete) {
            auto deleteIterator = zombieNs::zombieVector.begin() + (zombiePtrToDelete - &zombieNs::zombieVector[0]);
            zombieNs::zombieVector.erase(deleteIterator);
            heroNs::myHero.addBalance();
            gameScore++;
        }
        zombieNs::zombiesToDelete.clear();

        // hero stuff and 
        SDL_RenderCopyEx(myRenderer, heroNs::heroTexture, NULL, heroNs::myHero.getRect(), 0, NULL, heroNs::heroRotation); 
        heroNs::heroBalContent = "BAL : " + to_string(heroNs::myHero.getBalance());
        heroNs::heroBalRect.w = heroNs::heroBalContent.length() * heroNs::heroBalRect.h;
        heroNs::heroBalSurface = TTF_RenderText_Solid(myFont, heroNs::heroBalContent.c_str(), heroNs::heroBalColor);
        heroNs::heroBalTexture = SDL_CreateTextureFromSurface(myRenderer, heroNs::heroBalSurface);
        SDL_RenderCopy(myRenderer, heroNs::heroBalTexture, NULL, &heroNs::heroBalRect);

        // gun stuff
        SDL_GetMouseState(&mouseX, &mouseY);
        gunNs::myGun.setPos(heroNs::myHero.getX() + 5, heroNs::myHero.getY() + 35);
        gunNs::myGun.setAngle(angleBetweenPoints(gunNs::myGun.getX(), gunNs::myGun.getY(), mouseX, mouseY));
        // rotating gun
        if(gunNs::myGun.getAngle() >= -90 && gunNs::myGun.getAngle() <= 90) {
            SDL_RenderCopyEx(myRenderer, gunNs::gunTexture, NULL, gunNs::myGun.getRect(), gunNs::myGun.getAngle(), NULL, SDL_FLIP_NONE);
        } else {
            SDL_RenderCopyEx(myRenderer, gunNs::gunTexture, NULL, gunNs::myGun.getRect(), gunNs::myGun.getAngle(), NULL, SDL_FLIP_VERTICAL);
        }

        // render present
        SDL_RenderPresent(myRenderer);

        // fps cap part 2
        FRAME_TIME = SDL_GetTicks() - FRAME_START;
        if (FRAME_DELAY > FRAME_TIME) {
            SDL_Delay(FRAME_DELAY - FRAME_TIME);
        }

    }
    
    // while loop end

    // free textures, surfaces, fonts, audios, etc

    // textures
    SDL_DestroyTexture(towerNs::towerTexture);
    SDL_DestroyTexture(heroNs::heroTexture);
    SDL_DestroyTexture(gunNs::gunTexture);
    SDL_DestroyTexture(towerNs::towerTexture);

    // font textures
    SDL_DestroyTexture(towerNs::towerHpTexture);
    SDL_DestroyTexture(heroNs::heroBalTexture);
    
    // font surfaces
    SDL_FreeSurface(towerNs::towerHpSurface);
    SDL_FreeSurface(heroNs::heroBalSurface);

    // fonts
    TTF_CloseFont(myFont);

    // sounds
    Mix_FreeChunk(backgroundMusic);
    Mix_FreeChunk(gunNs::upgradeSound);

    // destroying stuff
    SDL_DestroyRenderer(myRenderer);
    SDL_DestroyWindow(myWindow);

    // quitting everything
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();

    // game end, score, etc
    cout << endl;
    tCon.tPrint("GAME OVER");
    tCon.tPrint("YOUR SCORE : " + std::to_string(gameScore));
    cout << endl;
    tCon.tPause();

    // return 0
    return 0;
}