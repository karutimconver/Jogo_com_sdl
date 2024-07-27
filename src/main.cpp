#include <headers/game.hpp>
#include <ctime>

Game game("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN + SDL_WINDOW_RESIZABLE);
static int SDLCALL special_event_callback(void *userdata, SDL_Event *event);

int main(int argc, char* argv[]) {
    srand(std::time(NULL));
    // Jogo
    SDL_AddEventWatch(special_event_callback, NULL);
    game.gameLoop();

    return 0;
}


static int SDLCALL special_event_callback(void *userdata, SDL_Event *event) {
    return game.special_event_callback(userdata, event);
};