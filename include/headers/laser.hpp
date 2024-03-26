#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/globals.hpp>

class Laser {
private:
    Vec2d velocity;

    void move();
public:
    float x;
    float y;

    Laser(int x, int y);
    ~Laser();
    void update();
};