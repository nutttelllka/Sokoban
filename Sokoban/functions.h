#pragma once
using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL,
};
enum Object
{
	EMPTY,
	WALL, 
	FLOOR, 
	CAT, 
	BACKGROUND,
};
enum Buttons
{
	GAME,
	HOW_TO_PLAY,
	EXIT,
	YES,
	NO,
};
enum Wallps
{
	LOGO_OF_GROUP,
	LOGO_OF_GAME,
	MAIN_MENU,
	MENU_EXIT,

};
enum CountOdArrs
{
	CountOfLogos = 4,
	CountOfButtons = 5,
	CountOfPressedButtons = 5,
	CountOfTexture = 5,
};

bool init();
bool loadMedia();
void close();
void menu(bool& quit, int i, int& i_for_buttons, int& current_pressed_button, SDL_Surface* CurrentSurface);
void playGame(SDL_Surface* CurrentSurface);
void showButton(SDL_Surface* CurrentSurface, int i, SDL_Rect stretchRectб, int y_of_button1 = 250, int y_of_button2 = 250 + 70, int y_of_button3 = 250 + 140);
void backgroundMenu(SDL_Surface* CurrentSurface);
void exit(bool& quit, SDL_Surface* CurrentSurface);
void createMap(int**& arr, int* height, int* width, fstream& file);
void field(int** level, int height, int width, fstream& file, SDL_Rect posTexture, SDL_Surface* CurrentSurface);
void characterMovement(int**& level, int* height, int* width, fstream& file, SDL_Surface* CurrentSurface);
void createArr(int**& arr, int height, int width);
void clearMemory(int**& arr, int height);
void showTexture(int i, SDL_Rect posTexture, SDL_Surface* CurrentSurface);

//const int CountOfLogos = 4;
//const int CountOfButtons = 5;
//const int CountOfPressedButtons = 5;
//const int CountOfTexture = 5;
//SDL_Surface* CurrentSurface = NULL;

SDL_Surface* loadSurface(string path);
Mix_Music* music = NULL;
SDL_Window* Window = NULL;
SDL_Surface* ScreenSurface = NULL;

SDL_Surface* Logos[CountOfLogos];
SDL_Surface* Buttons[CountOfButtons];
SDL_Surface* PressedButtons[CountOfPressedButtons];
SDL_Surface* Texture[CountOfTexture];

