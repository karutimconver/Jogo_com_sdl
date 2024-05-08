#pragma once

#include <SDL/SDL.h>
#include <headers/text.hpp>

class Button {
private:
    Text* text;
    int width;
    int height;
    bool hover = false; // Se têm o não o rato em cima
    int x;
    int y;

    //void* func;
    void check_mouse();
public:
    Button(const char* text, int x, int y, int size, SDL_Renderer* renderer, void (func) ());
    void update();
    void draw(SDL_Renderer* renderer);
};