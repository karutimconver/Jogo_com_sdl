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
    // Criar um array de pontos nas coordenadas polares
    float points[vertices][2];
    for (int i = 0; i < vertices; i++) {
        float pdistance = radius + (((rand() % 20) * 0.1) - 1);
        float pangle = radius + (((rand() % 20) * 0.1) - 1) + (360 / i);
        points[vertices][0] = pdistance;
        points[vertices][1] = pangle;
    }

    // Criar dois arrays de coordenas cartesianas: x e y.
    Sint16 x;
    Sint16 y;

    for (int i = 0; i < vertices; i++) {
        
    }
};