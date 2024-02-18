#pragma once

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/ship.hpp>

enum class GameState {RUNNING, EXIT};

class Game {
public:
    GameState gameState = GameState::RUNNING;

    Game(const char* title, int x, int y, int w, int h, Uint32 flags);
    
    void run();
    void draw();

    Ship* player1 = nullptr;
    Ship* player2 = nullptr;
private:
    
    void gameLoop();
    void handleEvents();

    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

    long double dt;
};