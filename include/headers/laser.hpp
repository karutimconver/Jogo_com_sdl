#pragma once

#include <SDL/SDL2_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/globals.hpp>
#include <vector>

class Laser {
private:
    void* laser_array;
public:
    Laser(int y, int x, float angle);
    ~Laser();
    void update();
    void draw(SDL_Renderer* renderer);
};