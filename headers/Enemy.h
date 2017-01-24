//
// Created by elzoy on 24.01.17.
//
#include <SDL.h>
#include "GameSettings.h"
#ifndef UNTITLED_ENEMY_H
#define UNTITLED_ENEMY_H
#pragma once
class Enemy {
public:
    Enemy(SDL_Texture* texture, double pos_x, double pos_y);
    void draw(SDL_Renderer* renderer);
    double pos_x;
    double pos_y;
private:
    SDL_Texture* texture;
};
#endif //UNTITLED_ENEMY_H
