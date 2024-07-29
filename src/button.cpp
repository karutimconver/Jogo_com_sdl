#include <button.hpp>
#include <iostream>

//  --------------
//  | Construtor |
//  --------------

Button::Button(const char* text, int x, int y, int size, SDL_Renderer* renderer){
    this->text = new Text(text, x, y, size, renderer);
    this->hover = false;
    this->x = x;
    this->y = y;
    this->ox = x;
    this->oy = y;

    this->bwidth = strlen(text) * size / 2;
    this->bheight = size / 2;

    this->width = bwidth;
    this->height = bheight;
};

// --------------------------------
// | Verificar se foi pressionado |
// --------------------------------

void Button::check_mouse() {
    this->pressed = false;

    int mouse_x;
    int mouse_y;

    Uint32 state = SDL_GetMouseState(&mouse_x, &mouse_y);


    if (this->x - width < mouse_x && mouse_x < this->x + width && this->y - height < mouse_y && mouse_y < this->y + height) {
        this->hover = true;
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

void Button::draw(SDL_Renderer* renderer, int offsetx, int offsety, float scalefactor){
    x = (ox + offsetx) * scalefactor;
    y = (oy + offsety) * scalefactor;
    width = bwidth * scalefactor;
    height = bheight * scalefactor;

    text->x = ox + offsetx;
    text->y = oy + offsety;

    if (hover) {
        Uint8 color [3] = {250, 247, 62};
        this->text->change_color(color, renderer);
    }
    else {   
        Uint8 color [3] = {255, 255, 255};
        this->text->change_color(color, renderer);
    }

    text->draw(renderer, 0, 0);
};