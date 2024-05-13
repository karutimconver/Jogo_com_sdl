#include <button.hpp>
#include <iostream>

//  --------------
//  | Construtor |
//  --------------

Button::Button(const char* text, int x, int y, int size, SDL_Renderer* renderer){
    this->text = new Text(text, x, y, size, renderer);
    
    this->x = x;
    this->y = y;

    this->width = strlen(text) * size / 2;
    this->height = size / 2;
};

// --------------------------------
// | Verificar se foi pressionado |
// --------------------------------

void Button::check_mouse() {
    int mouse_x;
    int mouse_y;

    Uint32 state = SDL_GetMouseState(&mouse_x, &mouse_y);

    if (this->x - width < mouse_x && mouse_x < this->x + width && this->y - height < mouse_y && mouse_y < this->y + height) {
        this->hover = true;
    
        if (SDL_BUTTON(state) == 1) this->pressed = true;
    }
    else {
        this->hover = false;
    }
};

// -----------
// | Getters |
// -----------

const char * Button::get_text() {
    return this->text->get_text();
};

// -----------------
// | Ciclo de jogo |
// -----------------

void Button::update(){
    this->check_mouse();
};

void Button::draw(SDL_Renderer* renderer){
    //if (!hover) {
    //    int color [3] = {255, 255, 255};
    //    text->change_color(color, renderer);
    //}
    //else {
    //    int color [3] = {200, 180, 180};
    //    text->change_color(color, renderer);
    //}

    text->draw(renderer);
};