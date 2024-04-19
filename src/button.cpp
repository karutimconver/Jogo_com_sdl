#include <button.hpp>

//  --------------
//  | Construtor |
//  --------------

Button::Button(const char* text, int x, int y, int size, SDL_Renderer* renderer) {
    this->text = new Text(text, x, y, size, renderer);
};

// -----------------
// | Ciclo de jogo |
// -----------------

void Button::update(){

};

void Button::draw(SDL_Renderer* renderer){
    text->draw(renderer);
};