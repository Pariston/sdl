#include "SDL.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include "../headers/Bird.h"

using namespace std;

Bird::Bird(SDL_Renderer* renderer):
        renderer(renderer)
{
}

void Bird::draw(SDL_Texture* texture) {
    SDL_Rect rectangle;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 64;
    rectangle.h = 45;

    SDL_Rect drectangle;
    drectangle.x = pos_x;
    drectangle.y = pos_y;
    drectangle.w = 64;
    drectangle.h = 45;

    SDL_RenderCopyEx(renderer, texture, nullptr, &drectangle, angle, NULL, SDL_FLIP_NONE);
}
