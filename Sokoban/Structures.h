#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "enums.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
using namespace std;

struct Texture
{
	SDL_Rect posTexture;
	int X = 0;
	int Y = 0;
	int sizeTexture = 50;
	//Texture* textures_of_leveles[5];
	/*int x_cat;
	int y_cat;
	int x_box;
	int y_box;*/

};
//Texture* texture_of_level = new Texture[5];
//struct AllTextures
//{
//	//const int count_of_textures = 5;
//	Texture* texture_of_level[5];
//};
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
	SDL_Event e;
	/*SDL_Surface* Logos[CountOfLogos];
	SDL_Surface* Buttons[CountOfButtons];
	SDL_Surface* PressedButtons[CountOfPressedButtons];
	SDL_Surface* Texture[CountOfTexture];*/
};