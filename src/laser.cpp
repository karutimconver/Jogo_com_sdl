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
    this->x += this->velocity.x;
    this->y += this->velocity.y;
};

void Laser::screen_wrap() {
    if (this->y < 0)
        this->y = SCREEN_HEIGH;
    else if (this->y > SCREEN_HEIGH)
        this->y = 0;

    if (this->x < 0)
        this->x = SCREEN_WIDTH;
    else if (this->x> SCREEN_WIDTH)
        this->x = 0; 
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