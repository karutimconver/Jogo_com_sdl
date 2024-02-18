#include <headers/ship.hpp>
#include <headers/globals.hpp>
#include <iostream>

static double d2r(double d) {
  return (d / 180.0) * ((double) M_PI);
}

Ship::Ship(unsigned short int lives, unsigned short int x, unsigned short int y) {
    this->lives = lives;
    this->x = x;
    this->y = y;
};

Ship::~Ship() {
    
};

void Ship::draw(SDL_Renderer* renderer) {
    // Coordenadas Polares
    unsigned short int p1_angle    = 90 + angle;        // ângulo em graus do ponto 1
    unsigned short int p1_distance = 16;                // distancia em graus do ponto 1
    unsigned short int p2_angle    = 210 + angle;       // ângulo em graus do ponto 2
    unsigned short int p2_distance = 12;                 // distancia em graus do ponto 2
    unsigned short int p3_angle    = 330 + angle;       // ângulo em graus do ponto 3
    unsigned short int p3_distance = 12;                 // distancia em graus do ponto 3

  
    // Coordenadas Cartesianas
    // As funções sin() e cos() recebem um ângulo medido em radianos. A(radianos) = A(graus) * pi / 180; A - ângulo
    unsigned short int x1 = x + p1_distance * cos(p1_angle * M_PI / 180);
    unsigned short int y1 = y + p1_distance * sin(p1_angle * M_PI / 180);
    unsigned short int x2 = x + p2_distance * cos(p2_angle * M_PI / 180);
    unsigned short int y2 = y + p2_distance * sin(p2_angle * M_PI / 180);
    unsigned short int x3 = x + p3_distance * cos(p3_angle * M_PI / 180);
    unsigned short int y3 = y + p3_distance * sin(p3_angle * M_PI / 180);

    unsigned short int val = aatrigonRGBA(renderer, x1, y1, x2, y2, x3, y3, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
    if (DEBUGGING) {
      SDL_RenderDrawPoint(renderer, x, y);
    }
};