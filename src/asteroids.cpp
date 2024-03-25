#include <headers/asteroids.hpp>

// ---------------------------
// | Construtor e Destruidor |
// ---------------------------

Asteroid::Asteroid(int x, int y, int size) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->radius = r * size;
};

Asteroid::~Asteroid() {

};

// -------------
// | Movimento |
// -------------

void Asteroid::rotate() {

};

void Asteroid::move() {

};

// -----------------
// | Ciclo do jogo |
// -----------------

void Asteroid::update() {
    this->move();
    this->rotate();
};

void Asteroid::draw(SDL_Renderer* renderer) {
    // A criar um array de pontos nas coordenadas polares
    float points[vertices][2];
};