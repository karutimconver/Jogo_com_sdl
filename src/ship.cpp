#include <headers/ship.hpp>
#include <headers/globals.hpp>
#include <iostream>


// ---------------------------
// | Construtore e Destrutor |
// ---------------------------

Ship::Ship(unsigned short int lives, unsigned short int x, unsigned short int y, int keys [3]) {
    this->lives = lives;
    this->x = x;
    this->y = y;
    this->keys.insert({"RIGHT", keys[0]});
    this->keys.insert({"LEFT", keys[1]});
    this->keys.insert({"UP", keys[2]});
};

Ship::~Ship() {
    
};

// -------------------------
// | Controlos e Movimento |
// -------------------------

void Ship::rotate(const Uint8* keyboard_state) {
  if (keyboard_state[keys["RIGHT"]]) 
    this->angle += angular_speed;

  if (keyboard_state[keys["LEFT"]])
    this->angle -= angular_speed;
};

void Ship::controls(const Uint8* keyboard_state) {
  this->rotate(keyboard_state);

  if (keyboard_state[keys["UP"]])
    thrusting = true;
  else
    thrusting = false;
};

void Ship::move() {

}

// -----------------
// | Ciclo do jogo |
// -----------------

void Ship::update(const Uint8* keyboard_state) {
  this->controls(keyboard_state);
};

void Ship::draw(SDL_Renderer* renderer) {
    // Coordenadas Polares
    unsigned short int p1_angle    = 90 + (180 + (360 * 100)) + angle;        // ângulo em graus do ponto 1
    unsigned short int p1_distance = 16;                                    // distancia em graus do ponto 1
    unsigned short int p2_angle    = 210 + (180 + (360 * 100)) + angle;       // ângulo em graus do ponto 2
    unsigned short int p2_distance = 12;                                    // distancia em graus do ponto 2
    unsigned short int p3_angle    = 330 + (180 + (360 * 100)) + angle;       // ângulo em graus do ponto 3
    unsigned short int p3_distance = 12;                                    // distancia em graus do ponto 3

  
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