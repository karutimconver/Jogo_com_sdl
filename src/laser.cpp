#include <headers/laser.hpp>

// ---------------------------
// | Construtor e Destruidor |
// ---------------------------

Laser::Laser(int x, int y, float angle, std::vector<Laser*>* p) {
    this->x = x;
    this->y = y;

    this->laser_array = p;

    this->velocity.x -= speed * DT * cos(angle * M_PI / 180);
    this->velocity.y -= speed * DT * sin(angle * M_PI / 180);
};

Laser::~Laser() {
    laser_array = NULL;
};

// -------------
// | Movimento |
// -------------

void Laser::move() {
    this->x += this->velocity.x;
    this->y += this->velocity.y;
};

//
// | Relógio interno |
//

void Laser::Count() {
    this->time_alive += DT;

    if (this->time_alive >= this->max_time) {
        laser_array->erase(laser_array->begin());
        delete this;
    }
};

// -----------------
// | Ciclo do jogo |
// -----------------

void Laser::update() {
    this->move();
};

void Laser::draw(SDL_Renderer* renderer) {
    aacircleRGBA(renderer, x, y, 0, 255, 255, 255, SDL_ALPHA_OPAQUE);
};