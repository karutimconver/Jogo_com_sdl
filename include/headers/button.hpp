#pragma once

#include <SDL/SDL.h>
#include <headers/text.hpp>

class Button {
private:
    int width;
    int height;
    bool hover; // Se o rato está ou não em cima do botão
    int x;
    int y;

    void check_mouse();
public:
    Text* text;
    bool pressed = false;
   
    Button(const char* text, int x, int y, int size, SDL_Renderer* renderer);
    void update();
    void draw(SDL_Renderer* renderer);
    const char * get_text();
};