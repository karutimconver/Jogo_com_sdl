#include <headers/game.hpp>
#include <ctime>

int main(int argc, char* argv[]) {
    srand(std::time(NULL));
    // Jogo
    Game game("Asteroids multiplayer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    game.gameLoop();

    return 0;
}