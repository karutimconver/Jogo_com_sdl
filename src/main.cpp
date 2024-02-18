#include <headers/game.hpp>

int main(int argc, char* argv[]) {

    Game game("Asteroids multiplayer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGH, SDL_WINDOW_SHOWN);

    game.run();


    return 0;
}