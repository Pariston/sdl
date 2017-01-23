#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "gameSettings.h"

class Bird {
public:
	Bird(SDL_Renderer *renderer);
	void draw(SDL_Texture* texture);
	GameSettings settings;
	double pos_x = settings.Width/2;
	double pos_y = settings.Height/2;
	double angle = 0.0;
private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
};