#pragma once

#include <SDL/SDL2_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/globals.hpp>
#include <headers/laser.hpp>
#include <headers/ship.hpp>
#include <iostream>
#include <vector>

class Asteroid {
private:
    unsigned short int r = 10;       // Raio base
    Vec2d velocity;                  // Vetor velocidade
    float speed;                     // Rapidez
    float angle = 0;                 // Ângulo em graus
    float angular_speed;             // Velocidade com que gira em graus por tick 
    unsigned short int vertices = 7; // Nº de vertices
    float* v_distance_array;         // Ponteiro para o array de distancias dos vértices ao centro
    float* v_angle_array;            // Ponteiro para o array de angulos dos vértices

    void screen_wrap();
    void collide(std::vector<Laser*>* lasers, std::vector<Ship*>* players);
    void rotate();
    void move();
public:
    float x;
    float y;
    bool hit = false;                // Se foi ou não atingido
    unsigned short int size;         // Tamanho
    unsigned short int radius;       // raio do asteroide (caixa de colisão) raio = r * size

    Asteroid(int x, int y, int size);
    ~Asteroid();
    void update(std::vector<Laser*>* lasers, std::vector<Ship*>* players);
    void draw(SDL_Renderer* renderer, int offsetx, int offsety, Uint8 opacity);
};