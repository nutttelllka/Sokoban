#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include "functions.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
using namespace std;


//Инициализация SDL и загрузка изображения
int main(int argc, char* argv[])
{
	// Запускаем SDL и создаем окно 
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Флаг основного цикла
			bool quit = false;

			//Обработчик событий
			//Структура
			SDL_Event e;

			int i = 0;
			int i_for_buttons = 0;
			int current_pressed_button = 0;
			SDL_Surface* CurrentSurface = NULL;

			while (!quit)
			{
				//Обработка событий в очереди, пока она не стала пустой
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
						break;
					}
					else if (i < 2)
					{
						CurrentSurface = Logos[i];
						//Применяем изображение
						SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, NULL);
						//Update the surface
						SDL_UpdateWindowSurface(Window);

						//Sleep(3000);
						SDL_Delay(2000);
						i++;
					}
					if (i == 2)
					{
						Mix_FreeMusic(music);
						music = NULL;
						menu(quit, i, i_for_buttons, current_pressed_button,  CurrentSurface);
					}
				}
			}
		}
	}
	close();
	return 0;
}

