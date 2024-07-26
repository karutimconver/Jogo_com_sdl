#include <headers/game.hpp>

// ------------------------------
// | Construtor e Inicializador |
// ------------------------------

Game::Game(const char* title, int x, int y, int w, int h, Uint32 flags) {
    std::cout << "size of asteroid: " << sizeof(Asteroid) << " bytes\n";
    std::cout << "size of laser: " << sizeof(Laser) << " bytes\n";
    std::cout << "size of ship: " << sizeof(Ship) << " bytes\n";

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Couldn't initialize SDL2" << SDL_GetError();
    };

    if (TTF_Init() == -1) {
        std::cout << "Couldn't initialize SDL2_ttf" << TTF_GetError();
    };

    _window = SDL_CreateWindow(title, x, y, w, h, flags);
    _renderer = SDL_CreateRenderer(_window, -1, 0);

    // Criar Menu
    Text main_title("Asteroids", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 30, _renderer);
    Button single_player("single player", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 16, _renderer);
    Button multiplayer("multiplayer", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, 16, _renderer);

    menu_text.push_back(main_title);
    menu_buttons.push_back(single_player);
    menu_buttons.push_back(multiplayer);

    // Criar texto de pausa
    Text paused("PAUSED", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20, 20, _renderer);
    Text unpause("press 'esc' to unpause", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 10, 16, _renderer);

    pause_text.push_back(paused);
    pause_text.push_back(unpause);

    // Criar estado de fim do jogo
    Text gameover("GAME OVER", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60, 30, _renderer);
    Button retry("try again", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 10, 16, _renderer);
    Button menu("menu", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, 16, _renderer);

    gameover_text.push_back(gameover);
    gameover_buttons.push_back(retry);
    gameover_buttons.push_back(menu);
}

void Game::run(int n) {
    level = 0;

    // A criar jogadores
    int distance_from_the_center = 200;    // distancia da nave ao centro da tela
    int player1_keys [4] = {SDL_SCANCODE_D, SDL_SCANCODE_A, SDL_SCANCODE_W, SDL_SCANCODE_SPACE};
    int player2_keys [4] = {SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT, SDL_SCANCODE_UP, SDL_SCANCODE_RCTRL};
    
    this->player_num = n;

    switch (n) {
        case 1:
            ships.push_back(new Ship(3, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, player1_keys, &lasers, 0));
            break;
        case 2:
            ships.push_back(new Ship(3, SCREEN_WIDTH / 2 - distance_from_the_center, SCREEN_HEIGHT / 2, player1_keys, &lasers, 1));
            ships.push_back(new Ship(3, SCREEN_WIDTH / 2 + distance_from_the_center, SCREEN_HEIGHT / 2, player2_keys, &lasers, 2));
            break;
        default:
            std::cout << "Error: unexpected number of players!";
    }
}

// -----------------
// | Ciclo de jogo |
// -----------------

