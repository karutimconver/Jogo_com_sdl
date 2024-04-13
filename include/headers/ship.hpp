#pragma once

#include <SDL/SDL2_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/globals.hpp>
#include <headers/laser.hpp>
#include <headers/text.hpp>
#include <unordered_map>
#include <iostream>
#include <vector>

class Ship {
private:
    std::vector<Laser*>* laser_array = nullptr; // Ponteiro para o array de lasers
    Vec2d velocity;                             // Vetor da velocidade
    bool thrusting = false;                     // Representa se está a acelarar ou não
    int thrust = 7;                             // Accelaração por segundo
    float friction = 0.5;                       // Fricção por segundo
    float angle = 270;                          // Ângulo em graus
    float angular_speed = 2.5;                  // Velocidade com que gira em graus por tick 
    float shot_timer = 0;                       // Tempo desdo último disparo
    double cooldown = 30 * DT;                  // Tempo de recarga em Ticks
    float invincible_timer = 2;                 // Cronômetro de invencibilidade
    Text* name = nullptr;                       // Nome da nave

    unsigned short int tip_x;
    unsigned short int tip_y;

    void rotate(const Uint8* keyboard_state);
    void controls(const Uint8* keyboard_state); 
    void apply_friction();
    void screen_wrap();
    void move();
public:
    bool invincible = true;                     // Se está ou não invencivel
    unsigned short int n;                       // número da nave
    float x;
    float y;
    bool hit = false;                           // Se foi ou não atingido
    int radius = 10;                            // Raio (colisão)
    std::unordered_map<std::string, int> keys;  // Teclas de controlos
    unsigned short int lives;

    Ship(unsigned short int lives, unsigned short int x, unsigned short int y, int keys [4], std::vector<Laser*>* lasers, unsigned short int n);
    ~Ship();
    void update(const Uint8* keyboard_state);
    void draw(SDL_Renderer* renderer);
};
