#pragma once

#include <SDL/SDL2_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/globals.hpp>
#include <headers/ship.hpp>
#include <headers/laser.hpp>
#include <iostream>
#include <vector>

class Asteroid {
private:
    unsigned short int r = 10;       // Raio padrão
    Vec2d velocity;
    float speed;                     // Velocidade
    float angle = 0;                 // Ângulo em graus
    float angular_speed;             // Velocidade com que gira em graus por tick 
    unsigned short int size;         // Tamanho
    unsigned short int vertices = 7; // nº de vertices
    float* v_distance_array;
    float* v_angle_array;

    void screen_wrap();
    //void collide();
    void rotate();
    void move();
public:
    float x;
    float y;
    unsigned short int radius;       // raio do asteroide (caixa de colisão) raio = r * size

    Asteroid(int x, int y, int size);
    ~Asteroid();
    void update();
    void draw(SDL_Renderer* renderer);
};