#ifndef __PHYSICS_ENGINE_
#define __PHYSICS_ENGINE_

#include <SDL2/SDL.h>

class PhysicsEngine {
public:
    static bool checkCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
private:
};

#endif