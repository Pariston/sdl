#include "../headers/Bullet.h"
#include <SDL.h>

Bullet::Bullet(SDL_Renderer* renderer, double pos_x):
    renderer(renderer),
    pos_x(pos_x)
{
};

void Bullet::draw() {
/* Declaring the surface. */
    SDL_Surface *s;

/* Creating the surface. */
    s = SDL_CreateRGBSurface(0, 30, 30, 32, 0, 0, 0, 0);

/* Filling the surface with red color. */
    SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 0, 0));
    SDL_FreeSurface(s);
};