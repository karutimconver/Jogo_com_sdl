#include <headers/text.hpp>

// ---------------------------
// | Construtor e destruidor |
// ---------------------------

Text::Text(const char* text, int x, int y, int size, SDL_Renderer* renderer) {
    this->x = x;
    this->y = y;
    this->font = TTF_OpenFont("./fonts/retro.ttf", size);

    SDL_Surface* surface = TTF_RenderText_Solid(this->font, text, {255, 255, 255});
    
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    
    rectangle.w = strlen(text) * size;
    rectangle.h = size;
};

Text::~Text() {
    this->font = NULL;
};


// -----------
// | Desenho |
// -----------

void Text::draw(SDL_Renderer* renderer) {
    rectangle.x = round(this->x);
    rectangle.y = round(this->y);

    SDL_RenderCopy(renderer, this->texture, NULL, &this->rectangle);
}