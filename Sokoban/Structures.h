#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "enums.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
using namespace std;

struct Test
{

};
struct Surface
{
	//SDL_Surface* loadSurface(string path);


	SDL_Surface* CurrentSurface ;
	Mix_Music* music ;
	SDL_Window* Window ;
	SDL_Surface* ScreenSurface ;
	SDL_Surface* Logos[CountOfLogos];
	SDL_Surface* Buttons[CountOfButtons];
	SDL_Surface* PressedButtons[CountOfPressedButtons];
	SDL_Surface* Texture[CountOfTexture];
	SDL_Surface* WindowsHowToPlay[CountOfWindows];
	/*SDL_Surface* Logos[CountOfLogos];
	SDL_Surface* Buttons[CountOfButtons];
	SDL_Surface* PressedButtons[CountOfPressedButtons];
	SDL_Surface* Texture[CountOfTexture];*/
};