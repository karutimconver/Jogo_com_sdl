#pragma once

#include <SDL/SDL2_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/globals.hpp>
#include <vector>
#include <iostream>

class Laser {
private:
    Vec2d velocity;              // Vetor da velocidade
    int speed = 1000;            // Rapidez de movimento em unidades por segundo
    float max_distance = 750;    // Distância máxima
    float distance_traveled=0;   // distância percorrida

    void move();
    void screen_wrap();
    void count();
public:
    bool to_delete = false;
    int y;
    int x;

    Laser(int x, int y, float angle);
    ~Laser();
    void update();
    void draw(SDL_Renderer* renderer);
};