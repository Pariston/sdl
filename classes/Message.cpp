#include <SDL.h>
#include "../headers/Message.h"
#include <SDL_ttf.h>
#include <string>

using namespace std;

Message::Message(TTF_Font* font, string message, int pos_x, int pos_y):
        font(font),
        message(message),
        pos_x(pos_x),
        pos_y(pos_y)
{}

void Message::draw(SDL_Renderer* renderer) {
    TTF_SetFontOutline(font, 2);

    SDL_Color White = { 84, 234, 50 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, message.c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = pos_x;  //controls the rect's x coordinate
    Message_rect.y = pos_y; // controls the rect's y coordinte

    int w;
    int h;

    if (TTF_SizeText(font, message.c_str(), &w, &h)) {
        // perhaps print the current TTF_GetError(), the string can't be rendered...
    }
    else {
        Message_rect.w = w; // controls the width of the rect
        Message_rect.h = 40; // controls the height of the rect
    }

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

//pos_x = 20
//settings.Height - 40;