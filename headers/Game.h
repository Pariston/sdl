//
// Created by elzoy on 23.01.17.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H

#pragma once
#include <SDL.h>
#include <vector>
#include "Bird.h"
#include "../classes/Pipe.cpp"
#include "Message.h"
#include <SDL_mixer.h>
#include "Enemy.h"
#include "Bullet.h"

class Game
{
public:
    Game(SDL_Renderer *renderer);
    int menu();
    int exec();
    void draw();
    void close();
    void restart();
private:
    bool inMenu = true;
    bool running = false;
    SDL_Renderer *renderer;
    SDL_Texture *pipeTexture;
    SDL_Texture *birdTexture;
    SDL_Texture *background;
    Bird bird;
    vector<Message> messages;
    vector<Enemy> enemies;
    Message message;
    GameSettings settings;
    vector<Pipe> pipeList;
    Mix_Music* backgroundMusic = Mix_LoadMUS("c:\\chickensong.mp3");
    Mix_Chunk* pointSound;
    double pipeSpeed = 0.5;
    int period = 1000;
    TTF_Font* font;
    int counter = 0;
    int points = 0;
    vector<Bullet> bullets;
};

#endif //UNTITLED_GAME_H
