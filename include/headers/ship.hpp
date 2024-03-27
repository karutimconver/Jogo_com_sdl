#pragma once

#include <SDL/SDL2_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/globals.hpp>
#include <headers/laser.hpp>
#include <unordered_map>
#include <vector>

class Ship {
private:
    std::vector<Laser*>* laser_array = nullptr; // ponteiro para o array de lasers
    std::unordered_map<std::string, int> keys;  // Teclas de controlos
    Vec2d velocity;                             // Vetor da velocidade
    bool thrusting = false;                     // Representa se está a acelarar ou não
    int thrust = 7;                             // Accelaração por segundo
    float friction = 0.5;                       // Fricção por segundo
    float angle = 270;                          // Ângulo em graus
    float angular_speed = 2.5;                  // Velocidade com que gira em graus por tick 
    unsigned short int tip_x;
    unsigned short int tip_y;

    void rotate(const Uint8* keyboard_state);
    void controls(const Uint8* keyboard_state);
    void move();
    void apply_friction();
    void screen_wrap();
public:
    float x;
    float y;
    int radius = 10;                            // Raio (colisão)
    unsigned short int lives;

    Ship(unsigned short int lives, unsigned short int x, unsigned short int y, int keys [4], std::vector<Laser*>* lasers);
    ~Ship();
    void update(const Uint8* keybaoard_state);
    void draw(SDL_Renderer* renderer);
};
