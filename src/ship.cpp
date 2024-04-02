#include <headers/ship.hpp>
#include <headers/globals.hpp>
#include <iostream>

// ---------------------------
// | Construtore e Destruidor |
// ---------------------------

Ship::Ship(unsigned short int lives, unsigned short int x, unsigned short int y, int keys [4], std::vector<Laser*>* lasers) {
  this->lives = lives;
  this->x = x;
  this->y = y;
  
  this->keys.insert({"RIGHT", keys[0]});
  this->keys.insert({"LEFT", keys[1]});
  this->keys.insert({"UP", keys[2]});
  this->keys.insert({"SHOT", keys[3]});

  this->laser_array = lasers;
};

Ship::~Ship() {
    laser_array = NULL;
};

// -------------
// | Controlos |
// -------------

void Ship::rotate(const Uint8* keyboard_state) {
  if (keyboard_state[keys["RIGHT"]]) 
    this->angle += angular_speed;

  if (keyboard_state[keys["LEFT"]])
    this->angle -= angular_speed;
};

void Ship::controls(const Uint8* keyboard_state) {
  // Movimento
  this->rotate(keyboard_state);

  if (keyboard_state[keys["UP"]])
    thrusting = true;
  else
    thrusting = false;

  // Tiros
  if (keyboard_state[keys["SHOT"]]) {
    if (this->shot_timer >= this->cooldown) {
      laser_array->push_back(new Laser(tip_x, tip_y, angle));
      this->shot_timer = 0;
    }
  }
  this->shot_timer += DT;
};

// -------------
// | Movimento |
// -------------

void Ship::move() {
  if (thrusting) {
    velocity.x += thrust * cos(angle * M_PI / 180);
    velocity.y += thrust * sin(angle * M_PI / 180);
  }

  apply_friction();

  x += velocity.x * DT;
  y += velocity.y * DT;
};

void Ship::apply_friction() {
  velocity.x -= friction * DT * velocity.x;
  velocity.y -= friction * DT * velocity.y;
}

// -----------------
// | Ecrã infinito |
// -----------------

void Ship::screen_wrap(){
  if (this->y + this->radius < 0)
    this->y = SCREEN_HEIGH + this->radius;
  else if (this->y - this->radius > SCREEN_HEIGH)
    this->y = 0 - this->radius;

  if (this->x + this->radius < 0)
    this->x = SCREEN_WIDTH + this->radius;
  else if (this->x - this->radius > SCREEN_WIDTH)
    this->x = 0 - this->radius; 
};

// -----------------
// | Ciclo do jogo |
// -----------------

void Ship::update(const Uint8* keyboard_state) {
  this->controls(keyboard_state);
  this->move();
  this->screen_wrap();
};

void Ship::draw(SDL_Renderer* renderer) {
    // Coordenadas Polares
    unsigned short int p1_angle    = (360 * 100) + angle;                   // ângulo em graus do ponto 1
    unsigned short int p1_distance = 14;                                    // distancia em graus do ponto 1
    unsigned short int p2_angle    = 130 + (360 * 100) + angle;             // ângulo em graus do ponto 2
    unsigned short int p2_distance = 13;                                    // distancia em graus do ponto 2
    unsigned short int p3_angle    = 230 + (360 * 100) + angle;             // ângulo em graus do ponto 3
    unsigned short int p3_distance = 13;                                    // distancia em graus do ponto 3

  
    // Coordenadas Cartesianas
    // As funções sin() e cos() recebem um ângulo medido em radianos. A(radianos) = A(graus) * pi / 180; A - ângulo
    tip_x = round(x + p1_distance * cos(p1_angle * M_PI / 180));
    tip_y = round(y + p1_distance * sin(p1_angle * M_PI / 180));
    unsigned short int x2 = round(x + p2_distance * cos(p2_angle * M_PI / 180));
    unsigned short int y2 = round(y + p2_distance * sin(p2_angle * M_PI / 180));
    unsigned short int x3 = round(x + p3_distance * cos(p3_angle * M_PI / 180));
    unsigned short int y3 = round(y + p3_distance * sin(p3_angle * M_PI / 180));

    unsigned short int val = aatrigonRGBA(renderer, tip_x, tip_y, x2, y2, x3, y3, 255, 255, 255, SDL_ALPHA_OPAQUE);

    if (DEBUGGING) {
      SDL_RenderDrawPoint(renderer, x, y);
      aacircleRGBA(renderer, x, y, radius, 255, 120, 120, SDL_ALPHA_OPAQUE);
    }
};