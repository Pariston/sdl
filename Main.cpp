#include "headers/Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* args[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    auto res = SDL_Init(SDL_INIT_EVERYTHING);
    if (res != 0)
        throw std::runtime_error(std::string("SDL_Init(SDL_INIT_EVERYTHING)") + SDL_GetError());
    SDL_CreateWindowAndRenderer(1280, 720, NULL, &window, &renderer);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetWindowPosition(window, 65, 126);
    SDL_SetRenderDrawColor(renderer, 47, 47, 47, 1);
    srand(time(NULL));

    Game game(renderer);
    game.menu();
    return 0;
}