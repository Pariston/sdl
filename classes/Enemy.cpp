#include "../headers/Enemy.h"
#include <SDL.h>

Enemy::Enemy(SDL_Texture* texture, double pos_x, double pos_y):
        texture(texture),
        pos_x(pos_x),
        pos_y(pos_y)
{}

void Enemy::draw(SDL_Renderer* renderer) {
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

    SDL_RenderCopyEx(renderer, texture, nullptr, &drectangle, 0, NULL, SDL_FLIP_HORIZONTAL);
}