#include "SDL.h"
#include <chrono>
#include <math.h> 
#include <vector>
#include "../headers/Game.h"
#include <SDL_ttf.h>
#include <sstream>
#include <SDL_mixer.h>

using namespace std;

SDL_Texture *loadTexture(SDL_Renderer* renderer, char* path) {
    SDL_Surface* surface = SDL_LoadBMP(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Game::draw() {
    SDL_Rect rectangle;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = settings.Width;
    rectangle.h = settings.Height;

    SDL_Rect drectangle;
    drectangle.x = 0;
    drectangle.y = 0;
    drectangle.w = settings.Width;
    drectangle.h = settings.Height;

    SDL_RenderCopyEx(renderer, background, nullptr, &drectangle, 0, NULL, SDL_FLIP_NONE);

}

Game::Game(SDL_Renderer *renderer) :
        font(TTF_OpenFont("../fonts/OpenSans-Regular.ttf", 55)),
        message(TTF_OpenFont("../fonts/OpenSans-Regular.ttf", 55), "", 20, 40),
        renderer(renderer),
        bird(renderer),
        birdTexture(loadTexture(renderer, "../bitmaps/bird2.bmp")),
        pipeTexture(loadTexture(renderer, "../bitmaps/pipe2.bmp"))
{
}

int Game::menu() {
    backgroundMusic = Mix_LoadMUS("../sounds/chickensong.mp3");
    restart();

    SDL_Event event;
    //title
    messages.emplace_back(font, "Trzepoczacy ptak", 20, 40);

    //menu
    messages.emplace_back(font, "1 - Rosyjski Nowy Rok - Baboshka", 20, 80);
    messages.emplace_back(font, "2 - Kubelek kurczakow", 20, 120);

    //levels
    messages.emplace_back(font, "Poziom trudnosci", 20, 40);
    messages.emplace_back(font, "1 - Dla mieczakow", 20, 80);
    messages.emplace_back(font, "2 - Dla kozakow", 20, 120);

    Mix_PlayMusic(backgroundMusic, -1);

    bool stepOne = true;
    bool stepTwo = false;

    while (inMenu) {
        if (stepOne) {
            for (int i = 0; i < messages.size(); i++) {
                if (i < 3) {
                    messages.at(i).draw(renderer);
                }
            }
        }
        else {
            for (int i = 0; i < messages.size(); i++) {
                if (i >= 3) {
                    messages.at(i).draw(renderer);
                }
            }
        }


        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                /* Look for a keypress */
                case SDL_QUIT:
                    running = false;
                case SDL_KEYDOWN:
                    /* Check the SDLKey values and move change the coords */
                    switch (event.key.keysym.sym) {
                        case SDLK_1:
                            if (stepOne) {
                                background = loadTexture(renderer, "../bitmaps/novygod.bmp");
                                backgroundMusic = Mix_LoadMUS("../sounds/nowygod.mp3");
                                pointSound = Mix_LoadWAV("../sounds/blyat.wav");
                                stepOne = false;
                                stepTwo = true;
                            }
                            else {
                                pipeSpeed = 0.5;
                                period = 1000;
                                inMenu = false;
                                running = true;
                                exec();
                            }
                            break;
                        case SDLK_2:
                            if (stepOne) {
                                background = loadTexture(renderer, "../bitmaps/nigga.bmp");
                                backgroundMusic = Mix_LoadMUS("../sounds/niggasong.mp3");
                                pointSound = Mix_LoadWAV("../sounds/damn.wav");
                                stepOne = false;
                                stepTwo = true;
                            }
                            else {
                                pipeSpeed = 1;
                                period = 500;
                                inMenu = false;
                                running = true;
                                exec();
                            }
                            break;
                        case SDLK_ESCAPE:
                            close();
                            break;
                        default:
                            break;
                    }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }

    Mix_CloseAudio();
    return 0;
}

int Game::exec() {
    Mix_Chunk* riseEffect = Mix_LoadWAV("../sounds/Powerup.wav");
    SDL_Event event;
    SDL_MouseButtonEvent mouseEvent;

    auto prevTime = chrono::system_clock::now();
    bool rise = false;
    double acceleration = 0;
    double speed = 0.98;
    int counter = 0;
    stringstream epoints;
    epoints << points;

    Mix_PlayMusic(backgroundMusic, -1);
    while (running) {
        draw();
        counter++;
        double dt = 0;
        chrono::duration<double> cdt; // frame time
        auto now = chrono::system_clock::now();
        cdt = now - prevTime; // przyrost czasu w sekundach
        dt = cdt.count();

        //bird
        bird.draw(birdTexture);



        if (!rise) {
            if (bird.angle < 0) {
                bird.angle += 140 * dt;
            }

            bird.pos_y += 300 * dt;
        }
        else {
            if (bird.angle > -60) {
                bird.angle -= 180 * dt;
            }
            if (speed <= 0.1) {
                rise = false;
                speed = 0.98;
            }
            else {
                bird.pos_y -= 450 * dt;
                speed -= speed * dt + acceleration*dt;
            }
        }

        prevTime = now;
        if (bird.pos_y >= settings.Height - 64) {
            bird.pos_y = 0;
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                /* Look for a keypress */
                case SDL_MOUSEBUTTONDOWN:
                    Mix_PlayChannel(-1, riseEffect, 0);
                    if (bird.pos_y >= 64) {
                        rise = true;
                        acceleration = 20;
                        speed = 9.8 / (dt * 1000);
                    }
                    break;
                case SDL_QUIT:
                    running = false;
                case SDL_KEYDOWN:
                    /* Check the SDLKey values and move change the coords */
                    switch (event.key.keysym.sym) {
                        case SDLK_SPACE:
                            Mix_PlayChannel(-1, riseEffect, 0);
                            if (bird.pos_y >= 64) {
                                rise = true;
                                acceleration = 20;
                                speed = 9.8 / (dt * 1000);
                            }
                            break;
                        case SDLK_x:
                            bullets.emplace_back(renderer, bird.pos_x);
                            break;
                        case SDLK_ESCAPE:
                            close();
                            break;
                        default:
                            break;
                    }
            }
        }

        //pipes
        if (counter % period == 0) {
            auto y = rand() % (settings.Height - 100 - 150 - 100) + 100;
            pipeList.emplace_back(pipeTexture, y + 250, false);
            pipeList.emplace_back(pipeTexture, y, true);
        }

        for (auto iter = begin(pipeList); iter != end(pipeList); )
        {
            if (iter->x < bird.pos_x && iter->done == false) {
                stringstream().swap(epoints);
                points++;
                epoints << points/2;
                iter->done = true;
                if(points % 20 == 0) {
                    auto y = rand() % (settings.Height - 100 - 150 - 100) + 100;
                    Mix_PlayChannel(-1, pointSound, 0);
                    enemies.emplace_back(birdTexture, settings.Width, y);
                }
            }
            else if (iter->x < -100) {
                iter = pipeList.erase(iter);
            }
            else
                ++iter;
        }

        SDL_Rect res;
        for (auto &pipe : pipeList) {
            pipe.draw(renderer, pipeTexture);
            pipe.x -= pipeSpeed;

            SDL_Rect birdRect;
            birdRect.x = bird.pos_x - 64 / 2;
            birdRect.y = bird.pos_y - 45 / 2;
            birdRect.w = 64;
            birdRect.h = 45;

            SDL_Rect pipeRect;
            pipeRect.x = pipe.x - 64 + 20;
            pipeRect.w = 150 - 40;
            pipeRect.h = 10000;

            //colision
            if (pipe.isUp)
            {
                pipeRect.y = pipe.y - 10000;
                if (SDL_IntersectRect(&birdRect, &pipeRect, &res))
                {
                    inMenu = true;
                    running = false;
                    menu();
                    break;
                }
            }
            else
            {
                pipeRect.y = pipe.y;
                if (SDL_IntersectRect(&birdRect, &pipeRect, &res))
                {
                    inMenu = true;
                    running = false;
                    menu();
                    break;
                }
            }
        }

        for (auto &enemy : enemies) {
            enemy.pos_x -= 0.5;
            enemy.draw(renderer);

            SDL_Rect birdRect;
            birdRect.x = bird.pos_x - 64 / 2;
            birdRect.y = bird.pos_y - 45 / 2;
            birdRect.w = 64;
            birdRect.h = 45;

            SDL_Rect enemyRect;
            enemyRect.x = enemy.pos_x - 64/2;
            enemyRect.y = enemy.pos_y - 64/2;
            enemyRect.w = 64;
            enemyRect.h = 45;

            if (SDL_IntersectRect(&birdRect, &enemyRect, &res))
            {
                inMenu = true;
                running = false;
                SDL_Delay(3000);
                menu();
                break;
            }
        }

        for (auto &bullet : bullets) {
            bullet.pos_x += 1.5;
            bullet.draw();
        }

        message.message = epoints.str();
        //printing points
        message.draw(renderer);

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
    Mix_CloseAudio();
    return 0;
}

void Game::restart() {
    pipeSpeed = 0.5;
    period = 1000;
    messages.clear();
    pipeList.clear();
    bird.pos_x = settings.Width / 2;
    bird.pos_y = settings.Height / 2;
    points = 0;
}

void Game::close() {
    SDL_Quit();
    TTF_Quit();
    running = false;
    inMenu = false;
}