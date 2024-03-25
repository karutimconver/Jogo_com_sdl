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
    float points[this->vertices][2];
    for (int i = 0; i < this->vertices; i++) {
        float p_distance = radius + (((rand() % 20) * 0.1) - 1);
        float p_angle = angle + (((rand() % 20) * 0.1) - 1) + ((380 / vertices) * (i + 1));
        points[i][0] = p_distance;
        points[i][1] = p_angle;
        std::cout << p_distance << " " << p_angle << "\n";
    }
    std::cout << "\n-----------\n";

    
};