void Game::gameLoop() {
    while (gameState != GameState::EXIT) {
        Uint64 start = SDL_GetPerformanceCounter();
        
        handleEvents();
        
        const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
        // jogo a correr
        if (gameState == GameState::RUNNING) {
            // Jogadores
            for (Ship* player : ships) {
                player->update(keyboard_state);
                if (player->hit) {
                    if (player->lives > 1) {
                        int keys[4] = {player->keys["RIGHT"], player->keys["LEFT"], player->keys["UP"], player->keys["SHOT"]};
                        std::replace(ships.begin(), ships.end(), player, new Ship(player->lives-1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, keys, &lasers, player->n));
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

                    if (level >= 7) {
                        asteroids.push_back(new Asteroid(asteroid->x, asteroid->y, asteroid->size/2));
                    }
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
                for (int i = 0; i < std::min(this->level*2 - 2 + (int) ships.size(), 8); i++) {
                    int x = rand() % SCREEN_WIDTH;
                    int y = rand() % SCREEN_HEIGHT;

                    while (1) {
                        if (ships.size() == 2) {
                            if (calculate_distance(x, y, ships[0]->x, ships[0]->y) > 80 &&
                                calculate_distance(x, y, ships[1]->x, ships[1]->y) > 80)
                                break;
                        }
                        else {
                            if (calculate_distance(x, y, ships[0]->x, ships[0]->y) > 80)
                                break;
                        }
                        x = rand() % SCREEN_WIDTH;
                        y = rand() % SCREEN_HEIGHT;
                    }

                    asteroids.push_back(new Asteroid(x, y, 4));
                }
            }

            // Fim do jogo
            if (this->ships.size() == 0) {
                gameState = GameState::GAMEOVER;

                asteroids.clear();
                lasers.clear();
            }
        }
    
        // Menu
        else if (gameState == GameState::MENU) {
            for (Button& button : menu_buttons) {
                if (button.pressed) {
                    gameState = GameState::RUNNING;

                    std::cout << button.get_text();
                    if (button.get_text() == "single player") { 
                        this->run(1); 
                    }
                    else if (button.get_text() == "multiplayer") { 
                        this->run(2); 
                    }
                }
                
                button.update();
            }
        }

        // Estado de fim de jogo
        else if (gameState == GameState::GAMEOVER) {
            for (Button& button : gameover_buttons) {
                if (button.pressed) {
                    gameState = GameState::RUNNING;

                    std::cout << "button "<< button.get_text() << " pressed!\n";
                    if (button.get_text() == "try again") { 
                        this->run(this->player_num); 
                    }
                    if (button.get_text() == "menu") { 
                        gameState = GameState::MENU;
                    }
                }

                button.update();
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

    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    //SDL_RenderSetViewport(_renderer, &border);
    
    // Inicio dos desenhos
    // Desenhar bordas
    if (SDL_RenderDrawRect(_renderer, &border) > 0)
        std::cout << "Unable to draw border" << SDL_GetError();

    // Desenhos de jogo
    switch (gameState) {
    case GameState::RUNNING:
        for (Ship* player : ships) {
            player->draw(_renderer, offsetx, offsety);
        }
        
        for (Asteroid* asteroid : asteroids) {
            asteroid->draw(_renderer, offsetx, offsety);
        }

        for (Laser* laser : lasers) {
            laser->draw(_renderer, offsetx, offsety);
        }

        break;
    
    case GameState::PAUSED:
        for (Ship* player : ships) {
            player->draw(_renderer, offsetx, offsety);
        }
        
        for (Asteroid* asteroid : asteroids) {
            asteroid->draw(_renderer, offsetx, offsety);
        }

        for (Laser* laser : lasers) {
            laser->draw(_renderer, offsetx, offsety);
        }

        for (Text& text : pause_text) {
            text.draw(_renderer, offsetx, offsety);
        }

        break;

    case GameState::GAMEOVER:
        for (Text& text : gameover_text) {
            text.draw(_renderer, offsetx, offsety);
        }
        
        for (Button& button : gameover_buttons) {
            button.draw(_renderer, offsetx, offsety);
        }

        break;
    
    case GameState::MENU:
        for (Text& text : menu_text) {
            text.draw(_renderer, offsetx, offsety);
        }
        
        for (Button& button : menu_buttons) {
            button.draw(_renderer, offsetx, offsety);
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
        case SDL_KEYDOWN:
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                if (gameState == GameState::PAUSED) {
                    std::cout << "Unpaused \n";
                    gameState = GameState::RUNNING;
                }
                else if (gameState == GameState::RUNNING) {
                    std::cout << "paused \n";
                    gameState = GameState::PAUSED;
                }
            }

            break;
        case SDL_MOUSEBUTTONDOWN: 
            std::cout << "mouse down\n";
            switch (gameState) {
                case GameState::MENU:
                    for (Button& button : menu_buttons) {
                        button.pressed = button.hover;
                    }
                    break;
                case GameState::GAMEOVER:
                    for(Button& button : gameover_buttons) {
                        button.pressed = button.hover;
                    }
                    break;
            }

        case SDL_WINDOWEVENT_RESIZED:
            SDL_GetWindowSize(_window, &width, &height);

            if (width < SCREEN_WIDTH) width = SCREEN_WIDTH;
            if (height < SCREEN_HEIGHT) height = SCREEN_HEIGHT; 

            SDL_SetWindowSize(_window, width, height);

            std::cout << "width" << width << "\n";
            std::cout << "height" << height << "\n";

            offsetx = std::max((width - SCREEN_WIDTH) / 2, 0);
            offsety = std::max((height - SCREEN_HEIGHT) / 2, 0);

            std::cout << "offsetx: " << offsetx << "\n";
            std::cout << "offsety: " << offsety << "\n";

            border = {offsetx, offsety, SCREEN_WIDTH, SCREEN_HEIGHT}; 

            break;
    }
}
