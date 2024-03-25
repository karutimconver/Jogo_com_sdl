#pragma once

#include <SDL/SDL2_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/globals.hpp>

class Asteroid {
private:
    unsigned short int r = 10;      // Raio padrão  
    unsigned short int angle = 90;  // Ângulo em graus
    float angular_speed = 2;        // Velocidade com que gira em graus por tick 
    unsigned short int size;        // Tamanho

    void rotate();
    void move();
public:
    float x;
    float y;
    int radius;                     // raio do asteroide (caixa de colisão) raio = r * size

    Asteroid();
    ~Asteroid();
    void update();
    void draw(SDL_Renderer* renderer);
};