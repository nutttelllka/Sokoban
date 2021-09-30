#pragma once
#include "Structures.h"
#include "Enums.h"
#include <vector>
using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
//#define KMOD_CTRL_z (SDLK_LCTRL|SDLK_z)
void intro(Surface& game);
bool init(Surface& game);
bool loadMedia(Surface& game);
void close(Surface& game);
void menu(bool& quit, int i, int& i_for_buttons, int& current_pressed_button, Surface& game);
void playGame(Surface& game, bool& quit);
void showButton(Surface& game, int i, SDL_Rect stretchRectб, int y_of_button1 = 250, int y_of_button2 = 250 + 70, int y_of_button3 = 250 + 140);
void backgroundMenu(Surface& game);
void exit(bool& quit, Surface& game);
void createMap(Surface& game, vector<vector<int>>& array, fstream& file);
void field(vector<vector<int>> level, fstream& file, SDL_Rect posTexture, Surface& game);
void characterMovement(vector<vector<int>>& level, fstream& file, Surface& game, bool& quit);
void showTexture(int i, SDL_Rect posTexture, Surface& game);
bool isPressed(int keyCode);
bool isReleased(int keyCode);
void howToPlay(Surface& game, bool quit, int count = 0);
bool win(Surface& game, vector<vector<int>> level, vector<vector<int>> copy_catAndGift);
//bool playingLevel(Surface& game, fstream& file, int** catAndGift, int**& level, Texture* texture_of_level, bool quit, int keydown_for_box = KEY_PRESS_DEFAULT, int count = 9);
int playingLevel(Surface& game, fstream& file, vector<vector<int>> catAndGift, vector<vector<int>> level, vector < Texture> texture_of_elements, bool& quit);
bool pressed_keys[7] = {};



//тут был Степа
SDL_Surface* loadSurface(string path);


