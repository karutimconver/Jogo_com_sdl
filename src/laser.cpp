#include <headers/laser.hpp>

// ---------------------------
// | Construtor e Destruidor |
// ---------------------------

Laser::Laser(int x, int y, float angle) {
    this->x = x;
    this->y = y;
    
    this->velocity.x += this->speed * DT * cos(angle * M_PI / 180);
    this->velocity.y += this->speed * DT * sin(angle * M_PI / 180); 
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
    this->move();
    this->screen_wrap();
};

void Laser::draw(SDL_Renderer* renderer) {
    aacircleRGBA(renderer, x, y, 0, 255, 255, 255, SDL_ALPHA_OPAQUE);
};