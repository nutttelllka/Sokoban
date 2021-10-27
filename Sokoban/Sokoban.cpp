#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include "functions.h"
#include "Structures.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
using namespace std;



int main(int argc, char* argv[])
{
	Surface game;
	game.CurrentSurface = NULL;
	//game.music = NULL;
	game.Window = NULL;
	game.ScreenSurface = NULL;
	//Stealth();
	intro(game);
	//if (!init(surf)) 
	//{
	//	printf("Failed to initialize!\n");
	//}
	//else {
	//	if (!loadMedia(surf))
	//	{
	//		printf("Failed to load media!\n");
	//	}
	//	else
	//	{
	//		
	//		bool quit = false;
	//		SDL_Event e;
	//		int i = 0;
	//		int i_for_buttons = 0;
	//		int current_pressed_button = 0;
	//		SDL_Surface* CurrentSurface = NULL;
	//		while (!quit)
	//		{
	//			//Обработка событий в очереди, пока она не стала пустой
	//			while (SDL_PollEvent(&e) != 0)
	//			{
	//				if (e.type == SDL_QUIT)
	//				{
	//					quit = true;
	//					break;
	//				}
	//				else if (i < 2)
	//				{
	//					surf.CurrentSurface = Logos[i];
	//					SDL_BlitSurface(CurrentSurface, NULL, surf.ScreenSurface, NULL);
	//					SDL_UpdateWindowSurface(surf.Window);
	//					//Sleep(3000);
	//					SDL_Delay(2000);
	//					i++;
	//				}
	//				if (i == 2)
	//				{
	//					Mix_FreeMusic(surf.music);
	//					surf.music = NULL;
	//					menu(quit, i, i_for_buttons, current_pressed_button, surf);
	//				}
	//			}
	//		}
	//	}
	//}
	close(game);
	return 0;
	//Surface test;
	//test.ScreenSurface = NULL;
	
}