void backgroundMenu(SDL_Surface* CurrentSurface)
{
	CurrentSurface = Logos[2];
	SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, NULL);
	SDL_UpdateWindowSurface(Window);
}
void menu(bool& quit, int i, int& i_for_buttons, int& current_pressed_button, SDL_Surface* CurrentSurface)
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

	backgroundMenu(CurrentSurface);
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			else if (i_for_buttons == 0)
			{
				CurrentSurface = PressedButtons[i_for_buttons];
				SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
				SDL_UpdateWindowSurface(Window);
				stretchRect.y += interval_Y;
				i_for_buttons++;
			}
			else if (i_for_buttons < 3)
			{
				CurrentSurface = Buttons[i_for_buttons];
				SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
				SDL_UpdateWindowSurface(Window);
				stretchRect.y += interval_Y;
				i_for_buttons++;
			}
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
							showButton( CurrentSurface,HOW_TO_PLAY, stretchRect);
					
						else if (current_pressed_button == HOW_TO_PLAY)
							showButton(CurrentSurface,EXIT, stretchRect);
				
						current_y -= interval_Y;
						stretchRect.y = current_y;
						CurrentSurface = PressedButtons[current_pressed_button];
						SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
						SDL_UpdateWindowSurface(Window);
					}
					break;

				case SDLK_DOWN:
					if (current_pressed_button < 2)
					{

						current_pressed_button++;

						if (current_pressed_button == EXIT)
							showButton(CurrentSurface,HOW_TO_PLAY, stretchRect);

						else if (current_pressed_button == HOW_TO_PLAY)
							showButton( CurrentSurface, GAME, stretchRect);

						current_y += interval_Y;
						stretchRect.y = current_y;
						CurrentSurface = PressedButtons[current_pressed_button];
						SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
						SDL_UpdateWindowSurface(Window);
					}
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
					switch (current_pressed_button)
					{
					case GAME:
						playGame(CurrentSurface);
						backgroundMenu(CurrentSurface);
						showButton( CurrentSurface, HOW_TO_PLAY, stretchRect);
						showButton(CurrentSurface,EXIT, stretchRect);
						stretchRect.y = y_of_button1;
						break;
					case HOW_TO_PLAY:

						break;
					case EXIT:

						exit(quit, CurrentSurface);
						backgroundMenu( CurrentSurface);
						showButton( CurrentSurface,GAME, stretchRect);
						showButton(CurrentSurface,HOW_TO_PLAY, stretchRect);
						stretchRect.y = y_of_button3;
						break;
					}
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
				CurrentSurface = PressedButtons[current_pressed_button];
				SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
				SDL_UpdateWindowSurface(Window);
			}
		}
	}

}
void playGame(SDL_Surface* CurrentSurface)
{
	fstream file("fields.TXT");

	int** level;
	int height = 0;
	int width = 0;

	createMap(level, &height, &width, file);
	characterMovement(level, &height, &width, file, CurrentSurface);
	clearMemory(level, height);

}
void characterMovement(int**& level, int* height, int* width, fstream& file, SDL_Surface* CurrentSurface)
{//передвижение персонажей
	SDL_Rect posTexture;
	posTexture.x = 0;
	posTexture.y = 0;


	showTexture(BACKGROUND, posTexture, CurrentSurface);
	field(level, *height, *width, file, posTexture, CurrentSurface);

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
void field(int** level, int height, int width, fstream& file, SDL_Rect posTexture, SDL_Surface* CurrentSurface) {//тут будет отображаться массив в-виде картинки
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

				showTexture(WALL, posTexture, CurrentSurface);
				break;
			case FLOOR:

				showTexture(FLOOR, posTexture,CurrentSurface);

				break;
			case CAT:

				showTexture(CAT, posTexture, CurrentSurface);
				break;
			}
			posTexture.x += sizeTexture;
		}
		posTexture.x = X;
		posTexture.y += sizeTexture;
	}

}
void showTexture(int i, SDL_Rect posTexture, SDL_Surface* CurrentSurface)
{
	CurrentSurface = Texture[i];
	SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &posTexture);
	SDL_UpdateWindowSurface(Window);
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
void exit(bool& quit, SDL_Surface* CurrentSurface)
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
	CurrentSurface = Logos[MENU_EXIT];
	SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, NULL);
	SDL_UpdateWindowSurface(Window);
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
			else if (a == 0)
			{
				CurrentSurface = PressedButtons[current_pressed_button];
				SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
				SDL_UpdateWindowSurface(Window);
				stretchRect.x += 300;
				i++;
				CurrentSurface = Buttons[i];
				SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
				SDL_UpdateWindowSurface(Window);
				a++;
			}
			else
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_RIGHT:
					if (current_pressed_button == YES)
					{
						CurrentSurface = PressedButtons[NO];
						SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
						SDL_UpdateWindowSurface(Window);
						stretchRect.x -= 300;
						CurrentSurface = Buttons[YES];
						SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
						SDL_UpdateWindowSurface(Window);
						current_pressed_button++;
					}
					break;
				case SDLK_LEFT:
					if (current_pressed_button == NO)
					{
						//stretchRect.x -= 400;
						CurrentSurface = PressedButtons[YES];
						SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
						SDL_UpdateWindowSurface(Window);

						stretchRect.x += 300;
						CurrentSurface = Buttons[NO];
						SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
						SDL_UpdateWindowSurface(Window);
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
						//_exit;
						break;
					}

				}
			}
			if (quit2 == true)break;
		}
	}
}
void showButton(SDL_Surface* CurrentSurface,int i, SDL_Rect stretchRect, int y_of_button1, int y_of_button2, int y_of_button3)
{
	if (i == 0)stretchRect.y = y_of_button1;
	if (i == 1)stretchRect.y = y_of_button2;
	if (i == 2)stretchRect.y = y_of_button3;
	CurrentSurface = Buttons[i];
	SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
	SDL_UpdateWindowSurface(Window);
}
bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else 
	{
		Window = SDL_CreateWindow(" Sokoban",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (Window == NULL) 
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else 
		{
			ScreenSurface = SDL_GetWindowSurface(Window);
		}
	}
	return success;
}
bool loadMedia()
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
	music = Mix_LoadMUS("sound\\intro.wav");
	if (music == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(music, -1);
	}
	Logos[0] = loadSurface("teamLogo.bmp");
	if (Logos[0] == NULL)
	{
		printf("Failed to load default image!\n");
		success = false;
	}
	Logos[1] = loadSurface("gameLogo.bmp");
	if (Logos[1] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	Logos[2] = loadSurface("MainMenu.bmp");
	if (Logos[2] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	Logos[MENU_EXIT] = loadSurface("MenuExit.bmp");
	if (Logos[MENU_EXIT] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	Buttons[0] = loadSurface("PlayGame1.bmp");
	if (Buttons[0] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	Buttons[1] = loadSurface("HowToPlay1.bmp");
	if (Buttons[1] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	Buttons[2] = loadSurface("Exit1.bmp");
	if (Buttons[2] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	Buttons[YES] = loadSurface("Yes1.bmp");
	if (Buttons[YES] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	Buttons[NO] = loadSurface("No1.bmp");
	if (Buttons[NO] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	PressedButtons[0] = loadSurface("PlayGame2.bmp");
	if (PressedButtons[0] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	PressedButtons[1] = loadSurface("HowToPlay2.bmp");
	if (PressedButtons[1] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	PressedButtons[2] = loadSurface("Exit2.bmp");
	if (PressedButtons[2] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	PressedButtons[YES] = loadSurface("Yes2.bmp");
	if (PressedButtons[YES] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	PressedButtons[NO] = loadSurface("No2.bmp");
	if (PressedButtons[NO] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	Texture[EMPTY] = loadSurface("empty.bmp");
	if (Texture[EMPTY] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	Texture[WALL] = loadSurface("wall.bmp");
	if (Texture[WALL] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	Texture[FLOOR] = loadSurface("floor.bmp");
	if (Texture[FLOOR] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	Texture[CAT] = loadSurface("mainCat.bmp");
	if (Texture[CAT] == NULL)
	{
		printf("Failed to load up images!\n");
		success = false;
	}
	Texture[BACKGROUND] = loadSurface("Background.bmp");
	if (Texture[BACKGROUND] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}

	return success;
}
void close()
{
	//После уничтожения окна не забудь указатели указать на NULL
	//Освободить поверхность
	Mix_FreeMusic(music);
	music = NULL;
	for (int i = 0; i < CountOfLogos; ++i)
	{
		SDL_FreeSurface(Logos[i]);
		Logos[i] = NULL;
	}
	//Уничтожить окно
	SDL_DestroyWindow(Window);
	Window = NULL;
	//Выйим из подсистемы SDL
	//SDL_Quit();
	for (int i = 0; i < CountOfLogos; ++i)
	{
		SDL_FreeSurface(Logos[i]);
		Logos[i] = NULL;
	}
	SDL_DestroyWindow(Window);
	Window = NULL;
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




