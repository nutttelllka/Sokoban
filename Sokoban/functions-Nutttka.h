#pragma once
#include "Structures.h"
#include "Enums.h"
using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
//#define KMOD_CTRL_z (SDLK_LCTRL|SDLK_z)
void intro(Surface& game);
bool init(Surface& game);
bool loadMedia(Surface& game);
void close(Surface& game);
void menu(bool& quit, int i, int& i_for_buttons, int& current_pressed_button,Surface& game);
void playGame(Surface& game);
void showButton(Surface& game, int i, SDL_Rect stretchRectб, int y_of_button1 = 250, int y_of_button2 = 250 + 70, int y_of_button3 = 250 + 140);
void backgroundMenu(Surface& game);
void exit(bool& quit, Surface& game);
void createMap(int**& arr, int* height, int* width, fstream& file);
void field(int** level, int height, int width, fstream& file, SDL_Rect posTexture, Surface& game);
void characterMovement(int**& level, int* height, int* width, fstream& file, Surface& game);
void createArr(int**& arr, int height, int width);
void clearMemory(int**& arr, int height);
void showTexture(int i, SDL_Rect posTexture, Surface& game);
bool isPressed(int keyCode);
bool isReleased(int keyCode);

bool pressed_keys[3] = {};

//const int CountOfLogos = 4;
//const int CountOfButtons = 5;
//const int CountOfPressedButtons = 5;
//const int CountOfTexture = 5;

//тут был Степа
SDL_Surface* loadSurface(string path);


//SDL_Surface* CurrentSurface
//Mix_Music* music = NULL;
//SDL_Window* Window = NULL;
//SDL_Surface* ScreenSurface = NULL;

//SDL_Surface* Logos[CountOfLogos];
//SDL_Surface* Buttons[CountOfButtons];
//SDL_Surface* PressedButtons[CountOfPressedButtons];
//SDL_Surface* Texture[CountOfTexture];

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
						Mix_FreeMusic(game.music);
						game.music = NULL;
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
void menu(bool& quit, int i, int& i_for_buttons, int& current_pressed_button,Surface& game)
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
							showButton(game,HOW_TO_PLAY, stretchRect);
					
						else if (current_pressed_button == HOW_TO_PLAY)
							showButton(game,EXIT, stretchRect);
				
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
							showButton(game,HOW_TO_PLAY, stretchRect);

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
						showButton(game,GAME, stretchRect);
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
						playGame(game);
						backgroundMenu(game);
						showButton(game, HOW_TO_PLAY, stretchRect);
						showButton(game,EXIT, stretchRect);
						stretchRect.y = y_of_button1;
						break;
					case HOW_TO_PLAY:

						break;
					case EXIT:
						exit(quit, game);
						backgroundMenu(game);
						showButton(game,GAME, stretchRect);
						showButton(game,HOW_TO_PLAY, stretchRect);
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
void playGame(Surface& game)
{
	fstream file("fields.TXT");

	int** level;
	int height = 0;
	int width = 0;

	createMap(level, &height, &width, file);
	characterMovement(level, &height, &width, file, game);
	clearMemory(level, height);

}
void characterMovement(int**& level, int* height, int* width, fstream& file, Surface& game)
{//передвижение персонажей
	SDL_Rect posTexture;
	posTexture.x = 0;
	posTexture.y = 0;


	showTexture(BACKGROUND, posTexture, game);
	field(level, *height, *width, file, posTexture, game);

	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
		}
	}
}
void field(int** level, int height, int width, fstream& file, SDL_Rect posTexture, Surface& game) {//тут будет отображаться массив в-виде картинки
	int sizeTexture = 50;

	//SDL_Rect posTexture;
	double X = (SCREEN_WIDTH / 2) - (width / 2.0 * sizeTexture);
	posTexture.x = X;
	posTexture.y = (SCREEN_HEIGHT / 2) - (height / 2.0 * sizeTexture);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
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
			}
			posTexture.x += sizeTexture;
		}
		posTexture.x = X;
		posTexture.y += sizeTexture;
	}

}
void showTexture(int i, SDL_Rect posTexture, Surface& game)
{
	game.CurrentSurface = game.Texture[i];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &posTexture);
	SDL_UpdateWindowSurface(game.Window);
}
void createMap(int**& arr, int* height, int* width, fstream& file) {// чтение файла и создание массива

	if (!file.is_open())
	{
		std::cerr << "Error opening file!" << std::endl;
		//More error handling code goes here
	}
	else {
		string str;
		//getline(file, str); // читает строку и переходит на новую, проблема - читает целую строку
		file >> str;
		(*height) = stoi(str);
		file >> str;
		(*width) = stoi(str);
		createArr(arr, *height, *width);
		for (int i = 0; i < (*height); i++) 
		{
			for (int j = 0; j < (*width); j++) 
			{
				file >> str;
				arr[i][j] = stoi(str);
			}
		}
		for (int i = 0; i < (*height); i++)
		{
			for (int j = 0; j < (*width); j++) 
			{
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}
}
void createArr(int**& arr, int height, int width)
{
	arr = new int* [height];
	for (int i = 0; i < height; i++) 
	{
		arr[i] = new int[width];

	}
}
void clearMemory(int**& arr, int height) 
{
	for (int i = 0; i < height; i++) 
	{
		delete[] arr[i];
	}
	delete[] arr;
	arr = nullptr;
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
void showButton(Surface& game,int i, SDL_Rect stretchRect, int y_of_button1, int y_of_button2, int y_of_button3)
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
	//Ôëàã óñïåøíîé çàãðóçêè
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
	game.music = Mix_LoadMUS("sound\\intro.wav");
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
	game.Texture[BACKGROUND] = loadSurface("Background.bmp");
	if (game.Texture[BACKGROUND] == NULL)
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


