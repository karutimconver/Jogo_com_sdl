#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <iostream>
#include <math.h>

class Text {
private:
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_Rect rectangle;
    int size;
    const char* text;
    Uint8 color [3] = {255, 255, 255};
public:
    float x;
    float y;

    Text(const char* text, int x, int y, int size, SDL_Renderer* renderer);
    ~Text();
    void change_text(const char* text, SDL_Renderer* renderer);
    void change_color(Uint8 color [3], SDL_Renderer* renderer);
    const char * get_text();
    void draw(SDL_Renderer* renderer, int offsetx, int offsety);
};