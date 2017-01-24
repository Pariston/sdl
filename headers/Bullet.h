//
// Created by elzoy on 24.01.17.
//
#include <SDL.h>
#ifndef UNTITLED_BULLET_H
#define UNTITLED_BULLET_H
#pragma once

class Bullet {
public:
    Bullet(SDL_Renderer* renderer, double pos_x);
    void draw();
    double pos_x;
    double pos_y;
private:
    SDL_Renderer* renderer;
};

#endif //UNTITLED_BULLET_H
