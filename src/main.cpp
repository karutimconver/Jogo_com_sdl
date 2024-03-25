#include <headers/game.hpp>
#include <windows.h>

int main(int argc, char* argv[]) {
    // Jogo
    Game game("Asteroids multiplayer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGH, SDL_WINDOW_SHOWN);

    game.run();

    return 0;
}