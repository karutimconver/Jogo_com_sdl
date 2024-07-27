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

  // crianção de vértices
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
    this->y = SCREEN_HEIGHT + this->radius;
  else if (this->y - this->radius > SCREEN_HEIGHT)
    this->y = 0 - this->radius;

  if (this->x + this->radius < 0)
    this->x = SCREEN_WIDTH + this->radius;
  else if (this->x - this->radius > SCREEN_WIDTH)
    this->x = 0 - this->radius; 
};


// -----------
// | Colisão |
// -----------

void Asteroid::collide(std::vector<Laser*>* lasers, std::vector<Ship*>* players) {
  for (Laser *laser : *lasers) {
    if (this->radius > calculate_distance(laser->x, laser->y, this->x, this->y)) {
      laser->to_delete = true;
      this->hit = true;
    }
  }

  for (Ship *player : *players) {
    if (this->radius + player->radius > calculate_distance(player->x, player->y, this->x, this->y)) {
      if (!player->invincible) {
        this->hit = true;
        player->hit = true;
      }
    }
  }
};

// -----------------
// | Ciclo do jogo |
// -----------------

void Asteroid::update(std::vector<Laser*>* lasers, std::vector<Ship*>* players) {
  this->rotate();
  this->move();
  this->screen_wrap();
  this->collide(lasers, players);
};

void Asteroid::draw(SDL_Renderer* renderer, int offsetx, int offsety, Uint8 opacity) {
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
      array_x[j] = round(x + points[j][0] * cos(points[j][1] * M_PI / 180)) + offsetx;
      array_y[j] = round(y + points[j][0] * sin(points[j][1] * M_PI / 180)) + offsety;
  }

  // Desenhar
  aapolygonRGBA(renderer, array_x, array_y, this->vertices, 255, 255, 255, opacity);

  if (DEBUGGING) {
    aacircleRGBA(renderer, x + offsetx, y + offsety, 0, 255, 120, 120, opacity);
    aacircleRGBA(renderer, x + offsetx, y + offsety, radius, 255, 120, 120, opacity);
  }
};