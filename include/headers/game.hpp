#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/ship.hpp>
#include <headers/asteroids.hpp>
#include <headers/laser.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

enum class GameState {RUNNING, EXIT};

class Game {
private:
    
    void gameLoop();
    void handleEvents();

    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

    long double dt;

public:
    GameState gameState = GameState::RUNNING;

    Game(const char* title, int x, int y, int w, int h, Uint32 flags);
    
    void run();
    void draw();

    std::vector<Ship*> ships;
    std::vector<Asteroid*> asteroids; 
    std::vector<Laser*> lasers; 
};