#include <headers/asteroids.hpp>

// ---------------------------
// | Construtor e Destruidor |
// ---------------------------

Asteroid::Asteroid(int x, int y, int size) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->radius = r * size;

    this->speed = (((rand() % 100) * 0.1) - 4) / 2 / size;
    float x_speed_percentage = (rand() % 100) * 0.01;
    this->velocity.x = this->speed * x_speed_percentage;
    this->velocity.y = this->speed - velocity.x;

    this->angular_speed = (((rand() % 30) * 0.1) - 1.5) / size;

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
    this->angle += this->angular_speed;
};

void Asteroid::move() {
    this->x += this->velocity.x;
    this->y += this->velocity.y;
};

// -----------------
// | Ecrã infinito |
// -----------------

void Asteroid::screen_wrap(){
  if (this->y + this->radius < 0)
    this->y = SCREEN_HEIGH + this->radius;
  else if (this->y - this->radius > SCREEN_HEIGH)
    this->y = 0 - this->radius;

  if (this->x + this->radius < 0)
    this->x = SCREEN_WIDTH + this->radius;
  else if (this->x - this->radius > SCREEN_WIDTH)
    this->x = 0 - this->radius; 
};

// -----------------
// | Ciclo do jogo |
// -----------------

void Asteroid::update() {
    this->rotate();
    this->move();
    this->screen_wrap();
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