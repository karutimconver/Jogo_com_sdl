#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL2_gfxPrimitives.h>
#include <vector>
#include <headers/globals.hpp>

class Laser {
private:
    std::vector<Laser*>* laser_array = nullptr; // Ponteiro para o array de Laseres
    Vec2d velocity;                             // Vetor velocidade
    int time_alive;                             // Tempo vivo
    int max_time = 30;                          // Tempo de vida em segundos (tempo = distancia percorrida / rapidez)
    int speed = 50;                             // Rapidez

    void move();
    void Count();
public:
    float x;
    float y;

    Laser(int x, int y, float angle, std::vector<Laser*>* p);
    ~Laser();
    void update();
    void draw(SDL_Renderer* renderer);
};