#pragma once

#include <SDL/SDL.h>
#include <headers/text.hpp>

class Button {
private:
    int width;
    int height;
    int x;
    int y;
    int ox;
    int oy;

    void check_mouse();
public:
    Text* text;
    bool hover; // Se o rato está ou não em cima do botão
    bool pressed = false;
   
    Button(const char* text, int x, int y, int size, SDL_Renderer* renderer);
    void update();
    void draw(SDL_Renderer* renderer, int offsetx, int offsety);
    const char * get_text();
};