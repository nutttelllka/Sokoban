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
};

class PlayField
{
	int height;
	int width;
	int count_place;
	int result;
	
	int count_levels;
public:
	vector<vector<int>> level;
	vector<vector<int>> catAndGift;
	PlayField() {
		height = 0;
		width = 0;
		count_place = 0;
		result = 0;
		count_levels = 5;
	}
	void SetHeight(int height) {
		this->height = height;
	}
	void SetWidth(int width) {
		this->width = width;
	}
	void SetCountPlace(int count) {
		count_place = count;
	}
	void SetResult(int result) {
		this->result = result;
	}
	void SetCountLevels(int count) {
		count_levels = count;
	}
	int GetHeight() {
		return height;
	}
	int GetWidth() {
		return width;
	}
	int GetCountPlace() {
		return count_place;
	}
	int GetResult() {
		return result;
	}
	int GetCountLevels() {
		return count_levels;
	}
	
	

};
//struct Surface
//{
//	//SDL_Surface* loadSurface(string path);
//
//
//	Mix_Music* music1;
//	Mix_Music* music2;
//	Mix_Chunk* box = NULL;
//	Mix_Chunk* button = NULL;
//	Mix_Chunk* win = NULL;
//	Mix_Chunk* intro = NULL;
//	//Mix_Music* AllMusic[2];
//
//	SDL_Surface* CurrentSurface;
//	SDL_Window* Window;
//	SDL_Surface* ScreenSurface;
//	SDL_Surface* Wallps[CountOfWallps];
//	SDL_Surface* Buttons[CountOfButtons];
//	SDL_Surface* PressedButtons[CountOfPressedButtons];
//	SDL_Surface* Texture[CountOfTexture];
//	SDL_Surface* WindowsHowToPlay[CountOfWindows];
//	SDL_Surface* Numbers[CountOfNumbers];
//	SDL_Surface* WindowLevel[CountOfLeveles];
//	SDL_Surface* Comic[CountOfComic];
//	SDL_Event e;
//	PlayField infOfFild;
//
//	//int result = 0;
//	//int count_step = 0;
//	//int count_levels = 5;
//
//
//};
