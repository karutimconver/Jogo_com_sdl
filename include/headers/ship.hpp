#pragma once
#include <SDL/SDL2_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <headers/globals.hpp>
#include <unordered_map>

class Ship {
private:
    std::unordered_map<std::string, int> keys;
    Vec2 velocity;
    int thrust    = 10;
    int friction  = 5;
public:
    unsigned short int angle = 0; // ângulo em graus
    unsigned short int lives;
    unsigned short int x;
    unsigned short int y;
    float angular_speed = 2;      // velocidade com que gira em graus por tick 

    Ship(unsigned short int lives, unsigned short int x, unsigned short int y, int keys [3]);
    ~Ship();
    void rotate(const Uint8* keyboard_state);
    void controls(const Uint8* keyboard_state);
    void move();
    void update(const Uint8* keybaoard_state);
    void aply_friction();
    void draw(SDL_Renderer* renderer);
};
