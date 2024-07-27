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
    int offsetx = 0;           // desvio dos desenhos no eixo x 
    int offsety = 0;           // desvio dos desenhos no eixo y (necessario quando se altera tamanho da janela)

    SDL_Rect border = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    unsigned short int level;
    int player_num = 0;

    long double dt;
 
    std::vector<Ship*> ships;
    std::vector<Asteroid*> asteroids; 
    std::vector<Laser*> lasers; 
    std::vector<Text> menu_text;
    std::vector<Button> menu_buttons;
    std::vector<Text> gameover_text;
    std::vector<Button> gameover_buttons;
    std::vector<Text> pause_text;
public:
    GameState gameState = GameState::MENU;

    Game(const char* title, int x, int y, int w, int h, Uint32 flags);
    int special_event_callback(void *userdata, SDL_Event *event);
    void run(int n);
    void gameLoop();
    void draw();
};