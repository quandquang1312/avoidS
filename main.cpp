#include "Game/Game.h" 

int main() {
    Game gameInstance;

    if (gameInstance.init("AvoidS", 1200, 800)) {
        gameInstance.run();
    } else {
        std::cerr << "Game itnitialized error!\n";
    }

    return 0;
}

