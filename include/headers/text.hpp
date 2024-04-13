#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include <cstring>

class Text {
private:
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_Rect rectangle;
public:
    float x;
    float y;

    Text(const char* text, int x, int y, int size, SDL_Renderer* renderer);
    ~Text();
    void draw(SDL_Renderer* renderer);
};