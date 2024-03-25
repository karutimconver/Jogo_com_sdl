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

