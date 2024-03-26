#include <headers/game.hpp>

// ------------------------------
// | Construtor e Inicializador |
// ------------------------------

Game::Game(const char* title, int x, int y, int w, int h, Uint32 flags) {
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow(title, x, y, w, h, flags);
    _renderer = SDL_CreateRenderer(_window, -1, 0);
};

void Game::run() {
    int player1_keys [4] = {SDL_SCANCODE_D, SDL_SCANCODE_A, SDL_SCANCODE_W, SDL_SCANCODE_SPACE};
    player1 = new Ship(3, SCREEN_WIDTH / 2, SCREEN_HEIGH / 2, player1_keys);

    asteroids.push_back(new Asteroid(50, 50, 4));
    asteroids.push_back(new Asteroid(100, 50, 1));
    asteroids.push_back(new Asteroid(50, 100, 1));
    asteroids.push_back(new Asteroid(250, 200, 2));
    asteroids.push_back(new Asteroid(200, 100, 2));
    
    gameLoop();
}

// -----------------
// | Ciclo de jogo |
// -----------------

void Game::gameLoop() {
    while (gameState != GameState::EXIT) {
        Uint64 start = SDL_GetPerformanceCounter();
        
        handleEvents();
        
        if (gameState == GameState::RUNNING) {
            const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
            player1->update(keyboard_state, &lasers);

            for (Asteroid* asteroid : asteroids) {
                asteroid->update();
            }
            
            for (Laser* laser : lasers) {
                laser->update();
            }
        }

        Uint64 end = SDL_GetPerformanceCounter();
        dt = (end - start) / SDL_GetPerformanceFrequency();
        draw();
        SDL_Delay(1000/120-dt);
    }
}

void Game::draw() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    // Mandar para aqui os desenhos

    player1->draw(_renderer);
    
    for (Asteroid* asteroid : asteroids) {
        asteroid->draw(_renderer);
    }

    for (Laser* laser : lasers) {
        laser->draw(_renderer);
    }

    // Fim dos desenhos
    // A renderizar
    SDL_RenderPresent(_renderer);
}

// -----------------
// | SDL Callbacks |
// -----------------

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            gameState = GameState::EXIT;
            break;
    }
}
