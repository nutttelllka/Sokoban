#pragma once
#include "Structures.h"
#include "Enums.h"
#include <vector>
#include <thread>//для работі с потоками
#include <chrono>//для потока со временем
#include <mutex>

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
//#define KMOD_CTRL_z (SDLK_LCTRL|SDLK_z)
void intro(Surface& game);
bool init(Surface& game);
bool loadMedia(Surface& game);
void close(Surface& game);
void menu(Surface& game, bool& quit, int i, int& i_for_buttons, int& current_pressed_button);
void playGame(Surface& game, bool& quit, fstream& file, fstream& fileCat);
void showButton(Surface& game, int i, SDL_Rect stretchRectб, int y_of_button1 = 250, int y_of_button2 = 250 + 70, int y_of_button3 = 250 + 140);
void backgroundMenu(Surface& game);
void exit(bool& quit, Surface& game);
void createMap(Surface& game, vector<vector<int>>& array, fstream& file, bool new_level);
void field(Surface& game, vector<vector<int>> array, fstream& file, SDL_Rect posTexture);//
//void characterMovement(Surface& game, fstream& file, fstream& fileCat, bool& quit);
bool characterMovement(Surface& game, fstream& file, fstream& fileCat, bool& quit, bool new_level);
void showTexture(int i, SDL_Rect posTexture, Surface& game);
bool isPressed(int keyCode);
bool isReleased(int keyCode);
void howToPlay(Surface& game, bool quit, int count = 0);
bool win(Surface& game, vector<vector<int>> copy_catAndGift);
int playingLevel(Surface& game, fstream& file, vector<vector<int>> catAndGift, vector < Texture> texture_of_elements, bool& quit, int &count_of_sec, bool first = false);
void countOfStep(Surface& game, bool what, bool zero = false);
void retry(Surface& game, bool& quit);

bool pressed_keys[7] = {};

bool stop_timer = false;


//тут был Степа
SDL_Surface* loadSurface(string path);


