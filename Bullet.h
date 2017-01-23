#pragma once
#include <SDL.h>

class Bullet {
public:
	Bullet(SDL_Renderer* renderer);
	void draw();
private:
	SDL_Renderer* renderer;
	int pos_x;
	int pos_y;
};