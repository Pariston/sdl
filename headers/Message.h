//
// Created by elzoy on 23.01.17.
//

#ifndef UNTITLED_MESSAGE_H
#define UNTITLED_MESSAGE_H

#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include "GameSettings.h"

using namespace std;

class Message {
public:
    Message(TTF_Font* font, string message, int pos_x, int pos_y);
    void draw(SDL_Renderer* renderer);
    string message;
    int pos_x;
    int pos_y;
private:
    GameSettings settings;
    TTF_Font* font;
};

#endif //UNTITLED_MESSAGE_H
