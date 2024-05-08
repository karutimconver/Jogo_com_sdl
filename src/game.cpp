#include <headers/game.hpp>

// ------------------------------
// | Construtor e Inicializador |
// ------------------------------

Game::Game(const char* title, int x, int y, int w, int h, Uint32 flags) {
    SDL_Init(SDL_INIT_EVERYTHING);

    TTF_Init();

    _window = SDL_CreateWindow(title, x, y, w, h, flags);
    _renderer = SDL_CreateRenderer(_window, -1, 0);

    // Criar Menu
    Text main_title("Asteroids", SCREEN_WIDTH / 2, SCREEN_HEIGH / 3, 24, _renderer);
    Text single_player("press 1 single player", SCREEN_WIDTH / 2, SCREEN_HEIGH / 2, 16, _renderer);
    Text multiplayer("press 2 for multiplayer", SCREEN_WIDTH / 2, SCREEN_HEIGH * 2 / 3, 16, _renderer);

    menu_text.push_back(main_title);
    menu_text.push_back(single_player);
    menu_text.push_back(multiplayer);
};

void Game::run(int n) {
    // A criar jogadores
    int distance_from_the_center = 200;    // distancia da nave ao centro da tela
    int player1_keys [4] = {SDL_SCANCODE_D, SDL_SCANCODE_A, SDL_SCANCODE_W, SDL_SCANCODE_SPACE};
    int player2_keys [4] = {SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT, SDL_SCANCODE_UP, SDL_SCANCODE_RCTRL};
    
    switch (n) {
        case 1:
            ships.push_back(new Ship(3, SCREEN_WIDTH / 2, SCREEN_HEIGH / 2, player1_keys, &lasers, 0));
            break;
        case 2:
            ships.push_back(new Ship(3, SCREEN_WIDTH / 2 - distance_from_the_center, SCREEN_HEIGH / 2, player1_keys, &lasers, 1));
            ships.push_back(new Ship(3, SCREEN_WIDTH / 2 + distance_from_the_center, SCREEN_HEIGH / 2, player2_keys, &lasers, 2));
            break;
        default:
            std::cout << "Error: unexpected number of players!";
    }

    gameLoop();
}

// -----------------
// | Ciclo de jogo |
// -----------------

void Game::gameLoop() {
    while (gameState != GameState::EXIT) {
        Uint64 start = SDL_GetPerformanceCounter();
        
        handleEvents();
        
        const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
        if (gameState == GameState::RUNNING) {
            
            // Jogadores
            for (Ship* player : ships) {
                player->update(keyboard_state);
                if (player->hit) {
                    if (player->lives > 1) {
                        int keys[4] = {player->keys["RIGHT"], player->keys["LEFT"], player->keys["UP"], player->keys["SHOT"]};
                        std::replace(ships.begin(), ships.end(), player, new Ship(player->lives-1, SCREEN_WIDTH / 2, SCREEN_HEIGH / 2, keys, &lasers, player->n));
                    }
                    else {
                        auto ships_remove = std::remove_if(ships.begin(), ships.end(), [&] (Ship* player) {return player->hit;});
                        if (ships_remove != ships.end()) {
                            ships.erase(ships_remove);
                        }
                    }
                }
            }

            // Asteroides
            // Atualizar
            for (Asteroid* asteroid : asteroids) {
                asteroid->update(&lasers, &ships);

                // Criar novos asteroides
                if (asteroid->size > 1 && asteroid->hit) {     
                    asteroids.push_back(new Asteroid(asteroid->x, asteroid->y, asteroid->size/2));
                    asteroids.push_back(new Asteroid(asteroid->x, asteroid->y, asteroid->size/2));                           
                }
            }
            // Destruir
            if (asteroids.size() > 0) {
                auto asteroid_remove = std::remove_if(asteroids.begin(), asteroids.end(), [&] (Asteroid* asteroid) {return asteroid->hit;});
                if (asteroid_remove != asteroids.end()) {
                    asteroids.erase(asteroid_remove);               
                }
            }

            // Lasers
            // Atualizar
            for (Laser* laser : lasers) {
                laser->update();
            }
            // Remover
            if (lasers.size() > 0) {
                auto laser_remove = std::remove_if(lasers.begin(), lasers.end(), [&] (Laser* laser) {return laser->to_delete;});
                if (laser_remove != lasers.end()) {
                    lasers.erase(laser_remove);
                }
            }

            // Mudar de nível
            if (asteroids.size() <= 0) {
                this->level++;
                for (int i = 0; i < std::min(this->level*2-1, 6); i++) {
                    asteroids.push_back(new Asteroid(rand() % SCREEN_WIDTH, rand() % SCREEN_WIDTH, 4));
                }
            }
        }
        keyboard_state = NULL;

        draw();
        Uint64 end = SDL_GetPerformanceCounter();
        dt = (end - start) / SDL_GetPerformanceFrequency();
        SDL_Delay(DT*1000-dt);
    }
}

void Game::draw() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    // Mandar para aqui os desenhos

    switch (gameState) {
    case GameState::RUNNING:
        for (Ship* player : ships) {
            player->draw(_renderer);
        }
        
        for (Asteroid* asteroid : asteroids) {
            asteroid->draw(_renderer);
        }

        for (Laser* laser : lasers) {
            laser->draw(_renderer);
        }

        break;
    
    case GameState::MENU:
        for (Text text : menu_text) {
            text.draw(_renderer);
        }

        break;
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
