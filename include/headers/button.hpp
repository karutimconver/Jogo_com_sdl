#pragma once

#include <SDL/SDL.h>
#include <headers/text.hpp>

class Button {
private:
    Text* text;

    bool check_pressed();
    bool check_hover();
public:
    Button(const char* text, int x, int y, int size, SDL_Renderer* renderer);
    void update();
    void draw(SDL_Renderer* renderer);
};