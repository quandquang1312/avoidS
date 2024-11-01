#include "Game.h"

Game::Game() 
{
    mRunning = false;
    mWindow = nullptr;
    mRenderer = nullptr;
    
    // Character
    characterTexture = nullptr;
    CHARACTER_WIDTH = 50;
    CHARACTER_HEIGHT = 50;
    characterPosX = 100.0f;
    characterPosY = 100.0f;
    characterRect = {100, 100, CHARACTER_WIDTH, CHARACTER_HEIGHT};
    character_image_path = "../resources/img/character.png";

    lastMove = 3; // Right
    lastMoveTime = 0;
    MOVE_SPEED = 1.0f;

    // Bullets
    bulletTexture = nullptr;
    int rdWidth  = Utils::randomInRange(0 + 10, 1200 - 10);
    int rdHeight = Utils::randomInRange(0 + 10, 800 - 10);
    std::cerr << rdWidth << "-" << rdHeight << "\n";
    bulletRect = {200, 200, 20, 20};
    // bulletRect = {rdWidth, rdHeight, 20, 20};
    bullet_image_path = "../resources/img/cut3shjt.png";

    // Score
    m_score = 0.0f;

    // Fonts
    // font = TTF_OpenFont("../resources/fonts/Eater-Regular.ttf", 15);
}

Game::~Game() 
{
}

bool Game::init(const std::string title, const int width, const int height)
{
    // Invokee mRunning
    mRunning = true;

    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF Init failed!\n";
        return false;
    }

    // Create an SDL window
    mWindow = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );

    if (!mWindow) {
        return false;
    }

    // Create an SDL renderer
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        return false;
    }

    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255); // Black

    //  Initilize SDL_Image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Image SDL_Image error!\n";
        return false;
    }

    // Load Character Texture
    if (!loadTexture(character_image_path)) {
        std::cerr << "Load textute error!\n";
        return false;
    }

    // Load bullet texture
    if (!loadBulletTexture(bullet_image_path)) {
        std::cerr << "Load bullet textute error!\n";
        return false;
    }

    return true;
}


void Game::run()
{
    while (mRunning) {
        handleEvents();
        handleCharacter();
        handleBullets();
        renderScore();
        render();
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            mRunning = false;
        }

        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_UP) {
                lastMove = 0;
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                lastMove = 1;
            }
            else if (event.key.keysym.sym == SDLK_LEFT) {
                lastMove = 2;
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                lastMove = 3;
            }
        }
    }
}

void Game::handleCharacter()
{
    // Uint32 currentTime = SDL_GetTicks();
    // if (currentTime - lastMoveTime < 1000 * MOVE_SPEED) {
    //     return;
    // }
    // lastMoveTime = currentTime;
    
    if (lastMove == 0) {
        if (characterPosY > 0)
            characterPosY -= 1.5f;
        else {
            lastMove = 1;
        }
    } else if (lastMove == 1) {
        if (characterPosY + CHARACTER_HEIGHT < WINDOW_HEIGHT)
            characterPosY += 1.5f;
        else {
            lastMove = 0;
        }
    } else if (lastMove == 2) {
        if (characterPosX > 0)
            characterPosX-= 0.2f;
    } else if (lastMove == 3) {
        if (characterPosX + CHARACTER_WIDTH < WINDOW_WIDTH)
            characterPosX += 0.2f;
    }

    characterRect.x = static_cast<int>(characterPosX);
    characterRect.y = static_cast<int>(characterPosY);
}

void Game::handleBullets()
{
    // bulletRect.y += 1;
    // bulletRect.x += 1;

    if (PhysicsEngine::checkCollision(bulletRect, characterRect)) {
        m_score += 2.9f;
        int rdWidth  = Utils::randomInRange(0 + 10, WINDOW_WIDTH - 10);
        int rdHeight = Utils::randomInRange(0 + 10, WINDOW_HEIGHT - 10);
        bulletRect.x = rdWidth;
        bulletRect.y = rdHeight;
    }
}

void Game::render()
{
    // Clear the screen
    // SDL_RenderClear(mRenderer);

    // Render Copy of the character
    if (lastMove == 2 || lastMove  == 3) {
        SDL_RenderCopy(mRenderer, characterTexture, nullptr, &characterRect);
    } else if (lastMove == 1) { // up
        // Rotate
        SDL_Point ctr = {50, 50};
        float angle = 45.0f;
        SDL_RenderCopyEx(mRenderer, characterTexture, nullptr, &characterRect, angle, &ctr, SDL_FLIP_NONE);
    } else if (lastMove == 0) { // down
        // Rotate
        SDL_Point ctr = {50, 50};
        float angle = -45.0f;
        SDL_RenderCopyEx(mRenderer, characterTexture, nullptr, &characterRect, angle, &ctr, SDL_FLIP_NONE);
    }

    // Render Bullet
    SDL_RenderCopy(mRenderer, bulletTexture, nullptr, &bulletRect);

    // Render the screen
    SDL_RenderPresent(mRenderer);
}

float Game::calculateScore()
{
    // distance: target - player
    float m_distance = characterRect.y + characterRect.x;
    return m_score; 
}

bool Game::renderScore()
{
    // Clear the screen
    SDL_RenderClear(mRenderer);
    
    // Get Score
    float score = calculateScore();

    // Init TTF
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
        return false;
    }

    // Score Text
    std::string scoreText = "Score: " + std::to_string(score);

    SDL_Color textColor = {255, 255, 255, 255};

    // font
    TTF_Font* font = TTF_OpenFont("../resources/fonts/Eater-Regular.ttf", 15);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "TextSurface error! " << TTF_GetError() << std::endl;
        return false;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture) {
        std::cerr << "TextTexture error " << TTF_GetError() << std::endl;
        return false;
    }

    SDL_Rect textRect = {10, 10, 100, 30};  // Top-left corner
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

    SDL_RenderCopy(mRenderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    TTF_Quit();
    /*
    */

    return true;
}
    
bool Game::loadTexture(const std::string& filePath)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Surface Error: " << IMG_GetError() << "\n";
        return false;     
    }
    
    characterTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);

    if (!characterTexture) {
        std::cerr << "Character Error!\n";
        return false;
    }

    return true;
}

bool Game::loadBulletTexture(const std::string& filePath)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Surface Error: " << IMG_GetError() << "\n";
        return false;     
    }
    
    bulletTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);

    if (!bulletTexture) {
        std::cerr << "Bullet Error!\n";
        return false;
    }

    return true;
}