//void Stealth()
//{
//	HWND Stealth;
//	AllocConsole();
//	Stealth = FindWindowA("ConsoleWindowClass", NULL);
//	ShowWindow(Stealth, 0);
//}
void showPic(Surface& game, SDL_Rect coord, int what_kind_of_arr, int what_kind_of_pic)
{
	switch (what_kind_of_arr)
	{
	case WALLPS:
		game.CurrentSurface = game.Wallps[what_kind_of_pic];
		break;
	case BUTTONS:
		game.CurrentSurface = game.Buttons[what_kind_of_pic];
		break;
	case PRESSED_BUTTONS:
		game.CurrentSurface = game.PressedButtons[what_kind_of_pic];
		break;
	case TEXTURES:
		game.CurrentSurface = game.Texture[what_kind_of_pic];
		break;
	case WINDOWS:
		game.CurrentSurface = game.WindowsHowToPlay[what_kind_of_pic];
		break;
	case NUMBERS:
		game.CurrentSurface = game.Numbers[what_kind_of_pic];
		break;
	case LEVELES:
		game.CurrentSurface = game.WindowLevel[what_kind_of_pic];
		break;
	case COMIC:
		game.CurrentSurface = game.Comic[what_kind_of_pic];
		break;
	}
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &coord);
	SDL_UpdateWindowSurface(game.Window);
}
void inisialitCoordOfWallp(SDL_Rect& coord)
{
	coord.x = 0;
	coord.y = 0;
}
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
			Mix_PlayChannel(4, game.intro, 0);
			bool quit = false;
			int i = 0;
			int i_for_buttons = 0;
			int current_pressed_button = 0;


			while (!quit)
			{
				while (SDL_PollEvent(&game.e) != 0)
				{
					if (game.e.type == SDL_QUIT)
					{
						quit = true;
						break;
					}
					else if (i < 2)
					{
						SDL_Rect coord_for_wallp;
						inisialitCoordOfWallp(coord_for_wallp);
						showPic(game, coord_for_wallp, WALLPS, i);
						SDL_Delay(500);
						//if(i == 0)Mix_PlayChannel(-1, game.intro, 0) == -1;
						SDL_Delay(500);
						i++;
					}
					if (i == 2)
					{
						/*Mix_FreeMusic(game.music);
						game.music = NULL;*/
						menu(game, quit, i, i_for_buttons, current_pressed_button);
					}
				}
			}
		}
	}
}
void backgroundMenu(Surface& game)
{
	game.CurrentSurface = game.Wallps[2];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
	SDL_UpdateWindowSurface(game.Window);
}
void menu(Surface& game, bool& quit, int i, int& i_for_buttons, int& current_pressed_button)
{
	if (Mix_FadeInMusic(game.music2, -1, 3000) == -1) 
	{
		printf("Mix_FadeInMusic: %s\n", Mix_GetError());

	}
	fstream file("fields.TXT");
	fstream fileCat("position.TXT");
	SDL_Rect stretchRect;
	stretchRect.x = 270;
	stretchRect.y = 250;
	int current_y = 250;
	int y_of_button1 = 250;
	int y_of_button2 = y_of_button1 + 70;
	int y_of_button3 = y_of_button2 + 70;
	int interval_Y = 70;

	backgroundMenu(game);
	showPic(game, stretchRect, PRESSED_BUTTONS, i_for_buttons);
	stretchRect.y += interval_Y;
	i_for_buttons++;

	for (; i_for_buttons < 3; i_for_buttons)
	{
		showPic(game, stretchRect, BUTTONS, i_for_buttons);
		stretchRect.y += interval_Y;
		i_for_buttons++;
	}
	while (!quit)
	{
		while (SDL_PollEvent(&game.e) != 0)
		{
			stop_timer = true;
			if (game.e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			else if (game.e.type == SDL_KEYDOWN)
			{
				switch (game.e.key.keysym.sym)
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
						showPic(game, stretchRect, PRESSED_BUTTONS, current_pressed_button);

					}
					break;
				case SDLK_ESCAPE:
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
					showPic(game, stretchRect, PRESSED_BUTTONS, current_pressed_button);
					SDL_UpdateWindowSurface(game.Window);
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
					switch (current_pressed_button)
					{
					case GAME:
						Mix_PlayChannel(3, game.button, 0) == 3;
						playGame(game, quit, file, fileCat);
						backgroundMenu(game);
						showButton(game, HOW_TO_PLAY, stretchRect);
						showButton(game, EXIT, stretchRect);
						stretchRect.y = y_of_button1;
						break;
					case HOW_TO_PLAY:
						Mix_PlayChannel(3, game.button, 0) == 3;
						howToPlay(game, quit);
						backgroundMenu(game);
						showButton(game, GAME, stretchRect);
						showButton(game, EXIT, stretchRect);
						stretchRect.y = y_of_button2;
						break;
					case EXIT:
						Mix_PlayChannel(3, game.button, 0) == 3;
						exit(quit, game);
						backgroundMenu(game);
						showButton(game, GAME, stretchRect);
						showButton(game, HOW_TO_PLAY, stretchRect);
						stretchRect.y = y_of_button3;
						break;
					}
					showPic(game, stretchRect, PRESSED_BUTTONS, current_pressed_button);
					break;
				default:
					break;
				}
			}
		}
	}
}
bool showWindowHowToPlay(Surface& game, int number_of_current_window)
{
	SDL_Rect coords;
	inisialitCoordOfWallp(coords);
	if (number_of_current_window < 0 || number_of_current_window >= CountOfWindows)return false;
	for (int number_of_window = 0; number_of_window < CountOdArrs::CountOfWindows; number_of_window++)
	{
		if (number_of_current_window == number_of_window)
		{
			showPic(game, coords, WINDOWS, number_of_window);
			return true;
		}
	}
}
void howToPlay(Surface& game, bool quit, int count)
{
	SDL_Rect stretchRect;
	SDL_Rect coord_for_wallp;
	coord_for_wallp.x = 0;
	coord_for_wallp.y = 0;
	stretchRect.x = 170;
	stretchRect.y = 450;

	showPic(game, coord_for_wallp, WINDOWS, FIRST);
	showPic(game, stretchRect, BUTTONS, BACK);
	stretchRect.x += 420;
	showPic(game, stretchRect, BUTTONS, NEXT);
	while (quit == false)
	{
		while (SDL_PollEvent(&game.e) != 0)
		{
			if (game.e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			else if (game.e.type == SDL_KEYDOWN)
			{
				Mix_PlayChannel(-1, game.button, 0) == -1;
				switch (game.e.key.keysym.sym)
				{
				case SDLK_RIGHT:
					count++;
					showPic(game, stretchRect, PRESSED_BUTTONS, NEXT);
					SDL_Delay(200);
					if (!showWindowHowToPlay(game, count))
						return;
					break;
				case SDLK_LEFT:
					count--;
					stretchRect.x = 170;
					showPic(game, stretchRect, PRESSED_BUTTONS, BACK);
					SDL_Delay(200);
					if (!showWindowHowToPlay(game, count))
						return;
					break;
				}
				stretchRect.x = 170;
				showPic(game, stretchRect, BUTTONS, BACK);
				stretchRect.x += 420;
				showPic(game, stretchRect, BUTTONS, NEXT);
			}
			if (quit == true)break;
		}
	}
}
void showWindowLevel(Surface& game, int number_of_current_level)
{
	SDL_Rect coords;
	inisialitCoordOfWallp(coords);
	for (int number_of_level = 0; number_of_level < CountOdArrs::CountOfLeveles; number_of_level++)
	{
		if (number_of_current_level == number_of_level)
		{
			showPic(game, coords, LEVELES, number_of_level);
		}
	}
}
void showComic(Surface& game)
{
	SDL_Rect coord_for_wallp;
	inisialitCoordOfWallp(coord_for_wallp);
	showPic(game, coord_for_wallp, COMIC, FIRST);
	SDL_Delay(1000);
	coord_for_wallp.x = 100;
	coord_for_wallp.y = 0;
	while (!Mix_FadeOutMusic(2000) && Mix_PlayingMusic())
	{
		// wait for any fades to complete
		SDL_Delay(40);
	}


	if (Mix_FadeInMusic(game.music2, -1, 2000) == -1) 
	{
		printf("Mix_FadeInMusic: %s\n", Mix_GetError());

	}
	for (int number_of_comic = SECOND; number_of_comic < CountOdArrs::CountOfComic;)
	{
		for (int i = 0; i < 2; i++)
		{
			showPic(game, coord_for_wallp, COMIC, number_of_comic);
			SDL_Delay(1000);
			coord_for_wallp.x += 300;
			number_of_comic++;
		}
		coord_for_wallp.x = 100;
		coord_for_wallp.y += 300;
	}

}
void timer(Surface& game, int &count_of_sec) {
	int size = 20;
	//int count_of_sec = 90;
	int sec = count_of_sec;
	int min = 0;
	while (sec > 60)
	{
		min++;
		sec -= 60;
	}

	SDL_Rect texture_of_number;
	texture_of_number.y = 35;
	int x = 0, y = 0, z = 0, w = 0;//изменение определенных цифр во времени

	x = sec % 10;
	texture_of_number.x = SCREEN_WIDTH - size * 2;
	showPic(game, texture_of_number, NUMBERS, x);

	y = (sec / 10);
	texture_of_number.x -= size;
	showPic(game, texture_of_number, NUMBERS, y);

	texture_of_number.x -= size;
	showPic(game, texture_of_number, NUMBERS, 10);

	z = min % 10;
	texture_of_number.x -= size;
	showPic(game, texture_of_number, NUMBERS, z);

	w = (min / 10);
	texture_of_number.x -= size;
	showPic(game, texture_of_number, NUMBERS, w);

	
	while (!stop_timer)
	{
		if (sec == 0) {
			if (min - 1 >= 0) {
				min--;
				sec = 60;
				z = min % 10;
				texture_of_number.x = SCREEN_WIDTH - size * 5;
				showPic(game, texture_of_number, NUMBERS, z);
				if ((min / 10) - 1 >= 0) {
					w = (min / 10);
					texture_of_number.x = SCREEN_WIDTH - size * 6;
					showPic(game, texture_of_number, NUMBERS, w);
				}	
			}
		}
		sec--;
		if (x == 0) {
			y = (sec / 10) % 10;
			texture_of_number.x = SCREEN_WIDTH - size * 3;
			showPic(game, texture_of_number, NUMBERS, y);
		}
		x = sec % 10;
		texture_of_number.x = SCREEN_WIDTH - size * 2;
		showPic(game, texture_of_number, NUMBERS, x);

		count_of_sec--;
		if (min == 0 && sec == 0) {
			stop_timer = true;
			return;
		}

		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}
void playGame(Surface& game, bool& quit, fstream& file, fstream& fileCat)
{
	//int** level;
	vector<vector<int>> level;
	game.infOfFild.count_place = 0;
	int height = 0;
	int width = 0;
	static bool new_level = false;
	static int number_of_level = FIRST;
	if (number_of_level == FIRST)
	{
		showComic(game);
	}
	while (number_of_level < game.count_levels)
	{
		//stop_timer = true;
		
		showWindowLevel(game, number_of_level);
		SDL_Delay(1000);
		game.count_step = 0;
		createMap(game, game.infOfFild.level, file, new_level);
		if (characterMovement(game, file, fileCat, quit, new_level) == EXIT_TO_MENU)
		{
			//quit = true;
			new_level = false;
			game.infOfFild.level.clear();
			game.infOfFild.catAndGift.clear();
			vector<vector<int>>().swap(game.infOfFild.level);
			vector<vector<int>>().swap(game.infOfFild.catAndGift);
			break;
		}
		else
		{
			
			stop_timer = true;
			//createMap(game, game.infOfFild.level, file);
			game.infOfFild.level.clear();
			game.infOfFild.catAndGift.clear();
			//game.infOfFild.level.swap(vector<vector<int>>());
			vector<vector<int>>().swap(game.infOfFild.level);
			vector<vector<int>>().swap(game.infOfFild.catAndGift);
			game.infOfFild.count_place = 0;
			SDL_Delay(1000);
			SDL_Rect coord;
			inisialitCoordOfWallp(coord);
			if (game.result == WIN_WALP) {
				number_of_level++;
				new_level = true;
				showPic(game, coord, WALLPS, WIN_WALP);
				SDL_Delay(1000);
			}
			else if (game.result == LOSE) {
				showPic(game, coord, WALLPS, LOSE);
				retry(game, quit);
				new_level = false;

			}
			
		}
	}
	if (number_of_level == game.count_levels)
	{
		file.seekg(0, ios_base::beg);
		fileCat.seekg(0, ios_base::beg);
		number_of_level = 0;
	}
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
void editCoordsMovementOfCat(vector < Texture>& copy_texture, int keydown_for_cat)
{
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
}
void editCoordsMovementOfBox(vector < Texture>& copy_texture, int keydown_for_box)
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
		copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y;
		copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x + copy_texture[CAT].sizeTexture;
		copy_texture[PRESENT].Y = copy_texture[CAT].Y;
		copy_texture[PRESENT].X = copy_texture[CAT].X + 1;
		break;
	}
}
void showFloorOfPlaceHere(Surface& game, vector<vector<int>> level, vector<Texture> struct_of_textures, int texture)
{
	if (level[struct_of_textures[texture].Y][struct_of_textures[texture].X] == PLACEHERE)
		showTexture(PLACEHERE, struct_of_textures[texture].posTexture, game);
	else
		showTexture(FLOOR, struct_of_textures[texture].posTexture, game);
}
void showPresent(Surface& game, vector<vector<int>> level, vector<Texture> struct_of_textures, int texture)
{
	if (level[struct_of_textures[texture].Y][struct_of_textures[texture].X] == PLACEHERE)
		showTexture(BOX_IN_PLACEHERE, struct_of_textures[texture].posTexture, game);
	else
		showTexture(PRESENT, struct_of_textures[texture].posTexture, game);
}
void showAfterRecurs(Surface& game, vector < Texture> copy_texture)
{
	showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, FLOOR);
	showTexture(CAT, copy_texture[CAT].posTexture, game);
	showPresent(game, game.infOfFild.level, copy_texture, PRESENT);
}
void retry(Surface& game, bool& quit) {
	bool quit2 = false;
	SDL_Rect stretchRect;
	stretchRect.x = 470;
	stretchRect.y = 388;

	showPic(game, stretchRect, BUTTONS, RETRY);
	while (quit2 == false)
	{
		while (SDL_PollEvent(&game.e) != 0)
		{
			if (game.e.type == SDL_QUIT)
			{
				quit = true;
				quit2 = true;
				break;
			}
			else if (game.e.type == SDL_KEYDOWN)
			{
				if (game.e.key.keysym.sym == SDLK_RETURN || game.e.key.keysym.sym == SDLK_KP_ENTER) {
					Mix_PlayChannel(3, game.button, 0) == 3;
					stretchRect.y++;
					showPic(game, stretchRect, PRESSED_BUTTONS, RETRY);
					SDL_Delay(200);

					showPic(game, stretchRect, BUTTONS, RETRY);
					SDL_Delay(200);

					quit2 = true;
					break;
				}
				
				
			}
			if (quit2 == true)break;
		}
	}
}
int playingLevel(Surface& game, fstream& file, vector<vector<int>> catAndGift, vector < Texture> texture_of_elements, bool& quit, int& count_of_sec, bool first)
{
	vector<Texture> copy_texture = texture_of_elements;
	vector<vector<int>> copy_catAndGift = catAndGift;
	static int keydown_for_cat;
	static int keydown_for_box = KEY_PRESS_DEFAULT;
	//int pressed_key_box = keydown_for_box;
	//int pressed_key_cat = keydown_for_cat;

	if (!first)
	{
		copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = 0;
		editCoordsMovementOfCat(copy_texture, keydown_for_cat);
		showTexture(CAT, copy_texture[CAT].posTexture, game);
		copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = CAT;

		if (keydown_for_box != KEY_PRESS_DEFAULT)
		{
			editCoordsMovementOfBox(copy_texture, keydown_for_box);
			keydown_for_box = KEY_PRESS_DEFAULT;
			copy_catAndGift[copy_texture[PRESENT].Y][copy_texture[PRESENT].X] = PRESENT;
			showPresent(game, game.infOfFild.level, copy_texture, PRESENT);
		}

	}
	
	if (win(game, copy_catAndGift) || count_of_sec == 0 || game.count_step == 300) {
		if (win(game, copy_catAndGift))game.result = WIN_WALP;
		else game.result = LOSE;
		return WIN;
	}
		
	//showArrInConsole(copy_catAndGift, 9, 9);
	bool flag = false;
	while (!quit)
	{
		while (SDL_PollEvent(&game.e) != 0)
		{
			if (win(game, copy_catAndGift) || count_of_sec == 0 || game.count_step == 300) {
				if (win(game, copy_catAndGift))game.result = WIN_WALP;
				else game.result = LOSE;
				return WIN;
			}
			if (game.e.type == SDL_QUIT || flag)
			{
				stop_timer = true;
				bool quit2 = false;
				exit(quit2, game);
				if (quit2) return EXIT_TO_MENU;
				flag = false;
				
				stop_timer = false;
				thread th(timer, ref(game), ref(count_of_sec));//ref - используется 
				th.detach();
				SDL_Rect coord;
				inisialitCoordOfWallp(coord);
				showPic(game, coord, TEXTURES, BACKGROUND_TIME);
				field(game, game.infOfFild.level, file, copy_texture[CAT].posTexture);
				field(game, copy_catAndGift, file, copy_texture[CAT].posTexture);
				//maxNumberOfCounter(game);
				countOfStep(game, true, true);
				break;
			}
			else if (game.e.type == SDL_KEYDOWN)
			{
				switch (game.e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					flag = true;
					break;
				case SDLK_LEFT:
					if (game.infOfFild.level[copy_texture[CAT].Y][copy_texture[CAT].X - 1] != WALL)
					{

						if (copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X - 1] != PRESENT)
						{
							countOfStep(game, true);
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							//if (pressed_key_cat == SDLK_RIGHT && pressed_key_box == KEY_PRESS_DEFAULT)
							//{
							//	//pressed_key_box = KEY_PRESS_DEFAULT;
							//	return RECURSION;
							//}
							keydown_for_cat = SDLK_LEFT;

							int result = playingLevel(game, file, copy_catAndGift,/* level, */copy_texture, quit, count_of_sec);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
								showTexture(CAT, copy_texture[CAT].posTexture, game);
							else
								return EXIT_TO_MENU;
						}
						else if (copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X - 1] == PRESENT
							&& game.infOfFild.level[copy_texture[CAT].Y][copy_texture[CAT].X - 2] != WALL
							&& copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X - 2] != PRESENT)
						{
							countOfStep(game, true);
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y;
							copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x - copy_texture[CAT].sizeTexture;

							copy_texture[PRESENT].Y = copy_texture[CAT].Y;
							copy_texture[PRESENT].X = copy_texture[CAT].X - 1;

							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, PRESENT);
							copy_texture[FLOOR].posTexture = copy_texture[PRESENT].posTexture;
							copy_texture[FLOOR].posTexture.x = copy_texture[PRESENT].posTexture.x - copy_texture[PRESENT].sizeTexture;

							copy_texture[FLOOR].Y = copy_texture[PRESENT].Y;
							copy_texture[FLOOR].X = copy_texture[PRESENT].X - 1;

							keydown_for_cat = SDLK_LEFT;
							keydown_for_box = SDLK_LEFT;
							int result = playingLevel(game, file, copy_catAndGift,/* level,*/ copy_texture, quit, count_of_sec);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								showAfterRecurs(game, copy_texture);
							}
							else
								return EXIT_TO_MENU;
						}
					}
					break;
				case SDLK_RIGHT:

					if (game.infOfFild.level[copy_texture[CAT].Y][copy_texture[CAT].X + 1] != WALL)
					{

						if (copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X + 1] != PRESENT)
						{
							countOfStep(game, true);
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							//if (pressed_key_cat == SDLK_LEFT && pressed_key_box == KEY_PRESS_DEFAULT)
							//{
							//	//pressed_key_box = KEY_PRESS_DEFAULT;
							//	return RECURSION;
							//}
							keydown_for_cat = SDLK_RIGHT;
							int result = playingLevel(game, file, copy_catAndGift,/* level,*/ copy_texture, quit, count_of_sec);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
								showTexture(CAT, copy_texture[CAT].posTexture, game);
							else
								return EXIT_TO_MENU;
						}
						else if (copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X + 1] == PRESENT
							&& game.infOfFild.level[copy_texture[CAT].Y][copy_texture[CAT].X + 2] != WALL
							&& copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X + 2] != PRESENT)
						{
							countOfStep(game, true);
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y;
							copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x + copy_texture[CAT].sizeTexture;

							copy_texture[PRESENT].Y = copy_texture[CAT].Y;
							copy_texture[PRESENT].X = copy_texture[CAT].X + 1;

							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, PRESENT);
							copy_texture[FLOOR].posTexture = copy_texture[PRESENT].posTexture;
							copy_texture[FLOOR].posTexture.x = copy_texture[PRESENT].posTexture.x + copy_texture[PRESENT].sizeTexture;

							copy_texture[FLOOR].Y = copy_texture[PRESENT].Y;
							copy_texture[FLOOR].X = copy_texture[PRESENT].X + 1;

							keydown_for_cat = SDLK_RIGHT;
							keydown_for_box = SDLK_RIGHT;
							int result = playingLevel(game, file, copy_catAndGift, copy_texture, quit, count_of_sec);

							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								showAfterRecurs(game, copy_texture);
							}
							else
								return EXIT_TO_MENU;
						}
					}
					break;
				case SDLK_UP:
					if (game.infOfFild.level[copy_texture[CAT].Y - 1][copy_texture[CAT].X] != WALL)
					{

						if (copy_catAndGift[copy_texture[CAT].Y - 1][copy_texture[CAT].X] != PRESENT)
						{
							countOfStep(game, true);
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							//if (pressed_key_cat == SDLK_DOWN && pressed_key_box == KEY_PRESS_DEFAULT)
							//{
							//	//pressed_key_box = KEY_PRESS_DEFAULT;
							//	return RECURSION;
							//}
							keydown_for_cat = SDLK_UP;
							int result = playingLevel(game, file, copy_catAndGift, /*level,*/ copy_texture, quit, count_of_sec);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
								showTexture(CAT, copy_texture[CAT].posTexture, game);
							else
								return EXIT_TO_MENU;
						}
						else if (copy_catAndGift[copy_texture[CAT].Y - 1][copy_texture[CAT].X] == PRESENT
							&& game.infOfFild.level[copy_texture[CAT].Y - 2][copy_texture[CAT].X] != WALL
							&& copy_catAndGift[copy_texture[CAT].Y - 2][copy_texture[CAT].X] != PRESENT)
						{
							countOfStep(game, true);
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y - copy_texture[CAT].sizeTexture;
							copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x;

							copy_texture[PRESENT].Y = copy_texture[CAT].Y - 1;
							copy_texture[PRESENT].X = copy_texture[CAT].X;

							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, PRESENT);
							copy_texture[FLOOR].posTexture = copy_texture[PRESENT].posTexture;
							copy_texture[FLOOR].posTexture.y = copy_texture[PRESENT].posTexture.y - copy_texture[PRESENT].sizeTexture;

							copy_texture[FLOOR].Y = copy_texture[PRESENT].Y - 1;
							copy_texture[FLOOR].X = copy_texture[PRESENT].X;

							keydown_for_cat = SDLK_UP;
							keydown_for_box = SDLK_UP;
							int result = playingLevel(game, file, copy_catAndGift, /*level,*/ copy_texture, quit, count_of_sec);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								showAfterRecurs(game, copy_texture);
							}
							else
								return EXIT_TO_MENU;
						}
					}
					break;
				case SDLK_DOWN:
					if (game.infOfFild.level[copy_texture[CAT].Y + 1][copy_texture[CAT].X] != WALL)
					{

						if (copy_catAndGift[copy_texture[CAT].Y + 1][copy_texture[CAT].X] != PRESENT)
						{
							countOfStep(game, true);
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							/*if (pressed_key_cat == SDLK_UP && pressed_key_box == KEY_PRESS_DEFAULT)
							{
								return RECURSION;
							}*/
							keydown_for_cat = SDLK_DOWN;
							int result = playingLevel(game, file, copy_catAndGift, /*level,*/ copy_texture, quit, count_of_sec);
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
							&& game.infOfFild.level[copy_texture[CAT].Y + 2][copy_texture[CAT].X] != WALL
							&& copy_catAndGift[copy_texture[CAT].Y + 2][copy_texture[CAT].X] != PRESENT)
						{
							countOfStep(game, true);
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y + copy_texture[CAT].sizeTexture;
							copy_texture[PRESENT].posTexture.x = copy_texture[CAT].posTexture.x;

							copy_texture[PRESENT].Y = copy_texture[CAT].Y + 1;
							copy_texture[PRESENT].X = copy_texture[CAT].X;

							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, PRESENT);
							copy_texture[FLOOR].posTexture = copy_texture[PRESENT].posTexture;
							copy_texture[FLOOR].posTexture.y = copy_texture[PRESENT].posTexture.y + copy_texture[PRESENT].sizeTexture;

							copy_texture[FLOOR].Y = copy_texture[PRESENT].Y + 1;
							copy_texture[FLOOR].X = copy_texture[PRESENT].X;

							keydown_for_cat = SDLK_DOWN;
							keydown_for_box = SDLK_DOWN;
							int result = playingLevel(game, file, copy_catAndGift, /*level,*/ copy_texture, quit, count_of_sec);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								showAfterRecurs(game, copy_texture);
							}
							else
								return EXIT_TO_MENU;
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
				//showArrInConsole(copy_catAndGift, 9, 9);
				if (pressed_keys[KEY_PRESS_LEFT_CTRL] && pressed_keys[KEY_PRESS_Z] && !first)
				{
					countOfStep(game, false);
					showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
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
bool characterMovement(Surface& game, fstream& file, fstream& fileCat, bool& quit, bool new_level)
{//передвижение персонажей
	stop_timer = false;
	int count_of_sec = 5;
	thread th(timer, ref(game), ref(count_of_sec));//ref - используется 
	th.detach();
	vector<Texture> texture_of_level;
	for (int i = 0; i < CountOfTexture; i++)
	{
		Texture texture;
		texture_of_level.push_back(texture);
	}

	texture_of_level[CAT].posTexture.y = 0;
	texture_of_level[CAT].posTexture.x = 0;

	//fstream fileCat("position.TXT");

	showTexture(BACKGROUND_TIME, texture_of_level[CAT].posTexture, game);
	field(game, game.infOfFild.level, file, texture_of_level[CAT].posTexture);

	//vector<vector<int>> catAndGift;
	createMap(game, game.infOfFild.catAndGift, fileCat, new_level);
	field(game, game.infOfFild.catAndGift, fileCat, texture_of_level[CAT].posTexture);

	for (int y = 0; y < (game.infOfFild.height); y++)
	{
		for (int x = 0; x < (game.infOfFild.width); x++)
		{
			if (game.infOfFild.catAndGift[y][x] == CAT)
			{
				texture_of_level[CAT].X = x;
				texture_of_level[CAT].Y = y;
			}
			if (game.infOfFild.level[y][x] == PLACEHERE) {
				game.infOfFild.count_place++;
			}
		}
	}

	texture_of_level[CAT].posTexture.x = ((SCREEN_WIDTH / 2) - ((game.infOfFild.width) / 2.0 * texture_of_level[CAT].sizeTexture)) + texture_of_level[CAT].X * texture_of_level[CAT].sizeTexture;
	texture_of_level[CAT].posTexture.y = ((SCREEN_HEIGHT / 2) - ((game.infOfFild.height) / 2.0 * texture_of_level[CAT].sizeTexture)) + texture_of_level[CAT].Y * texture_of_level[CAT].sizeTexture;
	countOfStep(game, true, true);

	if (playingLevel(game, file, game.infOfFild.catAndGift,  texture_of_level, quit, count_of_sec, true) == EXIT_TO_MENU)
	{
		return EXIT_TO_MENU;
	}
	else
	{
		return WIN;
	}
}
void createMap(Surface& game, vector<vector<int>>& array, fstream& file, bool new_level)
{// чтение файла и создание массива
	static int i = 0;

	if (!file.is_open())
	{
		std::cerr << "Error opening file!" << std::endl;
	}
	else
	{
		if (!new_level)
		{
			file.seekg(i, ios_base::beg);
		}
		i = file.tellg();
		string str;
		file >> str;
		(game.infOfFild.height) = stoi(str);
		file >> str;
		(game.infOfFild.width) = stoi(str);
		for (int i = 0; i < (game.infOfFild.height); i++)
		{
			vector<int> arr;
			for (int j = 0; j < (game.infOfFild.width); j++)
			{
				file >> str;
				arr.push_back(stoi(str));
			}
			array.push_back(arr);
		}

	}
}
void field(Surface& game, vector<vector<int>> array, fstream& file, SDL_Rect posTexture)
{//тут будет отображаться массив в-виде картинки
	int sizeTexture = 50;

	//SDL_Rect posTexture;
	double X = (SCREEN_WIDTH / 2) - (game.infOfFild.width / 2.0 * sizeTexture);
	posTexture.x = X;
	posTexture.y = (SCREEN_HEIGHT / 2) - (game.infOfFild.height / 2.0 * sizeTexture);
	for (int i = 0; i < game.infOfFild.height; i++) {
		for (int j = 0; j < game.infOfFild.width; j++) {
			switch (array[i][j])
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
				if (game.infOfFild.level[i][j] == PLACEHERE)
				{
					showTexture(BOX_IN_PLACEHERE, posTexture, game);
				}
				else
				{
					showTexture(PRESENT, posTexture, game);
				}
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
bool win(Surface& game, vector<vector<int>> copy_catAndGift) {
	int count = 0;
	for (int i = 0; i < game.infOfFild.height; i++)
	{
		for (int j = 0; j < game.infOfFild.width; j++)
		{
			if (game.infOfFild.level[i][j] == PLACEHERE && copy_catAndGift[i][j] == PRESENT)
				count++;
		}
	}
	if (count == game.infOfFild.count_place) return 1;
	return 0;

}
void showTexture(int i, SDL_Rect posTexture, Surface& game)
{
	game.CurrentSurface = game.Texture[i];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &posTexture);
	SDL_UpdateWindowSurface(game.Window);
}
void countOfStep(Surface& game, bool what, bool zero)
{
	int size = 20;

	int last_number = 0;
	SDL_Rect texture_of_number;
	texture_of_number.y = 35;

	if (what && !zero) 
	{

		game.count_step++;

	}
	else if (!what && !zero) game.count_step--;
	else
	{

		//maxNumberOfCounter(game, size);
		texture_of_number.x = size * 7;
		int c = 300;
		for (int i = 0; i < 3; i++) 
		{
			//int c = last_number;
			last_number = c % 10;//
			c /= 10;
			showPic(game, texture_of_number, NUMBERS, last_number);
			texture_of_number.x -= size;
		}
		texture_of_number.x = size * 4;
		showPic(game, texture_of_number, NUMBERS, 11);

		texture_of_number.x = size * 3;
		c = game.count_step;
		for (int i = 0; i < 3; i++) {
			last_number = c % 10;
			c /= 10;
			showPic(game, texture_of_number, NUMBERS, last_number);
			texture_of_number.x -= size;
		}
	
	}


	if (what && game.count_step % 10 == 0 || !what && game.count_step % 10 == 9) 
	{
		last_number = game.count_step/10 % 10;
		texture_of_number.x = size * 2;
		showPic(game, texture_of_number, NUMBERS, last_number);
	}
	if (what && (game.count_step / 10) % 10 == 0 || !what && (game.count_step / 10) % 10 == 9)
	{
		last_number = game.count_step / 100;
		texture_of_number.x = size;
		showPic(game, texture_of_number, NUMBERS, last_number);
	}
	last_number = game.count_step % 10;
	texture_of_number.x = size * 3;
	showPic(game, texture_of_number, NUMBERS, last_number);


}
void exit(bool& quit, Surface& game)
{
	bool quit2 = false;
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	showPic(game, stretchRect, WALLPS, MENU_EXIT);
	stretchRect.x = 160;
	stretchRect.y = 370;
	int i = 3;
	int a = 0;
	int current_pressed_button = i;

	showPic(game, stretchRect, PRESSED_BUTTONS, YES);
	stretchRect.x += 300;
	i++;
	showPic(game, stretchRect, BUTTONS, NO);
	while (quit2 == false)
	{
		while (SDL_PollEvent(&game.e) != 0)
		{
			if (game.e.type == SDL_QUIT)
			{
				quit = true;
				quit2 = true;
				break;
			}
			else if (game.e.type == SDL_KEYDOWN)
			{

				switch (game.e.key.keysym.sym)
				{
				case SDLK_RIGHT:
					if (current_pressed_button == YES)
					{
						showPic(game, stretchRect, PRESSED_BUTTONS, NO);
						stretchRect.x -= 300;
						showPic(game, stretchRect, BUTTONS, YES);
						current_pressed_button++;
					}
					break;
				case SDLK_LEFT:
					if (current_pressed_button == NO)
					{
						showPic(game, stretchRect, PRESSED_BUTTONS, YES);
						stretchRect.x += 300;
						showPic(game, stretchRect, BUTTONS, NO);
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
				}
			}
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

	game.music1 = Mix_LoadMUS("sound\\music1.wav");
	game.music2 = Mix_LoadMUS("sound\\music1.wav");
	if (game.music1 == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	if (game.music2 == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}



	game.button = Mix_LoadWAV("sound\\button.wav");
	game.box = Mix_LoadWAV("sound\\box.wav");
	game.intro = Mix_LoadWAV("sound\\intro.wav");
	//Если что-то пошло не так
	if ((game.button == NULL) || (game.box == NULL))
	{
		return false;
	}
	//if (Mix_PlayingMusic() == 0)
	//{
	//	//Play the music
	//	Mix_PlayMusic(game.music, -1);
	//}
	game.button = Mix_LoadWAV("sound\\button.wav");
	game.box = Mix_LoadWAV("sound\\box.wav");
	game.intro = Mix_LoadWAV("sound\\intro.wav");
	//Если что-то пошло не так
	if ((game.button == NULL) || (game.box == NULL))
	{
		return false;
	}
	game.Wallps[0] = loadSurface("Wallps\\teamLogo.bmp");
	game.Wallps[1] = loadSurface("Wallps\\gameLogo.bmp");
	game.Wallps[2] = loadSurface("Wallps\\MainMenu.bmp");
	game.Wallps[MENU_EXIT] = loadSurface("Wallps\\MenuExit.bmp");
	game.Wallps[WIN_WALP] = loadSurface("Wallps\\Win.bmp");
	game.Wallps[LOSE] = loadSurface("Wallps\\Lose.bmp");

	game.Buttons[0] = loadSurface("buttons\\PlayGame1.bmp");
	game.Buttons[1] = loadSurface("buttons\\HowToPlay1.bmp");
	game.Buttons[2] = loadSurface("buttons\\Exit1.bmp");
	game.Buttons[YES] = loadSurface("buttons\\Yes1.bmp");
	game.Buttons[NO] = loadSurface("buttons\\No1.bmp");
	game.Buttons[NEXT] = loadSurface("buttons\\Next1.bmp");
	game.Buttons[BACK] = loadSurface("buttons\\Back1.bmp");
	game.Buttons[RETRY] = loadSurface("buttons\\Retry.bmp");
	game.PressedButtons[0] = loadSurface("pressed_buttons\\PlayGame2.bmp");
	game.PressedButtons[1] = loadSurface("pressed_buttons\\HowToPlay2.bmp");
	game.PressedButtons[2] = loadSurface("pressed_buttons\\Exit2.bmp");
	game.PressedButtons[YES] = loadSurface("pressed_buttons\\Yes2.bmp");
	game.PressedButtons[NO] = loadSurface("pressed_buttons\\No2.bmp");
	game.PressedButtons[NEXT] = loadSurface("pressed_buttons\\Next2.bmp");
	game.PressedButtons[BACK] = loadSurface("pressed_buttons\\Back2.bmp");
	game.PressedButtons[RETRY] = loadSurface("pressed_buttons\\Retry.bmp");
	for (int i = 0; i < CountOfButtons; i++)
	{
		if (game.Buttons[i] == NULL || game.PressedButtons[i] == NULL) {
			printf("Failed to load up button!\n");
			success = false;
		}
	}
	game.Texture[EMPTY] = loadSurface("textures\\empty.bmp");
	game.Texture[WALL] = loadSurface("textures\\wall.bmp");
	game.Texture[FLOOR] = loadSurface("textures\\floor.bmp");
	game.Texture[CAT] = loadSurface("textures\\mainCat.bmp");
	game.Texture[PRESENT] = loadSurface("textures\\PresentBox.bmp");
	game.Texture[PLACEHERE] = loadSurface("textures\\PlaceHere.bmp");
	game.Texture[BACKGROUND] = loadSurface("textures\\Background.bmp");
	game.Texture[BOX_IN_PLACEHERE] = loadSurface("textures\\BoxInPlaceHere.bmp");
	game.Texture[BACKGROUND_TIME] = loadSurface("textures\\BackgroundTime.bmp");

	game.WindowsHowToPlay[FIRST] = loadSurface("how_to_play\\1.bmp");
	game.WindowsHowToPlay[SECOND] = loadSurface("how_to_play\\2.bmp");
	game.WindowsHowToPlay[THIRD] = loadSurface("how_to_play\\3.bmp");
	game.WindowsHowToPlay[FOURTH] = loadSurface("how_to_play\\4.bmp");
	game.WindowsHowToPlay[FIFTH] = loadSurface("how_to_play\\5.bmp");
	game.WindowsHowToPlay[SIXTH] = loadSurface("how_to_play\\6.bmp");

	game.Numbers[0] = loadSurface("numbers\\0 number.bmp");
	game.Numbers[1] = loadSurface("numbers\\1 number.bmp");
	game.Numbers[2] = loadSurface("numbers\\2 number.bmp");
	game.Numbers[3] = loadSurface("numbers\\3 number.bmp");
	game.Numbers[4] = loadSurface("numbers\\4 number.bmp");
	game.Numbers[5] = loadSurface("numbers\\5 number.bmp");
	game.Numbers[6] = loadSurface("numbers\\6 number.bmp");
	game.Numbers[7] = loadSurface("numbers\\7 number.bmp");
	game.Numbers[8] = loadSurface("numbers\\8 number.bmp");
	game.Numbers[9] = loadSurface("numbers\\9 number.bmp");
	game.Numbers[10] = loadSurface("numbers\\colon.bmp");
	game.Numbers[11] = loadSurface("numbers\\slash.bmp");

	game.WindowLevel[0] = loadSurface("windowlevel\\1.bmp");
	game.WindowLevel[1] = loadSurface("windowlevel\\2.bmp");
	game.WindowLevel[2] = loadSurface("windowlevel\\3.bmp");
	game.WindowLevel[3] = loadSurface("windowlevel\\4.bmp");
	game.WindowLevel[4] = loadSurface("windowlevel\\5.bmp");

	game.Comic[0] = loadSurface("comic\\0.bmp");
	game.Comic[1] = loadSurface("comic\\1.bmp");
	game.Comic[2] = loadSurface("comic\\2.bmp");
	game.Comic[3] = loadSurface("comic\\3.bmp");
	game.Comic[4] = loadSurface("comic\\4.bmp");

	for (int i = 0; i < CountOfComic; i++)
	{
		if (game.Comic[i] == NULL)
		{
			printf("Failed to load up comic!\n");
			success = false;
		}
	}
	for (int i = 0; i < CountOfLeveles; i++)
	{
		if (game.Numbers[i] == NULL)
		{
			printf("Failed to load up image!\n");
			success = false;
		}
	}
	for (int i = 0; i < 12; i++)
	{
		if (game.Numbers[i] == NULL)
		{
			printf("Failed to load up image!\n");
			success = false;
		}
	}
	for (int i = 0; i < CountOdArrs::CountOfTexture; i++)
	{
		if (game.Texture[i] == NULL)
		{
			printf("Failed to load up image!\n");
			success = false;
		}
	}

	return success;
}
void close(Surface& game)
{
	//После уничтожения окна не забудь указатели указать на NULL
	//Освободить поверхность
	Mix_FreeMusic(game.music1);
	game.music1 = NULL;
	for (int i = 0; i < CountOfWallps; ++i)
	{
		SDL_FreeSurface(game.Wallps[i]);
		game.Wallps[i] = NULL;
	}
	//Уничтожить окно
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


