#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <headers/ship.hpp>
#include <headers/asteroids.hpp>
#include <headers/laser.hpp>
#include <headers/text.hpp>
#include <headers/button.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

enum class GameState {RUNNING, EXIT, MENU, PAUSED, GAMEOVER};

class Game {
private:
    void handleEvents();

    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

    unsigned short int level = 0;

    long double dt;
public:
    GameState gameState = GameState::MENU;

    Game(const char* title, int x, int y, int w, int h, Uint32 flags);
    
    void run(int n);
    void gameLoop();
    void draw();

    std::vector<Ship*> ships;
    std::vector<Asteroid*> asteroids; 
    std::vector<Laser*> lasers; 
    std::vector<Text> menu_text;
    std::vector<Button> menu_buttons;
    std::vector<Text> pause_text;
};