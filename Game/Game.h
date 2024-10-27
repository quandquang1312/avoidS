#ifndef __GAME_
#define __GAME_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>

#include "../Engine/PhysicsEngine.h"
#include "../Engine/Utils.h"

class Game {
public:
    Game();
    ~Game();
    
    // Initilize, Run
    bool init(const std::string title, const int width, const int height);
    void run();

    // Load texture
    bool loadTexture(const std::string& fifePath);
    bool loadBulletTexture(const std::string& filePath);

    // Score
    float calculateScore();
    bool renderScore();
    
    // Handler
    void handleEvents();
    void handleCharacter();
    void handleBullets();
    void render();
private:
    bool mRunning;

    // Character
    SDL_Texture *characterTexture;
    SDL_Rect characterRect;
    std::string character_image_path;
    int CHARACTER_WIDTH;
    int CHARACTER_HEIGHT;
    float characterPosX;
    float characterPosY;

    int lastMove;

    // Bullet
    SDL_Texture *bulletTexture;
    SDL_Rect bulletRect;
    std::string bullet_image_path;

    // Game
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;

    // Scores
    float m_score;
    // TTF_Font* font; // = TTF_OpenFont("../resources/fonts/Eater-Regular.ttf", 35);

    float MOVE_SPEED;
    Uint32 lastMoveTime;
};

#endif