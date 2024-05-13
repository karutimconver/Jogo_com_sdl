#include <headers/text.hpp>

// ---------------------------
// | Construtor e destruidor |
// ---------------------------

Text::Text(const char* text, int x, int y, int size, SDL_Renderer* renderer) {
    this->x = x;
    this->y = y;
    this->text = text;
    this->size = size;
    this->font = TTF_OpenFont("./fonts/arcade.ttf", size);

    SDL_Surface* surface = TTF_RenderText_Solid(this->font, text, {255, 255, 255});
    
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    
    rectangle.w = strlen(text) * this->size;
    rectangle.h = this->size;
};

Text::~Text() {
    this->font = NULL;
    this->texture = NULL;
};

// ------------------
// | Outras funções |
// ------------------

void Text::change_text(const char* text, SDL_Renderer* renderer) {
    SDL_Surface* surface = TTF_RenderText_Solid(this->font, text, {255, 255, 255});
    
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    
    rectangle.w = strlen(text) * this->size;
    rectangle.h = strlen(text) * this->size;
};

void Text::change_color(int color [3], SDL_Renderer* renderer) {
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];

    change_text(text, renderer);
};

const char * Text::get_text() {
    return this->text;
};

// -----------
// | Desenho |
// -----------

void Text::draw(SDL_Renderer* renderer) {
    rectangle.x = round(this->x - (rectangle.w / 2));  // Alinhamento no eixo Oy
    rectangle.y = round(this->y - (rectangle.h / 2));  // Alinhamento no eixo Ox

    SDL_RenderCopy(renderer, this->texture, NULL, &this->rectangle);
}