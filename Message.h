#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include "gameSettings.h"

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