//void Stealth()
//{
//	HWND Stealth;
//	AllocConsole();
//	Stealth = FindWindowA("ConsoleWindowClass", NULL);
//	ShowWindow(Stealth, 0);
//}
void intro(Surface& game)
{
	if (!init(game))
	{
		printf("Failed to initialize!\n");
	}
	else {
		if (!loadMedia(game))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			int i = 0;
			int i_for_buttons = 0;
			int current_pressed_button = 0;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
						break;
					}
					else if (i < 2)
					{
						game.CurrentSurface = game.Logos[i];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
						SDL_UpdateWindowSurface(game.Window);
						//Sleep(3000);
						SDL_Delay(2000);
						i++;
					}
					if (i == 2)
					{
						/*Mix_FreeMusic(game.music);
						game.music = NULL;*/
						menu(quit, i, i_for_buttons, current_pressed_button, game);
					}
				}
			}
		}
	}
}
void backgroundMenu(Surface& game)
{
	game.CurrentSurface = game.Logos[2];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
	SDL_UpdateWindowSurface(game.Window);
}
void menu(bool& quit, int i, int& i_for_buttons, int& current_pressed_button, Surface& game)
{
	SDL_Event e;
	SDL_Rect stretchRect;
	stretchRect.x = 270;
	stretchRect.y = 250;
	int current_y = 250;
	int y_of_button1 = 250;
	int y_of_button2 = y_of_button1 + 70;
	int y_of_button3 = y_of_button2 + 70;
	int interval_Y = 70;

	backgroundMenu(game);
	game.CurrentSurface = game.PressedButtons[i_for_buttons];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
	SDL_UpdateWindowSurface(game.Window);
	stretchRect.y += interval_Y;
	i_for_buttons++;
	for (; i_for_buttons < 3; i_for_buttons)
	{
		game.CurrentSurface = game.Buttons[i_for_buttons];
		SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
		SDL_UpdateWindowSurface(game.Window);
		stretchRect.y += interval_Y;
		i_for_buttons++;
	}
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			/*		else if (i_for_buttons == 0)
					{
						game.CurrentSurface = game.PressedButtons[i_for_buttons];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
						SDL_UpdateWindowSurface(game.Window);
						stretchRect.y += interval_Y;
						i_for_buttons++;
					}*/
					//else if (i_for_buttons < 3)
					//{
					//	game.CurrentSurface = game.Buttons[i_for_buttons];
					//	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
					//	SDL_UpdateWindowSurface(game.Window);
					//	stretchRect.y += interval_Y;
					//	i_for_buttons++;
					//}
			else if (e.type == SDL_KEYDOWN)
			{
				//Select surfaces based on key press
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					if (current_pressed_button > 0)
					{
						current_pressed_button--;

						if (current_pressed_button == GAME)
							showButton(game, HOW_TO_PLAY, stretchRect);

						else if (current_pressed_button == HOW_TO_PLAY)
							showButton(game, EXIT, stretchRect);

						current_y -= interval_Y;
						stretchRect.y = current_y;
						game.CurrentSurface = game.PressedButtons[current_pressed_button];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
						SDL_UpdateWindowSurface(game.Window);
					}
					break;

				case SDLK_DOWN:
					if (current_pressed_button < 2)
					{

						current_pressed_button++;

						if (current_pressed_button == EXIT)
							showButton(game, HOW_TO_PLAY, stretchRect);

						else if (current_pressed_button == HOW_TO_PLAY)
							showButton(game, GAME, stretchRect);

						current_y += interval_Y;
						stretchRect.y = current_y;
						game.CurrentSurface = game.PressedButtons[current_pressed_button];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
						SDL_UpdateWindowSurface(game.Window);
					}
					break;
				case SDLK_ESCAPE:
					//current_pressed_button = EXIT;
					exit(quit, game);
					backgroundMenu(game);
					if (current_pressed_button == GAME)
					{
						showButton(game, HOW_TO_PLAY, stretchRect);
						showButton(game, EXIT, stretchRect);
						stretchRect.y = y_of_button1;
					}
					else if (current_pressed_button == HOW_TO_PLAY)
					{
						showButton(game, GAME, stretchRect);
						showButton(game, EXIT, stretchRect);
						stretchRect.y = y_of_button2;
					}
					else
					{
						showButton(game, GAME, stretchRect);
						showButton(game, HOW_TO_PLAY, stretchRect);
						stretchRect.y = y_of_button3;
					}
					game.CurrentSurface = game.PressedButtons[current_pressed_button];
					SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
					SDL_UpdateWindowSurface(game.Window);
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
					switch (current_pressed_button)
					{
					case GAME:
						Mix_PlayChannel(-1, game.button, 0) == -1;
						playGame(game, quit);
						backgroundMenu(game);
						showButton(game, HOW_TO_PLAY, stretchRect);
						showButton(game, EXIT, stretchRect);
						stretchRect.y = y_of_button1;
						break;
					case HOW_TO_PLAY:
						Mix_PlayChannel(-1, game.button, 0) == -1;
						howToPlay(game, quit);
						backgroundMenu(game);
						showButton(game, GAME, stretchRect);
						showButton(game, EXIT, stretchRect);
						stretchRect.y = y_of_button2;
						break;
					case EXIT:
						Mix_PlayChannel(-1, game.button, 0) == -1;
						exit(quit, game);
						backgroundMenu(game);
						showButton(game, GAME, stretchRect);
						showButton(game, HOW_TO_PLAY, stretchRect);
						stretchRect.y = y_of_button3;
						break;
					}
					game.CurrentSurface = game.PressedButtons[current_pressed_button];
					SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
					SDL_UpdateWindowSurface(game.Window);
					break;
				default:
					break;
				}
			}
		}
	}
}
void howToPlay(Surface& game, bool quit, int count)
{
	//if (count == 0)return true;
	//bool quit = false;
	SDL_Event e;
	SDL_Rect stretchRect;
	stretchRect.x = 170;
	stretchRect.y = 450;
	//int count = 0;
	//switch (count)
	//{
	//case FIRST:
	//	game.CurrentSurface = game.WindowsHowToPlay[FIRST];
	//	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
	//	SDL_UpdateWindowSurface(game.Window);
	//	break;
	//case SECOND:
	//	game.CurrentSurface = game.WindowsHowToPlay[SECOND];
	//	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
	//	SDL_UpdateWindowSurface(game.Window);
	//	break;
	//case THIRD:
	//	game.CurrentSurface = game.WindowsHowToPlay[THIRD];
	//	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
	//	SDL_UpdateWindowSurface(game.Window);
	//	break;
	//case FOURTH:
	//	game.CurrentSurface = game.WindowsHowToPlay[FOURTH];
	//	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
	//	SDL_UpdateWindowSurface(game.Window);
	//	break;
	//default:
	//	return;
	//}

	//game.CurrentSurface = game.WindowsHowToPlay[FIRST];
	//SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
	//SDL_UpdateWindowSurface(game.Window);
	game.CurrentSurface = game.WindowsHowToPlay[FIRST];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
	SDL_UpdateWindowSurface(game.Window);
	game.CurrentSurface = game.Buttons[BACK];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
	SDL_UpdateWindowSurface(game.Window);
	stretchRect.x += 420;
	game.CurrentSurface = game.Buttons[NEXT];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
	SDL_UpdateWindowSurface(game.Window);

	while (quit == false)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				Mix_PlayChannel(-1, game.button, 0) == -1;
				switch (e.key.keysym.sym)
				{
				case SDLK_RIGHT:
					count++;
					game.CurrentSurface = game.PressedButtons[NEXT];
					SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
					SDL_UpdateWindowSurface(game.Window);
					SDL_Delay(200);
					//howToPlay(game, quit,count);
					switch (count)
					{
					case SECOND:
						game.CurrentSurface = game.WindowsHowToPlay[SECOND];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
						SDL_UpdateWindowSurface(game.Window);
						break;
					case THIRD:
						game.CurrentSurface = game.WindowsHowToPlay[THIRD];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
						SDL_UpdateWindowSurface(game.Window);
						break;
					case FOURTH:
						game.CurrentSurface = game.WindowsHowToPlay[FOURTH];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
						SDL_UpdateWindowSurface(game.Window);
						break;
					default:
						return;
					}
					break;

				case SDLK_LEFT:
					count--;
					stretchRect.x = 170;
					game.CurrentSurface = game.PressedButtons[BACK];
					SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
					SDL_UpdateWindowSurface(game.Window);
					SDL_Delay(200);
					switch (count)
					{
					case FIRST:
						game.CurrentSurface = game.WindowsHowToPlay[FIRST];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
						SDL_UpdateWindowSurface(game.Window);
						break;
					case SECOND:
						game.CurrentSurface = game.WindowsHowToPlay[SECOND];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
						SDL_UpdateWindowSurface(game.Window);
						break;
					case THIRD:
						game.CurrentSurface = game.WindowsHowToPlay[THIRD];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
						SDL_UpdateWindowSurface(game.Window);
						break;
					default:
						return;
					}
					break;
				}
				stretchRect.x = 170;
				game.CurrentSurface = game.Buttons[BACK];
				SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
				SDL_UpdateWindowSurface(game.Window);
				stretchRect.x += 420;
				game.CurrentSurface = game.Buttons[NEXT];
				SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
				SDL_UpdateWindowSurface(game.Window);
			}
			if (quit == true)break;
		}
	}
}
void playGame(Surface& game, bool& quit)
{
	fstream file("fields.TXT");

	
	vector<vector<int>> level;
	int height = 0;
	int width = 0;

	createMap(game, level, file);
	characterMovement(level,  file, game, quit);
	
}
void showArrInConsole(vector<vector<int>> arr, int width, int hight)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
}
void movementOfCat()
{

}
int playingLevel(Surface& game, fstream& file, vector<vector<int>> catAndGift, vector<vector<int>> level, vector < Texture> texture_of_elements, bool& quit)
{
	vector<Texture> copy_texture = texture_of_elements;
	vector<vector<int>> copy_catAndGift = catAndGift;
	static int keydown_for_cat;
	static int keydown_for_box = KEY_PRESS_DEFAULT;
	copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = 0;

	switch (keydown_for_cat)
	{
	case SDLK_UP:
		copy_texture[CAT].Y--;
		copy_texture[CAT].posTexture.y -= copy_texture[CAT].sizeTexture;
		break;
	case SDLK_DOWN:
		copy_texture[CAT].Y++;
		copy_texture[CAT].posTexture.y += copy_texture[CAT].sizeTexture;
		break;
	case SDLK_LEFT:
		copy_texture[CAT].X--;
		copy_texture[CAT].posTexture.x -= copy_texture[CAT].sizeTexture;
		break;
	case SDLK_RIGHT:
		copy_texture[CAT].X++;
		copy_texture[CAT].posTexture.x += copy_texture[CAT].sizeTexture;
		break;
	}
	if (keydown_for_box != KEY_PRESS_DEFAULT)
	{
		switch (keydown_for_box)
		{
		case SDLK_UP:
			copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y - copy_texture[CAT].sizeTexture;
			copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x;
			copy_texture[PRESENT].Y = copy_texture[CAT].Y - 1;
			copy_texture[PRESENT].X = copy_texture[CAT].X;
			break;
		case SDLK_DOWN:
			copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y + copy_texture[CAT].sizeTexture;
			copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x;
			copy_texture[PRESENT].Y = copy_texture[CAT].Y + 1;
			copy_texture[PRESENT].X = copy_texture[CAT].X;
			break;
		case SDLK_LEFT:
			copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y;
			copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x - copy_texture[CAT].sizeTexture;
			copy_texture[PRESENT].Y = copy_texture[CAT].Y;
			copy_texture[PRESENT].X = copy_texture[CAT].X - 1;
			break;
		case SDLK_RIGHT:
			copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y ;
			copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x + copy_texture[CAT].sizeTexture;
			copy_texture[PRESENT].Y = copy_texture[CAT].Y ;
			copy_texture[PRESENT].X = copy_texture[CAT].X + 1;
			break;
		}
		keydown_for_box = KEY_PRESS_DEFAULT;
		showTexture(PRESENT, copy_texture[PRESENT].posTexture, game);
		copy_catAndGift[copy_texture[PRESENT].Y][copy_texture[PRESENT].X] = PRESENT;
	}
	

	showTexture(CAT, copy_texture[CAT].posTexture, game);
	copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = CAT;


	if (win(game, level,  copy_catAndGift))return WIN;
	showArrInConsole(copy_catAndGift, 9, 9);

	while (!quit)
	{
		while (SDL_PollEvent(&game.e) != 0)
		{
			if (game.e.type == SDL_QUIT)
			{
				exit(quit, game);
				showTexture(BACKGROUND, copy_texture[BACKGROUND].posTexture, game);
				field(level, file, copy_texture[CAT].posTexture, game);
				field(catAndGift, file, copy_texture[CAT].posTexture, game);
				//quit = true;
				//return EXIT_TO_MENU;
				break;
			}
			else if (game.e.type == SDL_KEYDOWN)
			{
				switch (game.e.key.keysym.sym)
				{
				case SDLK_LEFT:
					if (level[copy_texture[CAT].Y][copy_texture[CAT].X - 1] != WALL)
					{
						if (copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X - 1] != PRESENT)
						{
							if (level[copy_texture[CAT].Y][copy_texture[CAT].X] == PLACEHERE) {
								showTexture(PLACEHERE, copy_texture[CAT].posTexture, game);
							}
							else {
								showTexture(FLOOR, copy_texture[CAT].posTexture, game);
							}
							
							keydown_for_cat = SDLK_LEFT;
							
							int result = playingLevel(game, file, copy_catAndGift, level, copy_texture, quit);
							if (result == WIN)
								return WIN;
							else if(result == RECURSION)
							{
								showTexture(CAT, copy_texture[CAT].posTexture, game);
								copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = CAT;
							}
							else
							{
								return EXIT_TO_MENU;
							}
						}
						else if (copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X - 1] == PRESENT
							&& level[copy_texture[CAT].Y][copy_texture[CAT].X - 2] != WALL
							&& copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X - 2] != PRESENT)
						{
							if (level[copy_texture[CAT].Y][copy_texture[CAT].X] == PLACEHERE) {
								showTexture(PLACEHERE, copy_texture[CAT].posTexture, game);
							}
							else {
								showTexture(FLOOR, copy_texture[CAT].posTexture, game);
							}
							copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y;
							copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x - copy_texture[CAT].sizeTexture;
							if (level[copy_texture[CAT].Y][copy_texture[CAT].X] == PLACEHERE) {
								showTexture(PLACEHERE, copy_texture[PRESENT].posTexture, game);
							}
							else {
								showTexture(FLOOR, copy_texture[PRESENT].posTexture, game);
							}
							copy_texture[FLOOR].posTexture = copy_texture[PRESENT].posTexture;
							copy_texture[FLOOR].posTexture.x = copy_texture[PRESENT].posTexture.x - copy_texture[PRESENT].sizeTexture;
							keydown_for_cat = SDLK_LEFT;
							keydown_for_box = SDLK_LEFT;
							int result = playingLevel(game, file, copy_catAndGift, level, copy_texture, quit);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								if (level[copy_texture[CAT].Y][copy_texture[CAT].X] == PLACEHERE) {
									showTexture(PLACEHERE, copy_texture[FLOOR].posTexture, game);
								}
								else {
									showTexture(FLOOR, copy_texture[FLOOR].posTexture, game);
								}
								
								showTexture(CAT, copy_texture[CAT].posTexture, game);
								showTexture(PRESENT, copy_texture[PRESENT].posTexture, game);
							}
							else
							{
								return EXIT_TO_MENU;
							}
						}
					}
					break;
				case SDLK_RIGHT:
					if (level[copy_texture[CAT].Y][copy_texture[CAT].X + 1] != WALL)
					{
						if (copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X + 1] != PRESENT)
						{
			
							showTexture(FLOOR, copy_texture[CAT].posTexture, game);
							keydown_for_cat = SDLK_RIGHT;
							int result = playingLevel(game, file, copy_catAndGift, level, copy_texture, quit);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								showTexture(CAT, copy_texture[CAT].posTexture, game);
							}
							else
							{
								return EXIT_TO_MENU;
							}
						}
						else if (copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X + 1] == PRESENT 
							&& level[copy_texture[CAT].Y][copy_texture[CAT].X + 2] != WALL 
							&& copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X + 2] != PRESENT) 
						{
							showTexture(FLOOR, copy_texture[CAT].posTexture, game);
							copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y ;
							copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x + copy_texture[CAT].sizeTexture;
							showTexture(FLOOR, copy_texture[PRESENT].posTexture, game);
							copy_texture[FLOOR].posTexture = copy_texture[PRESENT].posTexture;
							copy_texture[FLOOR].posTexture.x = copy_texture[PRESENT].posTexture.x + copy_texture[PRESENT].sizeTexture;
							keydown_for_cat = SDLK_RIGHT;
							keydown_for_box = SDLK_RIGHT;

							int result = playingLevel(game, file, copy_catAndGift, level, copy_texture, quit);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								showTexture(FLOOR, copy_texture[FLOOR].posTexture, game);
								showTexture(CAT, copy_texture[CAT].posTexture, game);
								showTexture(PRESENT, copy_texture[PRESENT].posTexture, game);
							}
							else
							{
								return EXIT_TO_MENU;
							}
						}
					}
					break;
				case SDLK_UP:
					if (level[copy_texture[CAT].Y - 1][copy_texture[CAT].X] != WALL)
					{
						if (copy_catAndGift[copy_texture[CAT].Y - 1][copy_texture[CAT].X] != PRESENT)
						{
							if (level[copy_texture[CAT].Y][copy_texture[CAT].X] == PLACEHERE) {
								showTexture(PLACEHERE, copy_texture[CAT].posTexture, game);
							}
							else {
								showTexture(FLOOR, copy_texture[CAT].posTexture, game);
							}
							keydown_for_cat = SDLK_UP;

							int result = playingLevel(game, file, copy_catAndGift, level, copy_texture, quit);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								showTexture(CAT, copy_texture[CAT].posTexture, game);
								
							}
							else
							{
								return EXIT_TO_MENU;
							}
						}
						else if (copy_catAndGift[copy_texture[CAT].Y - 1][copy_texture[CAT].X] == PRESENT
							&& level[copy_texture[CAT].Y - 2][copy_texture[CAT].X] != WALL
							&& copy_catAndGift[copy_texture[CAT].Y - 2][copy_texture[CAT].X] != PRESENT)
						{
							showTexture(FLOOR, copy_texture[CAT].posTexture, game);
							copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y - copy_texture[CAT].sizeTexture;
					     	copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x;
							showTexture(FLOOR, copy_texture[PRESENT].posTexture, game);
							copy_texture[FLOOR].posTexture = copy_texture[PRESENT].posTexture;
							copy_texture[FLOOR].posTexture.y = copy_texture[PRESENT].posTexture.y - copy_texture[PRESENT].sizeTexture;
							keydown_for_cat = SDLK_UP;
							keydown_for_box = SDLK_UP;

							int result = playingLevel(game, file, copy_catAndGift, level, copy_texture, quit);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								showTexture(FLOOR, copy_texture[FLOOR].posTexture, game);
								showTexture(CAT, copy_texture[CAT].posTexture, game);
								showTexture(PRESENT, copy_texture[PRESENT].posTexture, game);
							}
							else
							{
								return EXIT_TO_MENU;
							}

						}
					}
					break;
				case SDLK_DOWN:
					if (level[copy_texture[CAT].Y + 1][copy_texture[CAT].X] != WALL)
					{
						if (copy_catAndGift[copy_texture[CAT].Y + 1][copy_texture[CAT].X] != PRESENT)
						{
						
							if (level[copy_texture[CAT].Y][copy_texture[CAT].X] == PLACEHERE) {
								showTexture(PLACEHERE, copy_texture[CAT].posTexture, game);
							}
							else {
								showTexture(FLOOR, copy_texture[CAT].posTexture, game);
							}
							keydown_for_cat = SDLK_DOWN;
							int result = playingLevel(game, file, copy_catAndGift, level, copy_texture, quit);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								showTexture(CAT, copy_texture[CAT].posTexture, game);
								copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = CAT;
							}
							else
							{
								return EXIT_TO_MENU;
							}
						}
						else if (copy_catAndGift[copy_texture[CAT].Y + 1][copy_texture[CAT].X] == PRESENT
							&& level[copy_texture[CAT].Y + 2][copy_texture[CAT].X] != WALL
							&& copy_catAndGift[copy_texture[CAT].Y + 2][copy_texture[CAT].X] != PRESENT)
						{
							if (level[copy_texture[CAT].Y][copy_texture[CAT].X] == PLACEHERE) {
								showTexture(PLACEHERE, copy_texture[CAT].posTexture, game);
							}
							else {
								showTexture(FLOOR, copy_texture[CAT].posTexture, game);
							}
							copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y + copy_texture[CAT].sizeTexture;
							copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x;

							if (level[copy_texture[PRESENT].Y][copy_texture[PRESENT].X] == PLACEHERE)
							{
								showTexture(PLACEHERE, copy_texture[PRESENT].posTexture, game);
							}
							else {
								showTexture(FLOOR, copy_texture[PRESENT].posTexture, game);
							}
							copy_texture[FLOOR].posTexture = copy_texture[PRESENT].posTexture;
							copy_texture[FLOOR].posTexture.y = copy_texture[PRESENT].posTexture.y + copy_texture[PRESENT].sizeTexture;
							copy_texture[FLOOR].Y = copy_texture[PRESENT].Y + 1;
							copy_texture[FLOOR].X = copy_texture[PRESENT].X;
							keydown_for_cat = SDLK_DOWN;
							keydown_for_box = SDLK_DOWN;

							int result = playingLevel(game, file, copy_catAndGift, level, copy_texture, quit);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								
								if (level[copy_texture[FLOOR].Y][copy_texture[FLOOR].X] == PLACEHERE)
								{
									showTexture(PLACEHERE, copy_texture[FLOOR].posTexture, game);
								}
								else 
								{
									showTexture(FLOOR, copy_texture[FLOOR].posTexture, game);
								}
								showTexture(CAT, copy_texture[CAT].posTexture, game);
								showTexture(PRESENT, copy_texture[PRESENT].posTexture, game);
							}
							else
							{
								return EXIT_TO_MENU;
							}
						}
					}
					break;
				case SDLK_z:
					pressed_keys[KEY_PRESS_Z] = 1;
					break;
				case SDLK_LCTRL:
					pressed_keys[KEY_PRESS_LEFT_CTRL] = 1;
					break;
				}
				showArrInConsole(copy_catAndGift, 9, 9);
				if (pressed_keys[KEY_PRESS_LEFT_CTRL] && pressed_keys[KEY_PRESS_Z])
				{
					if (level[copy_texture[CAT].Y][copy_texture[CAT].X] == PLACEHERE)
					{
						showTexture(PLACEHERE, copy_texture[CAT].posTexture, game);
					}
					else {
						showTexture(FLOOR, copy_texture[CAT].posTexture, game);
					}
					
					copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = 0;
					pressed_keys[KEY_PRESS_Z] = 0;
					pressed_keys[KEY_PRESS_LEFT_CTRL] = 0;
					return RECURSION;
				}
				if (quit)return EXIT_TO_MENU;
			}
		}

	}
}
//bool playingLevel(Surface& game, fstream& file, int** catAndGift, int**& level, Texture* texture_of_level, bool quit, int keydown_for_box, int count)
//{
//	static int keydown_for_cat;
//	
//	//static int keydown_for_box ;
//	Texture* copy_texture = new Texture[count];
//	for (int i = 0; i < count; i++)
//	{
//		copy_texture[i] = texture_of_level[i];
//	}
//	
//	switch (keydown_for_cat)
//	{
//	case SDLK_UP:
//		copy_texture[CAT].Y--;
//		copy_texture[CAT].posTexture.y -= copy_texture[CAT].sizeTexture;
//		break;
//	case SDLK_DOWN:
//		copy_texture[CAT].Y++;
//		copy_texture[CAT].posTexture.y += copy_texture[CAT].sizeTexture;
//		break;
//	case SDLK_LEFT:
//		copy_texture[CAT].X--;
//		copy_texture[CAT].posTexture.x -= copy_texture[CAT].sizeTexture;
//		break;
//	case SDLK_RIGHT:
//		copy_texture[CAT].X++;
//		copy_texture[CAT].posTexture.x += texture_of_level[CAT].sizeTexture;
//		break;
//	}
//	switch (keydown_for_box)
//	{
//	case SDLK_UP:
//		copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y - texture_of_level[CAT].sizeTexture;
//		copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x;
//		copy_texture[PRESENT].Y = copy_texture[CAT].Y - 1;
//		copy_texture[PRESENT].X = copy_texture[CAT].X;
//		keydown_for_box = KEY_PRESS_DEFAULT;
//		break;
//	case SDLK_DOWN:
//
//		break;
//	case SDLK_LEFT:
//
//		break;
//	case SDLK_RIGHT:
//
//		break;
//	}
//	//keydown_for_cat = KEY_PRESS_DEFAULT;
//	//keydown_for_box = KEY_PRESS_DEFAULT;
//	//if (keydown == KEY_PRESS_UP)
//	//{
//	//	copy_texture[CAT].Y--;
//	//	copy_texture[CAT].posTexture.y -= copy_texture[CAT].sizeTexture;
//	//}
//	showTexture(FLOOR, copy_texture[CAT].posTexture, game);
//	showTexture(CAT, copy_texture[CAT].posTexture, game);
//	showTexture(PRESENT, copy_texture[PRESENT].posTexture, game);
//
//
//	catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = CAT;
//    //catAndGift[copy_texture[PRESENT].Y][copy_texture[PRESENT].X] = PRESENT;
//	for (int i = 0; i < 9; i++)
//	{
//		for (int j = 0; j < 9; j++)
//		{
//			cout << catAndGift[i][j] << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//	cout << endl;
//
//	if (win())return true;
//	while (!quit)
//	{
//		while (SDL_PollEvent(&game.e) != 0)
//		{
//			if (game.e.type == SDL_QUIT)
//			{
//				quit = true;
//				break;
//			}
//			else if (game.e.type == SDL_KEYDOWN)
//			{
//				switch (game.e.key.keysym.sym)
//				{
//				case SDLK_LEFT:
//					if (level[copy_texture[CAT].Y][copy_texture[CAT].X - 1] != WALL)
//					{
//						if (catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X - 1] != PRESENT)
//						{
//							copy_texture[FLOOR].posTexture = copy_texture[CAT].posTexture;
//							showTexture(FLOOR, copy_texture[FLOOR].posTexture, game);
//							catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = 0;
//							keydown_for_cat = SDLK_LEFT;
//							/*copy_texture[CAT].X--;
//							copy_texture[CAT].posTexture.x -= copy_texture[CAT].sizeTexture;*/
//							if (playingLevel(game, file, catAndGift, level, copy_texture, quit, keydown_for_box))
//								return true;
//							else
//							{
//								//showTexture(FLOOR, copy_texture[FLOOR].posTexture, game);
//								showTexture(CAT, copy_texture[CAT].posTexture, game);
//								catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = CAT;
//							}
//						}
//					}
//					break;
//				case SDLK_RIGHT:
//					if (level[copy_texture[CAT].Y][copy_texture[CAT].X + 1] != WALL)
//					{
//						if (catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X + 1] != PRESENT)
//						{
//							copy_texture[FLOOR].posTexture = copy_texture[CAT].posTexture;
//							showTexture(FLOOR, copy_texture[FLOOR].posTexture, game);
//							catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = 0;
//							keydown_for_cat = SDLK_RIGHT;
//							/*copy_texture[CAT].X++;
//							copy_texture[CAT].posTexture.x += texture_of_level[CAT].sizeTexture;*/
//							//showTexture(FLOOR, posTexture); 
//							if (playingLevel(game, file, catAndGift, level, copy_texture, quit, keydown_for_box))
//								return true;
//							else
//							{
//								showTexture(CAT, copy_texture[CAT].posTexture, game);
//								catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = CAT;
//							}
//							//showTexture(CAT, posTexture, game);
//							//catAndGift[Y_Cat][X_Cat] = 3;
//						}
//					}
//					break;
//				case SDLK_UP:
//					if (level[copy_texture[CAT].Y - 1][copy_texture[CAT].X] != WALL)
//					{
//						if (catAndGift[copy_texture[CAT].Y - 1][copy_texture[CAT].X] != PRESENT)
//						{
//							copy_texture[FLOOR].posTexture = copy_texture[CAT].posTexture;
//							showTexture(FLOOR, copy_texture[FLOOR].posTexture, game);
//							catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = 0;
//							keydown_for_cat = SDLK_UP;
//
//							/*texture_of_level[CAT].Y--;
//							texture_of_level[CAT].posTexture.y -= texture_of_level[CAT].sizeTexture;*/
//							if (playingLevel(game, file, catAndGift, level, copy_texture, quit, keydown_for_box, count))
//								return true;
//							else
//							{
//								/*showTexture(FLOOR, texture_of_level[CAT].posTexture, game);
//								texture_of_level[CAT].Y++;
//								texture_of_level[CAT].posTexture.y += texture_of_level[CAT].sizeTexture;*/
//								//showTexture(FLOOR, texture_of_level[CAT].posTexture, game);
//								//showTexture(FLOOR, copy_texture[FLOOR].posTexture, game);
//								showTexture(CAT, copy_texture[CAT].posTexture, game);
//								showTexture(PRESENT, copy_texture[PRESENT].posTexture, game);
//								catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = CAT;
//								//catAndGift[copy_texture[PRESENT].Y][copy_texture[PRESENT].X] = PRESENT;
//							}
//						}
//						else if (catAndGift[copy_texture[CAT].Y - 1][copy_texture[CAT].X] == PRESENT
//							&& level[copy_texture[CAT].Y - 2][copy_texture[CAT].X] == FLOOR
//							&& catAndGift[copy_texture[CAT].Y - 2][copy_texture[CAT].X] != PRESENT)
//						{
//
//							copy_texture[FLOOR].posTexture = copy_texture[CAT].posTexture;
//							showTexture(FLOOR, copy_texture[FLOOR].posTexture, game);
//							catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = 0;
//							keydown_for_box = SDLK_UP;
//							keydown_for_cat = SDLK_UP;
//							//copy_texture[CAT].Y--;
//							//copy_texture[CAT].posTexture.y -= copy_texture[CAT].sizeTexture;
//							//copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y - texture_of_level[CAT].sizeTexture;
//							//copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x;
//							//copy_texture[PRESENT].Y = copy_texture[CAT].Y - 1;
//							//copy_texture[PRESENT].X = copy_texture[CAT].X;
//
//							if (playingLevel(game, file, catAndGift, level, copy_texture, quit, keydown_for_box))
//								return true;
//							else
//							{
//								showTexture(CAT, copy_texture[CAT].posTexture, game);
//								catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = CAT;
//								copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x;
//								copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y - copy_texture[CAT].sizeTexture;
//								copy_texture[PRESENT].Y = copy_texture[CAT].Y - 2;
//								copy_texture[PRESENT].X = copy_texture[CAT].X;
//								catAndGift[copy_texture[PRESENT].Y][copy_texture[PRESENT].X] = 0;
//								copy_texture[PRESENT].Y--;
//								showTexture(PRESENT, copy_texture[PRESENT].posTexture, game);
//								catAndGift[copy_texture[PRESENT].Y][copy_texture[PRESENT].X] = PRESENT;
//								copy_texture[PRESENT].posTexture.y -= texture_of_level[PRESENT].sizeTexture;
//								copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x;
//								showTexture(FLOOR, copy_texture[PRESENT].posTexture, game);
//								copy_texture[PRESENT].posTexture.y += texture_of_level[PRESENT].sizeTexture;
//							}
//						}
//					}
//					break;
//				case SDLK_DOWN:
//					if (level[copy_texture[CAT].Y + 1][copy_texture[CAT].X] != WALL)
//					{
//						if (catAndGift[copy_texture[CAT].Y + 1][copy_texture[CAT].X] != PRESENT)
//						{
//							copy_texture[FLOOR].posTexture.x = copy_texture[CAT].posTexture.x;
//							showTexture(FLOOR, copy_texture[CAT].posTexture, game);
//							catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = 0; \
//								keydown_for_cat = SDLK_DOWN;
//							/*copy_texture[CAT].Y++;
//							copy_texture[CAT].posTexture.y += copy_texture[CAT].sizeTexture;*/
//							//showTexture(FLOOR, posTexture); 
//							if (playingLevel(game, file, catAndGift, level, copy_texture, quit, keydown_for_box))
//								return true;
//							else
//							{
//								showTexture(CAT, copy_texture[CAT].posTexture, game);
//								catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = CAT;
//							}
//							//showTexture(CAT, posTexture, game);
//							//catAndGift[Y_Cat][X_Cat] = 3;
//						}
//					}
//					break;
//				case SDLK_z:
//					pressed_keys[KEY_PRESS_Z] = 1;
//					break;
//				case SDLK_LCTRL:
//					pressed_keys[KEY_PRESS_LEFT_CTRL] = 1;
//					break;
//				}
//				for (int i = 0; i < 9; i++)
//				{
//					for (int j = 0; j < 9; j++)
//					{
//						cout << catAndGift[i][j] << " ";
//					}
//					cout << endl;
//				}
//				cout << endl;
//				cout << endl;
//				if (pressed_keys[KEY_PRESS_LEFT_CTRL] && pressed_keys[KEY_PRESS_Z])
//				{
//					/*if(keydown_for_box != KEY_PRESS_DEFAULT)
//						showTexture(FLOOR, copy_texture[PRESENT].posTexture, game);*/
//					showTexture(FLOOR, copy_texture[CAT].posTexture, game);
//					catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = 0;
//					pressed_keys[KEY_PRESS_Z] = 0;
//					pressed_keys[KEY_PRESS_LEFT_CTRL] = 0;
//					return false;
//				}
//			}
//		}
//	}
//}
void characterMovement(vector<vector<int>>& level, fstream& file, Surface& game, bool& quit)
{//передвижение персонажей


	vector<Texture> texture_of_level;


	for (int i = 0; i < CountOfTexture; i++)
	{
		Texture texture;
		texture_of_level.push_back(texture);
	}
	
	texture_of_level[CAT].posTexture.y = 0;
	texture_of_level[CAT].posTexture.x = 0;
	texture_of_level[FLOOR].posTexture;

	fstream fileCat("position.TXT");
	showTexture(BACKGROUND, texture_of_level[CAT].posTexture, game);
	field(level, file, texture_of_level[CAT].posTexture, game);

	vector<vector<int>> catAndGift;
	createMap(game, catAndGift, fileCat);
	field(catAndGift, fileCat, texture_of_level[CAT].posTexture, game);
	
	
	for (int y = 0; y < (game.height); y++)
	{
		for (int x = 0; x < (game.width); x++)
		{
			if (catAndGift[y][x] == CAT)
			{
				texture_of_level[CAT].X = x;
				texture_of_level[CAT].Y = y;
			}
			if (level[y][x] == PLACEHERE) {
				game.count_place++;
			}
		}
	}

	texture_of_level[CAT].posTexture.x = ((SCREEN_WIDTH / 2) - ((game.width) / 2.0 * texture_of_level[CAT].sizeTexture)) + texture_of_level[CAT].X * texture_of_level[CAT].sizeTexture;
	texture_of_level[CAT].posTexture.y = ((SCREEN_HEIGHT / 2) - ((game.height) / 2.0 * texture_of_level[CAT].sizeTexture)) + texture_of_level[CAT].Y * texture_of_level[CAT].sizeTexture;
	
	playingLevel(game, file, catAndGift, level, texture_of_level, quit);
	

	/*while (!quit) {
		while (SDL_PollEvent(&e) != 0) {

			if (e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			else if (e.type == SDL_KEYDOWN)
			{


				// хождение персонажей
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
					//if (count < 1)
					//{

					if (level[Y_Cat][X_Cat - 1] != WALL)
					{
						if (catAndGift[Y_Cat][X_Cat - 1] != PRESENT)
						{
							if (level[Y_Cat][X_Cat] == PLACEHERE) {
								showTexture(PLACEHERE, posTexture, game);
							}
							else {
								showTexture(FLOOR, posTexture, game);
							}
							catAndGift[Y_Cat][X_Cat] = 0;
							X_Cat--;
							posTexture.x -= sizeTexture;
							//showTexture(FLOOR, posTexture);
							showTexture(CAT, posTexture, game);
							catAndGift[Y_Cat][X_Cat] = 3;
						}

						else if (catAndGift[Y_Cat][X_Cat - 1] == PRESENT && level[Y_Cat][X_Cat - 2] != WALL && catAndGift[Y_Cat][X_Cat - 2] != PRESENT) {
							if (level[Y_Cat][X_Cat] == PLACEHERE) {
								showTexture(PLACEHERE, posTexture, game);
							}
							else {
								showTexture(FLOOR, posTexture, game);
							}
							catAndGift[Y_Cat][X_Cat] = 0;
							X_Cat--;
							posTexture.x -= sizeTexture;
							if (level[Y_Cat][X_Cat] == PLACEHERE) {
								showTexture(PLACEHERE, posTexture, game);
							}
							else {
								showTexture(FLOOR, posTexture, game);
							}
							showTexture(CAT, posTexture, game);
							posTexture.x -= sizeTexture;
							showTexture(PRESENT, posTexture, game);
							posTexture.x += sizeTexture;
							catAndGift[Y_Cat][X_Cat] = 3;
							catAndGift[Y_Cat][X_Cat - 1] = 4;
						}
					}
					//}
					//count++;
					//if (count == 2) count = 0;
					break;
				case SDLK_RIGHT:
					//if (count < 1) {
					if (level[Y_Cat][X_Cat + 1] != WALL)
					{
						if (catAndGift[Y_Cat][X_Cat + 1] != PRESENT)
						{
							if (level[Y_Cat][X_Cat] == PLACEHERE) {
								showTexture(PLACEHERE, posTexture, game);
							}
							else {
								showTexture(FLOOR, posTexture, game);
							}
							catAndGift[Y_Cat][X_Cat] = 0;
							X_Cat++;
							posTexture.x += sizeTexture;
							//showTexture(FLOOR, posTexture);
							showTexture(CAT, posTexture, game);
							catAndGift[Y_Cat][X_Cat] = 3;
						}

						else if (catAndGift[Y_Cat][X_Cat + 1] == PRESENT && level[Y_Cat][X_Cat + 2] != WALL && catAndGift[Y_Cat][X_Cat + 2] != PRESENT) {
							if (level[Y_Cat][X_Cat] == PLACEHERE) {
								showTexture(PLACEHERE, posTexture, game);
							}
							else {
								showTexture(FLOOR, posTexture, game);
							}
							catAndGift[Y_Cat][X_Cat] = 0;
							X_Cat++;
							posTexture.x += sizeTexture;
							if (level[Y_Cat][X_Cat] == PLACEHERE) {
								showTexture(PLACEHERE, posTexture, game);
							}
							else {
								showTexture(FLOOR, posTexture, game);
							}
							showTexture(CAT, posTexture, game);
							posTexture.x += sizeTexture;
							showTexture(PRESENT, posTexture, game);
							posTexture.x -= sizeTexture;
							catAndGift[Y_Cat][X_Cat] = 3;
							catAndGift[Y_Cat][X_Cat + 1] = 4;
						}
					}

					break;
				case SDLK_UP:
					//if (count < 1) {

					if (level[Y_Cat - 1][X_Cat] != WALL )
					{
						if (catAndGift[Y_Cat - 1][X_Cat] != PRESENT)
						{
							if (level[Y_Cat][X_Cat] == PLACEHERE) {
								showTexture(PLACEHERE, posTexture, game);
							}
							else {
								showTexture(FLOOR, posTexture, game);
							}
							catAndGift[Y_Cat][X_Cat] = 0;
							Y_Cat--;
							posTexture.y -= sizeTexture;
							//showTexture(FLOOR, posTexture);
							showTexture(CAT, posTexture, game);
							catAndGift[Y_Cat][X_Cat] = 3;
						}

						else if (catAndGift[Y_Cat - 1][X_Cat] == PRESENT && level[Y_Cat - 2][X_Cat] != WALL && catAndGift[Y_Cat - 2][X_Cat] != PRESENT) {
							if (level[Y_Cat][X_Cat] == PLACEHERE) {
								showTexture(PLACEHERE, posTexture, game);
							}
							else {
								showTexture(FLOOR, posTexture, game);
							}
							catAndGift[Y_Cat][X_Cat] = 0;
							Y_Cat--;
							posTexture.y -= sizeTexture;
							if (level[Y_Cat][X_Cat] == PLACEHERE) {
								showTexture(PLACEHERE, posTexture, game);
							}
							else {
								showTexture(FLOOR, posTexture, game);
							}
							showTexture(CAT, posTexture, game);
							posTexture.y -= sizeTexture;
							showTexture(PRESENT, posTexture, game);
							posTexture.y += sizeTexture;
							catAndGift[Y_Cat][X_Cat] = 3;
							catAndGift[Y_Cat - 1][X_Cat] = 4;
						}
					}


					break;
				case SDLK_DOWN:

					if (level[Y_Cat + 1][X_Cat] != WALL)
					{
						
						if (catAndGift[Y_Cat + 1][X_Cat] != PRESENT)
						{
							if (level[Y_Cat][X_Cat] == PLACEHERE) {
								showTexture(PLACEHERE, posTexture, game);
							}
							else {
								showTexture(FLOOR, posTexture, game);
							}
							catAndGift[Y_Cat][X_Cat] = 0;
							Y_Cat++;
							posTexture.y += sizeTexture;

							showTexture(CAT, posTexture, game);
							catAndGift[Y_Cat][X_Cat] = 3;
						}

						else if (catAndGift[Y_Cat + 1][X_Cat] == PRESENT && level[Y_Cat + 2][X_Cat] != WALL && catAndGift[Y_Cat + 2][X_Cat] != PRESENT) {
							if (level[Y_Cat][X_Cat] == PLACEHERE) {
								showTexture(PLACEHERE, posTexture, game);
							}
							else {
								showTexture(FLOOR, posTexture, game);
							}
							
							catAndGift[Y_Cat][X_Cat] = 0;
							Y_Cat++;
							posTexture.y += sizeTexture;
							if (level[Y_Cat][X_Cat] == PLACEHERE) {
								showTexture(PLACEHERE, posTexture, game);
							}
							else {
								showTexture(FLOOR, posTexture, game);
							}
							showTexture(CAT, posTexture, game);
							posTexture.y += sizeTexture;
							showTexture(PRESENT, posTexture, game);
							posTexture.y -= sizeTexture;
							catAndGift[Y_Cat][X_Cat] = 3;
							catAndGift[Y_Cat + 1][X_Cat] = 4;
						}
					}

					break;

				case SDLK_ESCAPE:
					return;
					break;
				}

			}


		}
	}*/
}
void createMap(Surface& game, vector<vector<int>>& array, fstream& file) {// чтение файла и создание массива

	if (!file.is_open())
	{
		std::cerr << "Error opening file!" << std::endl;
		//More error handling code goes here
	}
	else {
		string str;
		file >> str;
		(game.height) = stoi(str);
		file >> str;
		(game.width) = stoi(str);
		for (int i = 0; i < (game.height); i++)
		{
			vector<int> arr;
			for (int j = 0; j < (game.width); j++)
			{
				file >> str;
				arr.push_back(stoi(str));
			}
			array.push_back(arr);
		}
	
	}
}
void field(vector<vector<int>> level, fstream& file, SDL_Rect posTexture, Surface& game)
{//тут будет отображаться массив в-виде картинки
	int sizeTexture = 50;

	//SDL_Rect posTexture;
	double X = (SCREEN_WIDTH / 2) - (game.width / 2.0 * sizeTexture);
	posTexture.x = X;
	posTexture.y = (SCREEN_HEIGHT / 2) - (game.height / 2.0 * sizeTexture);
	for (int i = 0; i < game.height; i++) {
		for (int j = 0; j < game.width; j++) {
			switch (level[i][j])
			{

			case WALL:
				showTexture(WALL, posTexture, game);
				break;
			case FLOOR:
				showTexture(FLOOR, posTexture, game);
				break;
			case CAT:
				showTexture(CAT, posTexture, game);
				break;
			case PRESENT:
				showTexture(PRESENT, posTexture, game);
				break;
			case PLACEHERE:
				showTexture(PLACEHERE, posTexture, game);
				break;
			}
			posTexture.x += sizeTexture;
		}
		posTexture.x = X;
		posTexture.y += sizeTexture;
	}

}

