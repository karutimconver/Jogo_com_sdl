#pragma once
#include <SDL/SDL2_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/globals.hpp>
#include <unordered_map>

class Ship {
private:
    std::unordered_map<std::string, int> keys;  // Teclas de controlos
    Vec2d velocity;                              // Vetor da velocidade
    bool thrusting = false;                     // Representa se está a acelarar ou não
    int thrust     = 7;                        // accelaração por segundo
    int friction   = 1;                         // fricção por segundo
public:
    float x;
    float y;
    unsigned short int angle = 90; // ângulo em graus
    float angular_speed = 2;       // velocidade com que gira em graus por tick 
    unsigned short int lives;

    Ship(unsigned short int lives, unsigned short int x, unsigned short int y, int keys [3]);
    ~Ship();
    void rotate(const Uint8* keyboard_state);
    void controls(const Uint8* keyboard_state);
    void move();
    void update(const Uint8* keybaoard_state);
    void apply_friction();
    void draw(SDL_Renderer* renderer);
};
