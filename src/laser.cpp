#include <headers/laser.hpp>

// ---------------------------
// | Construtor e Destruidor |
// ---------------------------

Laser::Laser(int y, int x, float angle) {
    this->x = x;
    this->y = y;

    
    this->velocity.x += this->speed * cos(angle * M_PI / 180);
    this->velocity.y += this->speed * sin(angle * M_PI / 180); 
};

Laser::~Laser() {

};

// -------------
// | Movimento |
// -------------

void Laser::move() {

};

void Laser::screen_wrap() {

};

// ------------
// | Contador |
// ------------

void Laser::count() {

};

// -----------------
// | Ciclo de jogo |
// -----------------

void Laser::update() {

};

void Laser::draw(SDL_Renderer* renderer) {

};