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
    Sint16 x[vertices];
    Sint16 y[vertices];

    for (int i = 0; i < vertices; i++) {
        x[i] = round(this->x + points[i][0] * cos(points[i][1] * M_PI / 180));
        y[i] = round(this->y + points[i][0] * sin(points[i][1] * M_PI / 180));
    }

    // Desenhar
    aapolygonRGBA(renderer, x, y, vertices, 255, 255, 255, SDL_ALPHA_OPAQUE);

    if (DEBUGGING) {
      SDL_RenderDrawPoint(renderer, this->x, this->y);
      aacircleRGBA(renderer, this->x, this->y, radius, 255, 120, 120, SDL_ALPHA_OPAQUE);
    }
};