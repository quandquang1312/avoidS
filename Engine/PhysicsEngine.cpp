#include "PhysicsEngine.h"

bool PhysicsEngine::checkCollision(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
    if (rectA.x + rectA.w <= rectB.x || rectB.x + rectB.w <= rectA.x ||
        rectA.y + rectA.h <= rectB.y || rectB.y + rectB.h <= rectA.y) {
        return false; // No collision
    }
    return true; // Collision detected
}