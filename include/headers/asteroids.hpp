#pragma once

#include <SDL/SDL2_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/globals.hpp>

class Asteroids {
private:
    unsigned short int r = 10;      // Raio padrão  
    unsigned short int angle = 90;  // Ângulo em graus
    float angular_speed = 2;        // Velocidade com que gira em graus por tick 
    unsigned short int size;        // Tamanho

public:
    float x;
    float y;
    int radius;                     // raio do asteroide (caixa de colisão) raio = r * size

};