bool win(Surface& game, vector<vector<int>> level, vector<vector<int>> copy_catAndGift) {
	int count = 0;
	for (int i = 0; i < game.height; i++)
	{
		for (int j = 0; j < game.width; j++)
		{
			if (level[i][j] == PLACEHERE && copy_catAndGift[i][j] == PRESENT)
				count++;
		}
	}
	if (count == game.count_place) return 1;
	return 0;

}
void showTexture(int i, SDL_Rect posTexture, Surface& game)
{
	game.CurrentSurface = game.Texture[i];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &posTexture);
	SDL_UpdateWindowSurface(game.Window);
}


void exit(bool& quit, Surface& game)
{
	//bool quit = false;
	bool quit2 = false;
	SDL_Event e;
	SDL_Rect stretchRect;
	stretchRect.x = 160;
	stretchRect.y = 370;
	int i = 3;
	int a = 0;
	int current_pressed_button = i;
	//backgroundMenu();
	game.CurrentSurface = game.Logos[MENU_EXIT];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
	SDL_UpdateWindowSurface(game.Window);

	game.CurrentSurface = game.PressedButtons[current_pressed_button];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
	SDL_UpdateWindowSurface(game.Window);
	stretchRect.x += 300;
	i++;
	game.CurrentSurface = game.Buttons[i];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
	SDL_UpdateWindowSurface(game.Window);
	//a++;
	//e.key.keysym.sym = SDL_DEFA
	while (quit2 == false)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				quit2 = true;
				break;
			}
			//else if (a == 0)
			//{
			//	game.CurrentSurface = game.PressedButtons[current_pressed_button];
			//	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
			//	SDL_UpdateWindowSurface(game.Window);
			//	stretchRect.x += 300;
			//	i++;
			//	game.CurrentSurface = game.Buttons[i];
			//	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
			//	SDL_UpdateWindowSurface(game.Window);
			//	a++;
			//}
			else if (e.type == SDL_KEYDOWN)
			{
				
				switch (e.key.keysym.sym)
				{
				case SDLK_RIGHT:
					if (current_pressed_button == YES)
					{
						game.CurrentSurface = game.PressedButtons[NO];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
						SDL_UpdateWindowSurface(game.Window);
						stretchRect.x -= 300;
						game.CurrentSurface = game.Buttons[YES];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
						SDL_UpdateWindowSurface(game.Window);
						current_pressed_button++;
					}
					break;
				case SDLK_LEFT:
					if (current_pressed_button == NO)
					{
						//stretchRect.x -= 400;
						game.CurrentSurface = game.PressedButtons[YES];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
						SDL_UpdateWindowSurface(game.Window);

						stretchRect.x += 300;
						game.CurrentSurface = game.Buttons[NO];
						SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
						SDL_UpdateWindowSurface(game.Window);
						current_pressed_button--;
					}
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
					Mix_PlayChannel(-1, game.button, 0) == -1;
					switch (current_pressed_button)
					{
					case YES:
						quit = true;
						quit2 = true;
						break;
					case NO:
						quit2 = true;
						break;
					}
					break;
					//case SDLK_z:
					//	pressed_keys[KEY_PRESS_Z] = 1;
					//	//if ( e.key.keysym.mod == KMOD_LCTRL)
					//	//{
					//	//SDLK_LCTRL == PRESSED;
					//	//}
					//	break;
					//case SDLK_LCTRL:
					//	pressed_keys[KEY_PRESS_LEFT_CTRL] = 1;
					//	//if ( e.key.keysym.mod == KMOD_LCTRL)
					//	//{
					//	//SDLK_LCTRL == PRESSED;
					//	//}
					//	break;
				}
			}
			/*if (pressed_keys[KEY_PRESS_LEFT_CTRL] && pressed_keys[KEY_PRESS_Z])
			{
				quit = true;
				quit2 = true;
			}*/
			if (quit2 == true)break;
		}
	}
}
void showButton(Surface& game, int i, SDL_Rect stretchRect, int y_of_button1, int y_of_button2, int y_of_button3)
{
	if (i == 0)stretchRect.y = y_of_button1;
	if (i == 1)stretchRect.y = y_of_button2;
	if (i == 2)stretchRect.y = y_of_button3;
	game.CurrentSurface = game.Buttons[i];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
	SDL_UpdateWindowSurface(game.Window);
}
bool init(Surface& game)
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		game.Window = SDL_CreateWindow(" Sokoban",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (game.Window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			game.ScreenSurface = SDL_GetWindowSurface(game.Window);
		}
	}
	return success;
}
bool loadMedia(Surface& game)
{
	
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	game.music = Mix_LoadMUS("sound\\music.wav");
	if (game.music == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(game.music, -1);
	}
	game.button = Mix_LoadWAV("sound\\button.wav");
	game.box = Mix_LoadWAV("sound\\box.wav");
	//Если что-то пошло не так
	if ((game.button == NULL) || (game.box == NULL))
	{
		return false;
	}


	game.Logos[0] = loadSurface("teamLogo.bmp");
	if (game.Logos[0] == NULL)
	{
		printf("Failed to load default image!\n");
		success = false;
	}
	game.Logos[1] = loadSurface("gameLogo.bmp");
	if (game.Logos[1] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Logos[2] = loadSurface("MainMenu.bmp");
	if (game.Logos[2] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Logos[MENU_EXIT] = loadSurface("MenuExit.bmp");
	if (game.Logos[MENU_EXIT] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Buttons[0] = loadSurface("PlayGame1.bmp");
	if (game.Buttons[0] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Buttons[1] = loadSurface("HowToPlay1.bmp");
	if (game.Buttons[1] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Buttons[2] = loadSurface("Exit1.bmp");
	if (game.Buttons[2] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Buttons[YES] = loadSurface("Yes1.bmp");
	if (game.Buttons[YES] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Buttons[NO] = loadSurface("No1.bmp");
	if (game.Buttons[NO] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Buttons[NEXT] = loadSurface("Next1.bmp");
	if (game.Buttons[NEXT] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Buttons[BACK] = loadSurface("Back1.bmp");
	if (game.Buttons[BACK] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.PressedButtons[0] = loadSurface("PlayGame2.bmp");
	if (game.PressedButtons[0] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.PressedButtons[1] = loadSurface("HowToPlay2.bmp");
	if (game.PressedButtons[1] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.PressedButtons[2] = loadSurface("Exit2.bmp");
	if (game.PressedButtons[2] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.PressedButtons[YES] = loadSurface("Yes2.bmp");
	if (game.PressedButtons[YES] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.PressedButtons[NO] = loadSurface("No2.bmp");
	if (game.PressedButtons[NO] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.PressedButtons[NEXT] = loadSurface("Next2.bmp");
	if (game.PressedButtons[NEXT] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.PressedButtons[BACK] = loadSurface("Back2.bmp");
	if (game.PressedButtons[BACK] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Texture[EMPTY] = loadSurface("empty.bmp");
	if (game.Texture[EMPTY] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Texture[WALL] = loadSurface("wall.bmp");
	if (game.Texture[WALL] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Texture[FLOOR] = loadSurface("floor.bmp");
	if (game.Texture[FLOOR] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Texture[CAT] = loadSurface("mainCat.bmp");
	if (game.Texture[CAT] == NULL)
	{
		printf("Failed to load up images!\n");
		success = false;
	}
	game.Texture[PRESENT] = loadSurface("PresentBox.bmp");
	if (game.Texture[PRESENT] == NULL)
	{
		printf("Failed to load up images!\n");
		success = false;
	}
	game.Texture[PLACEHERE] = loadSurface("PlaceHere.bmp");
	if (game.Texture[PLACEHERE] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Texture[BACKGROUND] = loadSurface("Background.bmp");
	if (game.Texture[BACKGROUND] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.Texture[PLACEHERE] = loadSurface("PlaceHere.bmp");
	if (game.Texture[PLACEHERE] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.WindowsHowToPlay[FIRST] = loadSurface("1Window.bmp");
	if (game.WindowsHowToPlay[FIRST] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.WindowsHowToPlay[SECOND] = loadSurface("2Window.bmp");
	if (game.WindowsHowToPlay[SECOND] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.WindowsHowToPlay[THIRD] = loadSurface("3Window.bmp");
	if (game.WindowsHowToPlay[THIRD] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.WindowsHowToPlay[FOURTH] = loadSurface("4Window.bmp");
	if (game.WindowsHowToPlay[FOURTH] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	return success;
}
void close(Surface& game)
{
	//После уничтожения окна не забудь указатели указать на NULL
	//Освободить поверхность
	Mix_FreeMusic(game.music);
	game.music = NULL;
	for (int i = 0; i < CountOfLogos; ++i)
	{
		SDL_FreeSurface(game.Logos[i]);
		game.Logos[i] = NULL;
	}
	//Уничтожить окно
	SDL_DestroyWindow(game.Window);
	game.Window = NULL;
	//Выйим из подсистемы SDL
	//SDL_Quit();
	for (int i = 0; i < CountOfLogos; ++i)
	{
		SDL_FreeSurface(game.Logos[i]);
		game.Logos[i] = NULL;
	}
	SDL_DestroyWindow(game.Window);
	game.Window = NULL;
	SDL_Quit();
	Mix_Quit();
}
SDL_Surface* loadSurface(std::string path)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}

bool isPressed(int keyCode)
{
	return 1;
}
bool isReleased(int keyCode)
{
	return 0;
}


