#pragma once
#include <SDL/SDL2_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/globals.hpp>

class Ship {
private:
public:
    unsigned short int angle = 0; // ângulo em graus
    unsigned short int lives;
    unsigned short int x;
    unsigned short int y;
    float angular_speed = 2; // velocidade com que gira em graus por tick 

    Ship(unsigned short int lives, unsigned short int x, unsigned short int y);
    ~Ship();
    void draw(SDL_Renderer* renderer);
};
