#include <headers/asteroids.hpp>

// ---------------------------
// | Construtor e Destruidor |
// ---------------------------

Asteroid::Asteroid(int x, int y, int size) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->radius = r * size;

    this->v_distance_array = new float [this->vertices];
    this->v_angle_array = new float [this->vertices];
    for (int i = 0; i < this->vertices; i++) {
        v_distance_array[i] = ((rand() % 50) * 0.1);
        v_angle_array[i] = ((rand() % 50) * 0.1);
    }
};

Asteroid::~Asteroid() {
    delete v_distance_array;
    delete v_angle_array;
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
    // Criar array de pontos defenidos por coordenadas polares
    float points[this->vertices][2];
    for (int i = 0; i < this->vertices; i++) {
        float p_distance = radius + v_distance_array[i];
        float p_angle = angle + v_angle_array[i] + ((380 / vertices) * (i + 1));
        points[i][0] = p_distance;
        points[i][1] = p_angle;
    }

    // Converter para arrays de coordenadas cartesianas
    Sint16 array_x[this->vertices];
    Sint16 array_y[this->vertices];

    for (int j = 0; j < this->vertices; j++) {
        array_x[j] = round(x + points[j][0] * cos(points[j][1] * M_PI / 180));
        array_y[j] = round(y + points[j][0] * sin(points[j][1] * M_PI / 180));
    }

    // Desenhar
    aapolygonRGBA(renderer, array_x, array_y, this->vertices, 255, 255, 255, SDL_ALPHA_OPAQUE);

    if (DEBUGGING) {
      SDL_RenderDrawPoint(renderer, x, y);
      aacircleRGBA(renderer, x, y, radius, 255, 120, 120, SDL_ALPHA_OPAQUE);
    }
};