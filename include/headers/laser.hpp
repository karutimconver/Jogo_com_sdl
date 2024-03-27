#pragma once

#include <SDL/SDL2_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/globals.hpp>
#include <vector>

class Laser {
private:
    int speed;               // Rapidez de movimento em unidades por segundo
    Vec2d velocity;          // Vetor da velocidade
    float max_distance;      // Distância máxima
    float distance_traveled; // distância percorrida

    void move();
    void screen_wrap();
    void count();
public:
    bool to_delete = false;
    int x;
    int y;

    Laser(int y, int x, float angle);
    ~Laser();
    void update();
    void draw(SDL_Renderer* renderer);
};