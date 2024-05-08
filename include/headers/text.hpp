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
    int size;
    const char* text;
public:
    float x;
    float y;
    int color [3] = {255, 255, 255};

    Text(const char* text, int x, int y, int size, SDL_Renderer* renderer);
    ~Text();
    void change_text(const char* text, SDL_Renderer* renderer);
    void change_color(int color [3], SDL_Renderer* renderer);
    void draw(SDL_Renderer* renderer);
};