#include <button.hpp>

//  --------------
//  | Construtor |
//  --------------

Button::Button(const char* text, int x, int y, int size, SDL_Renderer* renderer, void (*func) ()) {
    this->text = new Text(text, x, y, size, renderer);
    
    this->x = x;
    this->y = y;
    this->func = func;

    this->width = strlen(text) * size;
    this->height = size;
};

// --------------------------------
// | Verificar se foi pressionado |
// --------------------------------

void Button::check_mouse() {
    int *mouse_x, *mouse_y;

    unsigned short int press_code = SDL_BUTTON(SDL_GetMouseState(mouse_x, mouse_y));

    if (this->y - this->height < *mouse_y < this->y - this->height && this->x - this->width < *mouse_x < this->x - this->width) {
        this->hover = true;

        if (press_code == 1) // Se for clicado o butão esquerdo do rato 
            this->func();
    }
}

// -----------------
// | Ciclo de jogo |
// -----------------

void Button::update(){

};

void Button::draw(SDL_Renderer* renderer){
    if (!hover) {
        int color [3] = {255, 255, 255};
        text->change_color(color, renderer);
    }
    else {
        int color [3] = {200, 180, 180};
        text->change_color(color, renderer);
    }

    text->draw(renderer);
};