#include "SDL.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include "gameSettings.h"
#include <math.h> 

using namespace std;

class Pipe {
public:
	Pipe() {}
	Pipe(SDL_Texture* _texture, int _y, bool _isUp) :
		texture(_texture),
		y(_y),
		isUp(_isUp)
	{
	}

	SDL_Rect rectangle;
	SDL_Rect rectangle2;
	GameSettings settings;
	SDL_Texture* texture;
	bool done = false;
	int width = 100;
	int space = 300;

	int y;
	double x = settings.Width;

	int savedSpace = settings.Width - x;

	int buffer = 200;
	int aSpace = settings.Height - buffer;
	int h = rand() % aSpace;
	int h2 = aSpace - h;
	bool isUp;

	void draw(SDL_Renderer* renderer, SDL_Texture* texture) {
		if (!isUp)
		{
			SDL_Rect r;
			r.x = x - 64;
			r.y = y;
			r.w = 150;
			r.h = 700;
			auto res = SDL_RenderCopyEx(renderer, texture, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
			if (res != 0)
 				throw std::runtime_error(std::string("SDL_RenderCopy ") + SDL_GetError());
		}
		else
		{
			SDL_Rect r;
			r.x = x - 64;
			r.y = y - settings.Height;
			r.w = 150;
			r.h = 700;
			auto res = SDL_RenderCopyEx(renderer, texture, nullptr, &r, 0, nullptr, SDL_FLIP_VERTICAL);
			if (res != 0)
				throw std::runtime_error(std::string("SDL_RenderCopy ") + SDL_GetError());
		}
	}
};