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
bool stop_timer = false;

//class Field
//{
//public:
//	vector<vector<int>> level;
//	vector<vector<int>> catAndGift;
//	int height = 0;
//	int width = 0;
//	int count_place = 0;
//	
//};
class Surf
{
private:
	SDL_Surface* CurrentSurface;
	SDL_Window* Window;
	SDL_Surface* ScreenSurface;
	SDL_Surface* Wallps[CountOfWallps];
	SDL_Surface* Buttons[CountOfButtons];
	SDL_Surface* PressedButtons[CountOfPressedButtons];
	SDL_Surface* Texture[CountOfTexture];
	SDL_Surface* WindowsHowToPlay[CountOfWindows];
	SDL_Surface* Numbers[CountOfNumbers];
	SDL_Surface* WindowLevel[CountOfLeveles];
	SDL_Surface* Comic[CountOfComic];
	Mix_Music* music1;
	Mix_Music* music2;
	Mix_Chunk* box;
	Mix_Chunk* button;
	Mix_Chunk* win;
	Mix_Chunk* intro;
public:
	PlayField infOfFild;
	SDL_Event e;

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
	void init()
	{
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		Window = SDL_CreateWindow(" Sokoban",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (Window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			ScreenSurface = SDL_GetWindowSurface(Window);
		}
		loadMedia();
	}
	void loadHowToPlay()
	{
		WindowsHowToPlay[FIRST] = loadSurface("how_to_play\\1.bmp");
		WindowsHowToPlay[SECOND] = loadSurface("how_to_play\\2.bmp");
		WindowsHowToPlay[THIRD] = loadSurface("how_to_play\\3.bmp");
		WindowsHowToPlay[FOURTH] = loadSurface("how_to_play\\4.bmp");
		WindowsHowToPlay[FIFTH] = loadSurface("how_to_play\\5.bmp");
		WindowsHowToPlay[SIXTH] = loadSurface("how_to_play\\6.bmp");
	}
	void loadTextures()
	{
		Texture[EMPTY] = loadSurface("textures\\empty.bmp");
		Texture[WALL] = loadSurface("textures\\wall.bmp");
		Texture[FLOOR] = loadSurface("textures\\floor.bmp");
		Texture[CAT] = loadSurface("textures\\mainCat.bmp");
		Texture[PRESENT] = loadSurface("textures\\PresentBox.bmp");
		Texture[PLACEHERE] = loadSurface("textures\\PlaceHere.bmp");
		Texture[BACKGROUND] = loadSurface("textures\\Background.bmp");
		Texture[BOX_IN_PLACEHERE] = loadSurface("textures\\BoxInPlaceHere.bmp");
	}
	void loadExit()
	{
		Wallps[MENU_EXIT] = loadSurface("Wallps\\MenuExit.bmp");
		PressedButtons[YES] = loadSurface("pressed_buttons\\Yes2.bmp");
		PressedButtons[NO] = loadSurface("pressed_buttons\\No2.bmp");
		Buttons[YES] = loadSurface("buttons\\Yes1.bmp");
		Buttons[NO] = loadSurface("buttons\\No1.bmp");
	}
	void loadComics()
	{
		Comic[0] = loadSurface("comic\\1.bmp");
		Comic[1] = loadSurface("comic\\2.bmp");
		Comic[2] = loadSurface("comic\\3.bmp");
		Comic[3] = loadSurface("comic\\4.bmp");
	}
	void loadNumbers() {
		Numbers[0] = loadSurface("numbers\\0 number.bmp");
		Numbers[1] = loadSurface("numbers\\1 number.bmp");
		Numbers[2] = loadSurface("numbers\\2 number.bmp");
		Numbers[3] = loadSurface("numbers\\3 number.bmp");
		Numbers[4] = loadSurface("numbers\\4 number.bmp");
		Numbers[5] = loadSurface("numbers\\5 number.bmp");
		Numbers[6] = loadSurface("numbers\\6 number.bmp");
		Numbers[7] = loadSurface("numbers\\7 number.bmp");
		Numbers[8] = loadSurface("numbers\\8 number.bmp");
		Numbers[9] = loadSurface("numbers\\9 number.bmp");
		Numbers[10] = loadSurface("numbers\\colon.bmp");
		Numbers[11] = loadSurface("numbers\\slash.bmp");

	}
	void freeAfterNumbers() {
		for (int i = 0; i < CountOfNumbers; ++i)
		{
			SDL_FreeSurface(Numbers[i]);
			Texture[i] = NULL;
		}
	}
	void freeAfterExit()
	{
		SDL_FreeSurface(Wallps[MENU_EXIT]);
		SDL_FreeSurface(PressedButtons[YES]);
		SDL_FreeSurface(PressedButtons[NO]);
		SDL_FreeSurface(Buttons[YES]);
		SDL_FreeSurface(Buttons[NO]);
	}
	void freeAfterTextures()
	{
		for (int i = 0; i < CountOfTexture; ++i)
		{
			SDL_FreeSurface(Texture[i]);
			Texture[i] = NULL;
		}
	}
	bool loadMedia()
	{
		bool success = true;

		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		music1 = Mix_LoadMUS("sound\\menu.wav");
		music2 = Mix_LoadMUS("sound\\game.wav");
		if (music1 == NULL)
		{
			printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}
		if (music2 == NULL)
		{
			printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}
		button = Mix_LoadWAV("sound\\button.wav");
		box = Mix_LoadWAV("sound\\box.wav");
		intro = Mix_LoadWAV("sound\\intro.wav");
		//Если что-то пошло не так
		if ((button == NULL) || (box == NULL))
		{
			return false;
		}
		button = Mix_LoadWAV("sound\\button.wav");
		box = Mix_LoadWAV("sound\\box.wav");
		intro = Mix_LoadWAV("sound\\intro.wav");
		//Если что-то пошло не так
		if ((button == NULL) || (box == NULL))
		{
			return false;
		}
		Wallps[0] = loadSurface("Wallps\\teamLogo.bmp");
		Wallps[1] = loadSurface("Wallps\\gameLogo.bmp");
		Wallps[2] = loadSurface("Wallps\\MainMenu.bmp");
		/*Wallps[MENU_EXIT] = loadSurface("Wallps\\MenuExit.bmp");*/
		Wallps[WIN_WALP] = loadSurface("Wallps\\Win.bmp");
		Wallps[LOSE] = loadSurface("Wallps\\Lose.bmp");
		Wallps[BLACK] = loadSurface("comic\\0.bmp");
		Wallps[BACKGROUND_TIME] = loadSurface("textures\\BackgroundTime.bmp");

		Buttons[0] = loadSurface("buttons\\PlayGame1.bmp");
		Buttons[1] = loadSurface("buttons\\HowToPlay1.bmp");
		Buttons[2] = loadSurface("buttons\\Exit1.bmp");
		/*Buttons[YES] = loadSurface("buttons\\Yes1.bmp");
		Buttons[NO] = loadSurface("buttons\\No1.bmp");*/
		Buttons[NEXT] = loadSurface("buttons\\Next1.bmp");
		Buttons[BACK] = loadSurface("buttons\\Back1.bmp");
		Buttons[RETRY] = loadSurface("buttons\\Retry.bmp");
		PressedButtons[0] = loadSurface("pressed_buttons\\PlayGame2.bmp");
		PressedButtons[1] = loadSurface("pressed_buttons\\HowToPlay2.bmp");
		PressedButtons[2] = loadSurface("pressed_buttons\\Exit2.bmp");
		/*PressedButtons[YES] = loadSurface("pressed_buttons\\Yes2.bmp");
		PressedButtons[NO] = loadSurface("pressed_buttons\\No2.bmp");*/
		PressedButtons[NEXT] = loadSurface("pressed_buttons\\Next2.bmp");
		PressedButtons[BACK] = loadSurface("pressed_buttons\\Back2.bmp");
		PressedButtons[RETRY] = loadSurface("pressed_buttons\\Retry.bmp");
		/*for (int i = 0; i < CountOfButtons; i++)
		{
			if ( Buttons[i] == NULL ||  PressedButtons[i] == NULL) {
				printf("Failed to load up button!\n");
				success = false;
			}
		}*/
		/* Texture[EMPTY] = loadSurface("textures\\empty.bmp");
		 Texture[WALL] = loadSurface("textures\\wall.bmp");
		 Texture[FLOOR] = loadSurface("textures\\floor.bmp");
		 Texture[CAT] = loadSurface("textures\\mainCat.bmp");
		 Texture[PRESENT] = loadSurface("textures\\PresentBox.bmp");
		 Texture[PLACEHERE] = loadSurface("textures\\PlaceHere.bmp");
		 Texture[BACKGROUND] = loadSurface("textures\\Background.bmp");
		 Texture[BOX_IN_PLACEHERE] = loadSurface("textures\\BoxInPlaceHere.bmp");*/
		 // Texture[BACKGROUND_TIME] = loadSurface("textures\\BackgroundTime.bmp");

		  /*WindowsHowToPlay[FIRST] = loadSurface("how_to_play\\1.bmp");
		  WindowsHowToPlay[SECOND] = loadSurface("how_to_play\\2.bmp");
		  WindowsHowToPlay[THIRD] = loadSurface("how_to_play\\3.bmp");
		  WindowsHowToPlay[FOURTH] = loadSurface("how_to_play\\4.bmp");
		  WindowsHowToPlay[FIFTH] = loadSurface("how_to_play\\5.bmp");
		  WindowsHowToPlay[SIXTH] = loadSurface("how_to_play\\6.bmp");*/

		  /*Numbers[0] = loadSurface("numbers\\0 number.bmp");
		  Numbers[1] = loadSurface("numbers\\1 number.bmp");
		  Numbers[2] = loadSurface("numbers\\2 number.bmp");
		  Numbers[3] = loadSurface("numbers\\3 number.bmp");
		  Numbers[4] = loadSurface("numbers\\4 number.bmp");
		  Numbers[5] = loadSurface("numbers\\5 number.bmp");
		  Numbers[6] = loadSurface("numbers\\6 number.bmp");
		  Numbers[7] = loadSurface("numbers\\7 number.bmp");
		  Numbers[8] = loadSurface("numbers\\8 number.bmp");
		  Numbers[9] = loadSurface("numbers\\9 number.bmp");
		  Numbers[10] = loadSurface("numbers\\colon.bmp");
		  Numbers[11] = loadSurface("numbers\\slash.bmp");*/

		WindowLevel[0] = loadSurface("windowlevel\\1.bmp");
		WindowLevel[1] = loadSurface("windowlevel\\2.bmp");
		WindowLevel[2] = loadSurface("windowlevel\\3.bmp");
		WindowLevel[3] = loadSurface("windowlevel\\4.bmp");
		WindowLevel[4] = loadSurface("windowlevel\\5.bmp");

		// Comic[0] = loadSurface("comic\\0.bmp");
		Comic[0] = loadSurface("comic\\1.bmp");
		Comic[1] = loadSurface("comic\\2.bmp");
		Comic[2] = loadSurface("comic\\3.bmp");
		Comic[3] = loadSurface("comic\\4.bmp");

		/*for (int i = 0; i < CountOfComic; i++)
		{
			if (Comic[i] == NULL)
			{
				printf("Failed to load up comic!\n");
				success = false;
			}
		}*/
		for (int i = 0; i < CountOfLeveles; i++)
		{
			if (WindowLevel[i] == NULL)
			{
				printf("Failed to load up image!\n");
				success = false;
			}
		}
		/*	for (int i = 0; i < 12; i++)
			{
				if (Numbers[i] == NULL)
				{
					printf("Failed to load up image!\n");
					success = false;
				}
			}*/
			/*for (int i = 0; i < CountOdArrs::CountOfTexture; i++)
			{
				if ( Texture[i] == NULL)
				{
					printf("Failed to load up image!\n");
					success = false;
				}
			}*/

		return success;
	}

	void playIntro(int channel, int num)
	{
		playChunk(channel, num, intro);
	}
	void playButton(int channel, int num)
	{
		playChunk(channel, num, button);
	}
	void playChunk(int channel, int num, Mix_Chunk* chunk)
	{
		Mix_PlayChannel(channel, chunk, num);
	}
	void playMusicInMenu(int channel, unsigned int ms)
	{
		playMusic(channel, ms, music1);
	}
	void playMusic(int channel, unsigned int ms, Mix_Music* mus)
	{
		Mix_FadeInMusic(mus, channel, ms);
	}
	void showPic(SDL_Surface* CurrentSurface, SDL_Rect coord)
	{
		SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &coord);
		SDL_UpdateWindowSurface(Window);
	}
	void showPicWallp(SDL_Surface* CurrentSurface)
	{
		SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, NULL);
		SDL_UpdateWindowSurface(Window);
	}
	void showComics()
	{
		SDL_Rect coord_for_wallp;
		coord_for_wallp.x = 100;
		coord_for_wallp.y = 0;
		showPicWallp(Wallps[BLACK]);
		SDL_Delay(1000);
		while (!Mix_FadeOutMusic(2000) && Mix_PlayingMusic()) {
			// wait for any fades to complete
			SDL_Delay(40);
		}
		if (Mix_FadeInMusic(music2, -1, 2000) == -1) {
			printf("Mix_FadeInMusic: %s\n", Mix_GetError());

		}
		for (int number_of_comic = FIRST; number_of_comic < CountOdArrs::CountOfComic;)
		{
			for (int i = 0; i < 2; i++)
			{
				//showPic(game, coord_for_wallp, COMIC, number_of_comic);
				showPic(Comic[number_of_comic], coord_for_wallp);
				SDL_Delay(1000);
				coord_for_wallp.x += 300;
				number_of_comic++;
			}
			coord_for_wallp.x = 100;
			coord_for_wallp.y += 300;
		}
	}
	void ShowOneWindowHowToPlay(unsigned int what_kind_of_pic)
	{
		//CurrentSurface = WindowsHowToPlay[what_kind_of_pic];
		showPicWallp(WindowsHowToPlay[what_kind_of_pic]);
	}
	bool showWindowHowToPlay(int number_of_current_window)
	{
		if (number_of_current_window < 0 || number_of_current_window >= CountOfWindows)return false;
		for (int number_of_window = 0; number_of_window < CountOdArrs::CountOfWindows; number_of_window++)
		{
			if (number_of_current_window == number_of_window)
			{
				ShowOneWindowHowToPlay(number_of_current_window);
				return true;
			}
		}
		return false;
	}
	void freeAfterHowToPlay()
	{
		for (int i = 0; i < CountOfWindows; ++i)
		{
			SDL_FreeSurface(WindowsHowToPlay[i]);
			WindowsHowToPlay[i] = NULL;
		}
	}





	//Getter
	SDL_Surface* GetNumber(int what)
	{
		return Numbers[what];
	}
	SDL_Surface* GetWallp(int what)
	{
		return Wallps[what];
	}
	SDL_Surface* GetPressedButton(int what)
	{
		return PressedButtons[what];
	}
	SDL_Surface* GetButton(int what)
	{
		return Buttons[what];
	}
	SDL_Surface* GetWindowLevel(int what)
	{
		return WindowLevel[what];
	}
	SDL_Surface* GetWindowHowToPlay(int what)
	{
		return WindowsHowToPlay[what];
	}
	SDL_Surface* GetComic(int what)
	{
		return Comic[what];
	}
	SDL_Surface* GetTexture(int what)
	{
		return Texture[what];
	}
};
//class TextureNas : public Surf
//{
//
//	SDL_Surface* PicTexture;
//public:
//	SDL_Rect posTexture;
//	int X;
//	int Y;
//	int size_texture;
//	TextureNas() :TextureNas("textures\\empty.bmp")
//	{
//
//	}
//	TextureNas(string path) :TextureNas(path, 0, 0)
//	{
//
//	}
//	TextureNas(string path, int X, int Y)
//	{
//		this->X = X;
//		this->Y = Y;
//		SetPicTexture(path);
//		size_texture = 50;
//		posTexture.x = 0;
//		posTexture.y = 0;
//	}
//	void SetPosTextureY(unsigned int y)
//	{
//		posTexture.y = y;
//	}
//	void SetPosTextureX(unsigned int x)
//	{
//		posTexture.x = x;
//	}
//	void SetX(unsigned int X)
//	{
//		this->X = X;
//	}
//	void SetY(unsigned int Y)
//	{
//		this->Y = Y;
//	}
//	int GetX()
//	{
//		return X;
//	}
//	int GetY()
//	{
//		return Y;
//	}
//	SDL_Surface* GetPicTexture()
//	{
//		return PicTexture;
//	}
//	SDL_Rect GetPosTexture()
//	{
//		return posTexture;
//	}
//	int GetPosTextureY()
//	{
//		return posTexture.y;
//	}
//	int GetPosTextureX()
//	{
//		return posTexture.x;
//	}
//	int Getsize_texture()
//	{
//		return size_texture;
//	}
//	void SetPicTexture(string path)
//	{
//		PicTexture = loadSurface(path);
//	}
//	void movementLeftCat()
//	{
//		X--;
//		posTexture.x -= size_texture;
//	}
//	void movementRightCat()
//	{
//		Y++;
//		posTexture.y += size_texture;
//	}
//	void movementUpCat()
//	{
//		Y--;
//		posTexture.y -= size_texture;
//	}
//	void movementDownCat()
//	{
//		X++;
//		posTexture.x += size_texture;
//	}
//	void movementLeftBox(TextureNas copy_texture)
//	{
//		posTexture.y = copy_texture.posTexture.y;
//		posTexture.x = copy_texture.posTexture.x - copy_texture.size_texture;
//		Y = copy_texture.Y;
//		X = copy_texture.X - 1;
//	}
//	void movementRightBox(TextureNas copy_texture)
//	{
//		posTexture.y = copy_texture.posTexture.y;
//		posTexture.x = copy_texture.posTexture.x + copy_texture.size_texture;
//		Y = copy_texture.Y;
//		X = copy_texture.X + 1;
//	}
//
//};
class Counter {
	int size;
	int count_step;
	int last_number;
	int max_number;
	SDL_Rect texture_of_number;
	//Surf* number;
	void increase() {
		count_step++;
	}
	void decrease() {
		count_step--;
	}

public:
	Counter() : Counter(300) {

	}
	Counter(int max_number) {
		size = 20;
		count_step = 0;
		last_number = 0;
		texture_of_number.y = 35;
		this->max_number = max_number;
	}

	void printAll(Surf& game) {
		texture_of_number.x = size * 7;
		int c = max_number;
		for (int i = 0; i < 3; i++)
		{
			//int c = last_number;
			last_number = c % 10;//
			c /= 10;
			//owPic(game, texture_of_number, NUMBERS, last_number);
			game.showPic(game.GetNumber(last_number), texture_of_number);
			texture_of_number.x -= size;
		}
		texture_of_number.x = size * 4;
		//showPic(game, texture_of_number, NUMBERS, 11);
		game.showPic(game.GetNumber(11), texture_of_number);

		texture_of_number.x = size * 3;
		c = count_step;
		for (int i = 0; i < 3; i++) {
			last_number = c % 10;
			c /= 10;
			//showPic(game, texture_of_number, NUMBERS, last_number);
			game.showPic(game.GetNumber(last_number), texture_of_number);
			texture_of_number.x -= size;
		}
	}
	void printCount(Surf& game, bool what) {
		if (what)increase();
		else decrease();

		if (what && count_step % 10 == 0 || !what && count_step % 10 == 9)
		{
			last_number = count_step / 10 % 10;
			texture_of_number.x = size * 2;
			//showPic(game, texture_of_number, NUMBERS, last_number);
			game.showPic(game.GetNumber(last_number), texture_of_number);
		}
		if (what && (count_step / 10) % 10 == 0 || !what && (count_step / 10) % 10 == 9)
		{
			last_number = count_step / 100;
			texture_of_number.x = size;
			//showPic(game, texture_of_number, NUMBERS, last_number);
			game.showPic(game.GetNumber(last_number), texture_of_number);
		}
		last_number = count_step % 10;
		texture_of_number.x = size * 3;
		//showPic(game, texture_of_number, NUMBERS, last_number);
		game.showPic(game.GetNumber(last_number), texture_of_number);
	}

	void SetCountStep(int count) {
		count_step = count;
	}
	int GetCountStep() {
		return count_step;
	}
};

class Timer {
	int size;
	int min;//минуты
	int sec;
	int count_of_sec = 0;
	int x = 0, y = 0, z = 0, w = 0; //изменение определенных цифр во времени
	SDL_Rect texture_of_number;
public:
	Timer() : Timer(40) {
		
	}
	Timer(int count_of_sec) {
		this->count_of_sec = count_of_sec;
		size = 20;
		min = 0;
		texture_of_number.y = 35;
		sec = this->count_of_sec;
	}
	void Converter() {
		while (sec > 60)
		{
			min++;
			sec -= 60;
		}
	}
	void PrintAll(Surf game){
		x = sec % 10;
		texture_of_number.x = SCREEN_WIDTH - size * 2;
		//showPic(game, texture_of_number, NUMBERS, x);
		game.showPic(game.GetNumber(x), texture_of_number);

		y = (sec / 10);
		texture_of_number.x -= size;
		//showPic(game, texture_of_number, NUMBERS, y);
		game.showPic(game.GetNumber(y), texture_of_number);

		texture_of_number.x -= size;
		//showPic(game, texture_of_number, NUMBERS, 10);
		game.showPic(game.GetNumber(10), texture_of_number);

		z = min % 10;
		texture_of_number.x -= size;
		//showPic(game, texture_of_number, NUMBERS, z);
		game.showPic(game.GetNumber(z), texture_of_number);

		w = (min / 10);
		texture_of_number.x -= size;
		//showPic(game, texture_of_number, NUMBERS, w);
		game.showPic(game.GetNumber(w), texture_of_number);

	}
	void timeGo(Surf& game) {
		Converter();
		PrintAll(game);
		while (!stop_timer)
		{
			if (sec == 0) {
				if (min - 1 >= 0) {
					min--;
					sec = 60;
					z = min % 10;
					texture_of_number.x = SCREEN_WIDTH - size * 5;
					//showPic(game, texture_of_number, NUMBERS, z);
					game.showPic(game.GetNumber(z), texture_of_number);
					if ((min / 10) - 1 >= 0) {
						w = (min / 10);
						texture_of_number.x = SCREEN_WIDTH - size * 6;
						//showPic(game, texture_of_number, NUMBERS, w);
						game.showPic(game.GetNumber(w), texture_of_number);

					}
				}
			}
			sec--;
			if (x == 0) {
				y = (sec / 10) % 10;
				texture_of_number.x = SCREEN_WIDTH - size * 3;
				//showPic(game, texture_of_number, NUMBERS, y);
				game.showPic(game.GetNumber(y), texture_of_number);
			}
			x = sec % 10;
			texture_of_number.x = SCREEN_WIDTH - size * 2;
			//showPic(game, texture_of_number, NUMBERS, x);
			game.showPic(game.GetNumber(x), texture_of_number);
			count_of_sec--;
			if (min == 0 && sec == 0) {
				stop_timer = true;
				return;
			}

			this_thread::sleep_for(chrono::milliseconds(1000));
		}
	}
	

	int GetCountSec() {
		return count_of_sec;
	}
	void SetCountSec(unsigned int digit) {
		
		count_of_sec = digit;
	}

};

void intro(Surf& game);
void menu(Surf& game, bool& quit, int i, int& i_for_buttons, int& current_pressed_button);
void howToPlay(Surf& game, bool quit, int count = 0);
void playGame(Surf& game, bool& quit, fstream& file, fstream& fileCat);
void exit(bool& quit, Surf& game);
void createMap(Surf& game, vector<vector<int>>& array, fstream& file, bool new_level);
void field(Surf& game, vector<vector<int>> array, fstream& file, SDL_Rect posTexture);//
bool characterMovement(Surf& game, Counter& counter, fstream& file, fstream& fileCat, bool& quit, bool new_level);
//void showTexture(int i, SDL_Rect posTexture, Surface& game);
//void howToPlay(Surface& game, bool quit, int count = 0);
//bool win(Surface& game, vector<vector<int>> copy_catAndGift);
//void characterMovement(Surface& game, fstream& file, fstream& fileCat, bool& quit);
//void showButton(Surface& game, int i, SDL_Rect stretchRectб, int y_of_button1 = 250, int y_of_button2 = 250 + 70, int y_of_button3 = 250 + 140);
//void backgroundMenu(Surface& game);
//bool init(Surface& game);
//bool loadMedia(Surface& game);
//void close(Surface& game);
bool isPressed(int keyCode);
bool isReleased(int keyCode);

int playingLevel(Surf& game, Counter& counter, fstream& file, vector<vector<int>> catAndGift, vector < Texture> texture_of_elements, bool& quit, Timer& timer, bool first = false);
//void countOfStep(Surf& game, bool what, bool zero = false);
void retry(Surf& game, bool& quit);

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

//void showPic(Surface& game, SDL_Rect coord, int what_kind_of_arr, int what_kind_of_pic)
//{
//	switch (what_kind_of_arr)
//	{
//	case WALLPS:
//		game.CurrentSurface = game.Wallps[what_kind_of_pic];
//		break;
//	case BUTTONS:
//		game.CurrentSurface = game.Buttons[what_kind_of_pic];
//		break;
//	case PRESSED_BUTTONS:
//		game.CurrentSurface = game.PressedButtons[what_kind_of_pic];
//		break;
//	case TEXTURES:
//		game.CurrentSurface = game.Texture[what_kind_of_pic];
//		break;
//	case WINDOWS:
//		game.CurrentSurface = game.WindowsHowToPlay[what_kind_of_pic];
//		break;
//	case NUMBERS:
//		game.CurrentSurface = game.Numbers[what_kind_of_pic];
//		break;
//	case LEVELES:
//		game.CurrentSurface = game.WindowLevel[what_kind_of_pic];
//		break;
//	case COMIC:
//		game.CurrentSurface = game.Comic[what_kind_of_pic];
//		break;
//	}
//	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &coord);
//	SDL_UpdateWindowSurface(game.Window);
//}
//void inisialitCoordOfWallp(SDL_Rect& coord)
//{
//	coord.x = 0;
//	coord.y = 0;
//}
void intro(Surf& game)
{
	game.init();
	game.playIntro(4, 0);
	bool quit = false;
	int i = 0;
	int i_for_buttons = 0;
	int current_pressed_button = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&(game.e)) != 0)
		{
			if (game.e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
			else if (i < 2)
			{
				SDL_Rect coord_for_wallp;
				game.showPicWallp(game.GetWallp(i));
				SDL_Delay(1500);
				i++;
			}
			if (i == 2)
			{
				menu(game, quit, i, i_for_buttons, current_pressed_button);
			}
		}
	}


}
//void backgroundMenu(Surface& game)
//{
//	game.CurrentSurface = game.Wallps[2];
//	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
//	SDL_UpdateWindowSurface(game.Window);
//}
void menu(Surf& game, bool& quit, int i, int& i_for_buttons, int& current_pressed_button)
{
	game.playMusicInMenu(-1, 3000);
	fstream file("fields.TXT");
	fstream fileCat("position.TXT");
	SDL_Rect coords_button;
	coords_button.x = 270;
	coords_button.y = 250;
	int current_y = 250;
	int y_of_button1 = 250;
	int y_of_button2 = y_of_button1 + 70;
	int y_of_button3 = y_of_button2 + 70;
	int interval_Y = 70;

	game.showPicWallp(game.GetWallp(MAIN_MENU));
	game.showPic(game.GetPressedButton(GAME), coords_button);
	coords_button.y += interval_Y;
	i_for_buttons++;

	for (; i_for_buttons < 3; i_for_buttons)
	{
		game.showPic(game.GetButton(i_for_buttons), coords_button);
		coords_button.y += interval_Y;
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
						{
							coords_button.y = y_of_button2;
							game.showPic(game.GetButton(HOW_TO_PLAY), coords_button);
						}

						else if (current_pressed_button == HOW_TO_PLAY)
						{
							coords_button.y = y_of_button3;
							game.showPic(game.GetButton(EXIT), coords_button);
						}

						current_y -= interval_Y;
						coords_button.y = current_y;

						game.showPic(game.GetPressedButton(current_pressed_button), coords_button);
					}
					break;
				case SDLK_DOWN:
					if (current_pressed_button < 2)
					{
						current_pressed_button++;
						if (current_pressed_button == EXIT)
						{
							coords_button.y = y_of_button2;
							game.showPic(game.GetButton(HOW_TO_PLAY), coords_button);
						}

						else if (current_pressed_button == HOW_TO_PLAY)
						{
							coords_button.y = y_of_button1;
							game.showPic(game.GetButton(GAME), coords_button);
						}

						current_y += interval_Y;
						coords_button.y = current_y;
						game.showPic(game.GetPressedButton(current_pressed_button), coords_button);
					}
					break;
				case SDLK_ESCAPE:
					exit(quit, game);
					game.showPicWallp(game.GetWallp(MAIN_MENU));
					if (current_pressed_button == GAME)
					{
						coords_button.y = y_of_button2;
						game.showPic(game.GetButton(HOW_TO_PLAY), coords_button);
						coords_button.y = y_of_button3;
						game.showPic(game.GetButton(EXIT), coords_button);
						coords_button.y = y_of_button1;
					}
					else if (current_pressed_button == HOW_TO_PLAY)
					{
						coords_button.y = y_of_button1;
						game.showPic(game.GetButton(GAME), coords_button);
						coords_button.y = y_of_button3;
						game.showPic(game.GetButton(EXIT), coords_button);
						coords_button.y = y_of_button2;
					}
					else
					{
						coords_button.y = y_of_button1;
						game.showPic(game.GetButton(GAME), coords_button);
						coords_button.y = y_of_button2;
						game.showPic(game.GetButton(HOW_TO_PLAY), coords_button);
						coords_button.y = y_of_button3;
					}
					game.showPic(game.GetPressedButton(current_pressed_button), coords_button);
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
					switch (current_pressed_button)
					{
					case GAME:
						game.playButton(3, 0);
						playGame(game, quit, file, fileCat);
						game.showPicWallp(game.GetWallp(MAIN_MENU));
						coords_button.y = y_of_button2;
						game.showPic(game.GetButton(HOW_TO_PLAY), coords_button);
						coords_button.y = y_of_button3;
						game.showPic(game.GetButton(EXIT), coords_button);
						coords_button.y = y_of_button1;
						break;
					case HOW_TO_PLAY:
						game.playButton(3, 0);

						coords_button.y = y_of_button2;
						game.showPicWallp(game.GetWallp(MAIN_MENU));
						coords_button.y = y_of_button1;
						game.showPic(game.GetButton(GAME), coords_button);
						coords_button.y = y_of_button3;
						game.showPic(game.GetButton(EXIT), coords_button);
						coords_button.y = y_of_button2;
						break;
					case EXIT:
						game.playButton(3, 0);
						exit(quit, game);
						game.showPicWallp(game.GetWallp(MAIN_MENU));
						coords_button.y = y_of_button1;
						game.showPic(game.GetButton(GAME), coords_button);
						coords_button.y = y_of_button2;
						game.showPic(game.GetButton(HOW_TO_PLAY), coords_button);
						coords_button.y = y_of_button3;
						break;
					}
					game.showPic(game.GetPressedButton(current_pressed_button), coords_button);
					break;
				default:
					break;
				}
			}
		}
	}
}
//bool showWindowHowToPlay(Surface& game, int number_of_current_window)
//{
//	SDL_Rect coords;
//	inisialitCoordOfWallp(coords);
//	if (number_of_current_window < 0 || number_of_current_window >= CountOfWindows)return false;
//	for (int number_of_window = 0; number_of_window < CountOdArrs::CountOfWindows; number_of_window++)
//	{
//		if (number_of_current_window == number_of_window)
//		{
//			showPic(game, coords, WINDOWS, number_of_window);
//			return true;
//		}
//	}
//}
void exit(bool& quit, Surf& game)
{
	game.loadExit();
	bool quit2 = false;
	SDL_Rect stretchRect;
	//stretchRect.x = 0;
	//stretchRect.y = 0;
	//showPic(game, stretchRect, WALLPS, MENU_EXIT);
	game.showPicWallp(game.GetWallp(MENU_EXIT));
	//game.showWallp(MENU_EXIT);
	stretchRect.x = 160;
	stretchRect.y = 370;
	int i = 3;
	int a = 0;
	int current_pressed_button = i;

	//showPic(game, stretchRect, PRESSED_BUTTONS, YES);
	game.showPic(game.GetPressedButton(YES), stretchRect);
	stretchRect.x += 300;
	i++;
	//showPic(game, stretchRect, BUTTONS, NO);
	game.showPic(game.GetButton(NO), stretchRect);
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
						//showPic(game, stretchRect, PRESSED_BUTTONS, NO);
						game.showPic(game.GetPressedButton(NO), stretchRect);
						stretchRect.x -= 300;
						/*showPic(game, stretchRect, BUTTONS, YES);*/
						game.showPic(game.GetButton(YES), stretchRect);
						current_pressed_button++;
					}
					break;
				case SDLK_LEFT:
					if (current_pressed_button == NO)
					{
						//showPic(game, stretchRect, PRESSED_BUTTONS, YES);
						game.showPic(game.GetPressedButton(YES), stretchRect);
						stretchRect.x += 300;
						//showPic(game, stretchRect, BUTTONS, NO);
						game.showPic(game.GetButton(NO), stretchRect);
						current_pressed_button--;
					}
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
					//Mix_PlayChannel(-1, game.button, 0) == -1;
					game.playButton(-1, 0);
					game.freeAfterExit();
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
void howToPlay(Surf& game, bool quit, int count)
{
	game.loadHowToPlay();
	SDL_Rect stretchRect;
	/*SDL_Rect coord_for_wallp;
	coord_for_wallp.x = 0;
	coord_for_wallp.y = 0;*/
	stretchRect.x = 170;
	stretchRect.y = 450;

	//showPic(game, coord_for_wallp, WINDOWS, FIRST);
	game.ShowOneWindowHowToPlay(FIRST);
	//showPic(game, stretchRect, BUTTONS, BACK);
	game.showPic(game.GetButton(BACK), stretchRect);
	stretchRect.x += 420;
	game.showPic(game.GetButton(NEXT), stretchRect);
	//showPic(game, stretchRect, BUTTONS, NEXT);
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
				//Mix_PlayChannel(-1, game.button, 0) == -1;
				switch (game.e.key.keysym.sym)
				{
				case SDLK_RIGHT:
					count++;
					//showPic(game, stretchRect, PRESSED_BUTTONS, NEXT);
					game.showPic(game.GetPressedButton(NEXT), stretchRect);
					SDL_Delay(200);
					if (!(game.showWindowHowToPlay(count)))
					{
						game.freeAfterHowToPlay();
						return;
					}
					break;
				case SDLK_LEFT:
					count--;
					stretchRect.x = 170;
					//showPic(game, stretchRect, PRESSED_BUTTONS, BACK);
					game.showPic(game.GetPressedButton(BACK), stretchRect);
					SDL_Delay(200);
					if (!(game.showWindowHowToPlay(count)))
					{
						game.freeAfterHowToPlay();
						return;
					}
					break;
				}
				stretchRect.x = 170;
				//showPic(game, stretchRect, BUTTONS, BACK);
				game.showPic(game.GetButton(BACK), stretchRect);
				stretchRect.x += 420;
				//showPic(game, stretchRect, BUTTONS, NEXT);
				game.showPic(game.GetButton(NEXT), stretchRect);
			}
			if (quit == true)break;
		}
	}
}
//void showComic(Surface& game)
//{
//	SDL_Rect coord_for_wallp;
//	inisialitCoordOfWallp(coord_for_wallp);
//	showPic(game, coord_for_wallp, COMIC, FIRST);
//	SDL_Delay(1000);
//	coord_for_wallp.x = 100;
//	coord_for_wallp.y = 0;
//	while (!Mix_FadeOutMusic(2000) && Mix_PlayingMusic())
//	{
//		// wait for any fades to complete
//		SDL_Delay(40);
//	}
//
//
//	if (Mix_FadeInMusic(game.music2, -1, 2000) == -1) 
//	{
//		printf("Mix_FadeInMusic: %s\n", Mix_GetError());
//
//	}
//	for (int number_of_comic = SECOND; number_of_comic < CountOdArrs::CountOfComic;)
//	{
//		for (int i = 0; i < 2; i++)
//		{
//			showPic(game, coord_for_wallp, COMIC, number_of_comic);
//			SDL_Delay(50);
//			coord_for_wallp.x += 300;
//			number_of_comic++;
//		}
//		coord_for_wallp.x = 100;
//		coord_for_wallp.y += 300;
//	}
//
//}

//void timer(Surface& game, int &count_of_sec) {
//	int size = 20;
//	//int count_of_sec = 90;
//	int sec = count_of_sec;
//	int min = 0;
//	while (sec > 60)
//	{
//		min++;
//		sec -= 60;
//	}
//
//	SDL_Rect texture_of_number;
//	texture_of_number.y = 35;
//	int x = 0, y = 0, z = 0, w = 0;//изменение определенных цифр во времени
//
//	x = sec % 10;
//	texture_of_number.x = SCREEN_WIDTH - size * 2;
//	showPic(game, texture_of_number, NUMBERS, x);
//
//	y = (sec / 10);
//	texture_of_number.x -= size;
//	showPic(game, texture_of_number, NUMBERS, y);
//
//	texture_of_number.x -= size;
//	showPic(game, texture_of_number, NUMBERS, 10);
//
//	z = min % 10;
//	texture_of_number.x -= size;
//	showPic(game, texture_of_number, NUMBERS, z);
//
//	w = (min / 10);
//	texture_of_number.x -= size;
//	showPic(game, texture_of_number, NUMBERS, w);
//
//	
//	while (!stop_timer)
//	{
//		if (sec == 0) {
//			if (min - 1 >= 0) {
//				min--;
//				sec = 60;
//				z = min % 10;
//				texture_of_number.x = SCREEN_WIDTH - size * 5;
//				showPic(game, texture_of_number, NUMBERS, z);
//				if ((min / 10) - 1 >= 0) {
//					w = (min / 10);
//					texture_of_number.x = SCREEN_WIDTH - size * 6;
//					showPic(game, texture_of_number, NUMBERS, w);
//				}	
//			}
//		}
//		sec--;
//		if (x == 0) {
//			y = (sec / 10) % 10;
//			texture_of_number.x = SCREEN_WIDTH - size * 3;
//			showPic(game, texture_of_number, NUMBERS, y);
//		}
//		x = sec % 10;
//		texture_of_number.x = SCREEN_WIDTH - size * 2;
//		showPic(game, texture_of_number, NUMBERS, x);
//
//		count_of_sec--;
//		if (min == 0 && sec == 0) {
//			stop_timer = true;
//			return;
//		}
//
//		this_thread::sleep_for(chrono::milliseconds(1000));
//	}
//}
void playGame(Surf& game, bool& quit, fstream& file, fstream& fileCat)
{
	//int** level;
	Counter counter(300);
	vector<vector<int>> level;
	counter.SetCountStep(0);
	int height = 0;
	int width = 0;
	static bool new_level = false;
	static int number_of_level = FIRST;

	if (number_of_level == FIRST)
	{
		game.showComics();
		//showComic(game);
	}
	while (number_of_level < game.infOfFild.GetCountLevels())
	{
		stop_timer = true;

		//showWindowLevel(game, number_of_level);
		game.loadTextures();
		game.loadNumbers();
		game.showPicWallp(game.GetWindowLevel(number_of_level));
		SDL_Delay(1000);
		counter.SetCountStep(0);
		createMap(game, game.infOfFild.level, file, new_level);
		if (characterMovement(game, counter, file, fileCat, quit, new_level) == EXIT_TO_MENU)
		{
			//quit = true;
			game.freeAfterTextures();
			game.freeAfterNumbers();
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
			game.freeAfterTextures();
			game.freeAfterNumbers();
			game.infOfFild.level.clear();
			game.infOfFild.catAndGift.clear();
			//game.infOfFild.level.swap(vector<vector<int>>());
			vector<vector<int>>().swap(game.infOfFild.level);
			vector<vector<int>>().swap(game.infOfFild.catAndGift);
			game.infOfFild.SetCountPlace(0);
			SDL_Delay(1000);
			//SDL_Rect coord;
			//inisialitCoordOfWallp(coord);
			if (game.infOfFild.GetResult() == WIN_WALP)
			{
				number_of_level++;
				new_level = true;
				game.showPicWallp(game.GetWallp(WIN_WALP));
				//showPic(game, coord, WALLPS, WIN_WALP);
				SDL_Delay(1000);
			}
			else if (game.infOfFild.GetResult() == LOSE)
			{

				game.showPicWallp(game.GetWallp(LOSE));
				retry(game, quit);
				new_level = false;

			}

		}
	}
	if (number_of_level == game.infOfFild.GetCountLevels())
	{
		file.seekg(0, ios_base::beg);
		fileCat.seekg(0, ios_base::beg);
		number_of_level = 0;
	}

}
//void showArrInConsole(vector<vector<int>> arr, int width, int hight)
//{
//	for (int i = 0; i < 9; i++)
//	{
//		for (int j = 0; j < 9; j++)
//		{
//			cout << arr[i][j] << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//	cout << endl;
//}
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

void retry(Surf& game, bool& quit) 
{
	bool quit2 = false;
	SDL_Rect stretchRect;
	stretchRect.x = 470;
	stretchRect.y = 388;

	game.showPic(game.GetButton(RETRY), stretchRect);
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
					game.playButton(3, 0);
					stretchRect.y++;
					game.showPic(game.GetPressedButton(RETRY), stretchRect);
					SDL_Delay(200);

					game.showPic(game.GetButton(RETRY), stretchRect);
					SDL_Delay(200);

					quit2 = true;
					break;
				}
				
				
			}
			if (quit2 == true)break;
		}
	}
}

void showFloorOfPlaceHere(Surf& game, vector<vector<int>> level, vector<Texture> struct_of_textures, int texture)
{
	if (level[struct_of_textures[texture].Y][struct_of_textures[texture].X] == PLACEHERE)
		game.showPic(game.GetTexture(PLACEHERE), struct_of_textures[texture].posTexture);
	else
		game.showPic(game.GetTexture(FLOOR), struct_of_textures[texture].posTexture);
}
void showPresent(Surf& game, vector<vector<int>> level, vector<Texture> struct_of_textures, int texture)
{
	if (level[struct_of_textures[texture].Y][struct_of_textures[texture].X] == PLACEHERE)
		game.showPic(game.GetTexture(BOX_IN_PLACEHERE), struct_of_textures[texture].posTexture);
		
	else
		game.showPic(game.GetTexture(PRESENT), struct_of_textures[texture].posTexture);
}
void showAfterRecurs(Surf& game, vector < Texture> copy_texture)
{
	showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, FLOOR);
	game.showPic(game.GetTexture(CAT), copy_texture[CAT].posTexture);
	showPresent(game, game.infOfFild.level, copy_texture, PRESENT);
}
bool win(Surf& game, vector<vector<int>> copy_catAndGift) {
	int count = 0;
	for (int i = 0; i < game.infOfFild.GetHeight(); i++)
	{
		for (int j = 0; j < game.infOfFild.GetWidth(); j++)
		{
			if (game.infOfFild.level[i][j] == PLACEHERE && copy_catAndGift[i][j] == PRESENT)
				count++;
		}
	}
	if (count == game.infOfFild.GetCountPlace()) return 1;
	return 0;

}
int playingLevel(Surf& game, Counter& counter, fstream& file, vector<vector<int>> catAndGift, vector < Texture> texture_of_elements, bool& quit, Timer& timer, bool first)
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
		//showTexture(CAT, copy_texture[CAT].posTexture, game);
		game.showPic(game.GetTexture(CAT), copy_texture[CAT].posTexture);
		copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = CAT;

		if (keydown_for_box != KEY_PRESS_DEFAULT)
		{
			editCoordsMovementOfBox(copy_texture, keydown_for_box);
			keydown_for_box = KEY_PRESS_DEFAULT;
			copy_catAndGift[copy_texture[PRESENT].Y][copy_texture[PRESENT].X] = PRESENT;
			showPresent(game, game.infOfFild.level, copy_texture, PRESENT);
		}

	}

	if (win(game, copy_catAndGift) || timer.GetCountSec() == 0 || counter.GetCountStep() == 300)//getter
	{
		if (win(game, copy_catAndGift)) game.infOfFild.SetResult(WIN_WALP);
		else game.infOfFild.SetResult(LOSE);
		return WIN;
	}

	//showArrInConsole(copy_catAndGift, 9, 9);
	bool flag = false;
	while (!quit)
	{
		while (SDL_PollEvent(&game.e) != 0)
		{

			if (win(game, copy_catAndGift) || timer.GetCountSec() == 0 || counter.GetCountStep() == 300)
			{
				if (win(game, copy_catAndGift)) game.infOfFild.SetResult(WIN_WALP);
				else game.infOfFild.SetResult(LOSE);
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
				//Timer timer;
				thread th(&Timer::timeGo, ref(timer), ref(game));//ref - используется 
				th.detach();
				//SDL_Rect coord;
				//inisialitCoordOfWallp(coord);
				//showPic(game, coord, TEXTURES, BACKGROUND_TIME);
				game.showPicWallp(game.GetWallp(BACKGROUND_TIME));
				field(game, game.infOfFild.level, file, copy_texture[CAT].posTexture);
				field(game, copy_catAndGift, file, copy_texture[CAT].posTexture);
				//maxNumberOfCounter(game);

				counter.printAll(game);
				//countOfStep(game, true, true);



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
							counter.printCount(game, true);
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);

							keydown_for_cat = SDLK_LEFT;

							int result = playingLevel(game, counter, file, copy_catAndGift, copy_texture, quit, timer);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								//showTexture(CAT, copy_texture[CAT].posTexture, game);
								game.showPic(game.GetTexture(CAT), copy_texture[CAT].posTexture);
							}
							else
								return EXIT_TO_MENU;
						}
						else if (copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X - 1] == PRESENT
							&& game.infOfFild.level[copy_texture[CAT].Y][copy_texture[CAT].X - 2] != WALL
							&& copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X - 2] != PRESENT)
						{
							counter.printCount(game, true);
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
							int result = playingLevel(game, counter, file, copy_catAndGift,/* level,*/ copy_texture, quit, timer);
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
							counter.printCount(game, true);
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							keydown_for_cat = SDLK_RIGHT;
							int result = playingLevel(game, counter, file, copy_catAndGift,/* level,*/ copy_texture, quit, timer);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								//showTexture(CAT, copy_texture[CAT].posTexture, game);
								game.showPic(game.GetTexture(CAT), copy_texture[CAT].posTexture);
							}
							else
								return EXIT_TO_MENU;
						}
						else if (copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X + 1] == PRESENT
							&& game.infOfFild.level[copy_texture[CAT].Y][copy_texture[CAT].X + 2] != WALL
							&& copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X + 2] != PRESENT)
						{
							counter.printCount(game, true);

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
							int result = playingLevel(game, counter, file, copy_catAndGift, copy_texture, quit, timer);

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
							counter.printCount(game, true);
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							//if (pressed_key_cat == SDLK_DOWN && pressed_key_box == KEY_PRESS_DEFAULT)
							//{
							//	//pressed_key_box = KEY_PRESS_DEFAULT;
							//	return RECURSION;
							//}
							keydown_for_cat = SDLK_UP;
							int result = playingLevel(game, counter, file, copy_catAndGift, /*level,*/ copy_texture, quit, timer);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								//showTexture(CAT, copy_texture[CAT].posTexture, game);
								game.showPic(game.GetTexture(CAT), copy_texture[CAT].posTexture);
							}
							else
								return EXIT_TO_MENU;
						}
						else if (copy_catAndGift[copy_texture[CAT].Y - 1][copy_texture[CAT].X] == PRESENT
							&& game.infOfFild.level[copy_texture[CAT].Y - 2][copy_texture[CAT].X] != WALL
							&& copy_catAndGift[copy_texture[CAT].Y - 2][copy_texture[CAT].X] != PRESENT)
						{
							counter.printCount(game, true);
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
							int result = playingLevel(game, counter, file, copy_catAndGift, /*level,*/ copy_texture, quit, timer);
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
							counter.printCount(game, true);
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							keydown_for_cat = SDLK_DOWN;
							int result = playingLevel(game, counter, file, copy_catAndGift, /*level,*/ copy_texture, quit, timer);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								//showTexture(CAT, copy_texture[CAT].posTexture, game);
								game.showPic(game.GetTexture(CAT), copy_texture[CAT].posTexture);
								//copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = CAT;
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
							counter.printCount(game, true);

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
							int result = playingLevel(game, counter, file, copy_catAndGift, /*level,*/ copy_texture, quit, timer);
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
					counter.printCount(game, false);

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

bool characterMovement(Surf& game, Counter& counter, fstream& file, fstream& fileCat, bool& quit, bool new_level)
{//передвижение персонажей

	stop_timer = false;
	Timer timer;
	thread th(&Timer::timeGo, ref(timer), ref(game));//ref - используется 
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

	game.showPicWallp(game.GetWallp(BACKGROUND_TIME));
	field(game, game.infOfFild.level, file, texture_of_level[CAT].posTexture);

	//vector<vector<int>> catAndGift;
	createMap(game, game.infOfFild.catAndGift, fileCat, new_level);
	field(game, game.infOfFild.catAndGift, fileCat, texture_of_level[CAT].posTexture);

	for (int y = 0; y < (game.infOfFild.GetHeight()); y++)
	{
		for (int x = 0; x < (game.infOfFild.GetWidth()); x++)
		{
			if (game.infOfFild.catAndGift[y][x] == CAT)
			{
				texture_of_level[CAT].X = x;
				texture_of_level[CAT].Y = y;
			}
			if (game.infOfFild.level[y][x] == PLACEHERE) {
				game.infOfFild.SetCountPlace(game.infOfFild.GetCountPlace() + 1);
			}
		}
	}

	texture_of_level[CAT].posTexture.x = ((SCREEN_WIDTH / 2) - ((game.infOfFild.GetWidth()) / 2.0 * texture_of_level[CAT].sizeTexture)) + texture_of_level[CAT].X * texture_of_level[CAT].sizeTexture;
	texture_of_level[CAT].posTexture.y = ((SCREEN_HEIGHT / 2) - ((game.infOfFild.GetHeight()) / 2.0 * texture_of_level[CAT].sizeTexture)) + texture_of_level[CAT].Y * texture_of_level[CAT].sizeTexture;


	counter.printAll(game);
	//countOfStep(game, true, true);

	if (playingLevel(game, counter, file, game.infOfFild.catAndGift, texture_of_level, quit, timer, true) == EXIT_TO_MENU)
	{
		return EXIT_TO_MENU;
	}
	else
	{
		return WIN;
	}
	//SDL_Delay(1000);
	//return WIN;
}
void createMap(Surf& game, vector<vector<int>>& array, fstream& file, bool new_level)
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
			file.seekg(i, ios::beg);
		}
		i = file.tellg();
		string str;
		file >> str;
		game.infOfFild.SetHeight(stoi(str));
		file >> str;
		game.infOfFild.SetWidth(stoi(str));
		for (int i = 0; i < (game.infOfFild.GetHeight()); i++)
		{
			vector<int> arr;
			for (int j = 0; j < (game.infOfFild.GetWidth()); j++)
			{
				file >> str;
				arr.push_back(stoi(str));
			}
			array.push_back(arr);
		}

	}
}
void field(Surf& game, vector<vector<int>> array, fstream& file, SDL_Rect posTexture)
{//тут будет отображаться массив в-виде картинки
	int sizeTexture = 50;

	//SDL_Rect posTexture;
	double X = (SCREEN_WIDTH / 2) - (game.infOfFild.GetWidth() / 2.0 * sizeTexture);
	posTexture.x = X;
	posTexture.y = (SCREEN_HEIGHT / 2) - (game.infOfFild.GetHeight() / 2.0 * sizeTexture);
	for (int i = 0; i < game.infOfFild.GetHeight(); i++) {
		for (int j = 0; j < game.infOfFild.GetWidth(); j++) {
			switch (array[i][j])
			{

			case WALL:
				//showTexture(WALL, posTexture, game);
				game.showPic(game.GetTexture(WALL), posTexture);
				break;
			case FLOOR:
				//showTexture(FLOOR, posTexture, game);
				game.showPic(game.GetTexture(FLOOR), posTexture);
				break;
			case CAT:
				//showTexture(CAT, posTexture, game);
				game.showPic(game.GetTexture(CAT), posTexture);
				break;
			case PRESENT:
				if (game.infOfFild.level[i][j] == PLACEHERE)
				{
					//showTexture(BOX_IN_PLACEHERE, posTexture, game);
					game.showPic(game.GetTexture(BOX_IN_PLACEHERE), posTexture);
				}
				else
				{
					//showTexture(PRESENT, posTexture, game);
					game.showPic(game.GetTexture(PRESENT), posTexture);
				}
				break;
			case PLACEHERE:
				//showTexture(PLACEHERE, posTexture, game);
				game.showPic(game.GetTexture(PLACEHERE), posTexture);
				break;
			}
			posTexture.x += sizeTexture;
		}
		posTexture.x = X;
		posTexture.y += sizeTexture;
	}

}

//void showTexture(int i, SDL_Rect posTexture, Surface& game)
//{
//	game.CurrentSurface = game.Texture[i];
//	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &posTexture);
//	SDL_UpdateWindowSurface(game.Window);
//}



//int showButton(int i)
//{
//	if (i == 0)return 250;
//	if (i == 1)stretchRect.y = y_of_button2;
//	if (i == 2)stretchRect.y = y_of_button3;
//	/*game.CurrentSurface = game.Buttons[i];
//	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, &stretchRect);
//	SDL_UpdateWindowSurface(game.Window);*/
//}

//bool init(Surface& game)
//{
//	bool success = true;
//	if (SDL_Init(SDL_INIT_VIDEO) < 0)
//	{
//		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
//		success = false;
//	}
//	else
//	{
//		game.Window = SDL_CreateWindow(" Sokoban",
//			SDL_WINDOWPOS_UNDEFINED,
//			SDL_WINDOWPOS_UNDEFINED,
//			SCREEN_WIDTH, SCREEN_HEIGHT,
//			SDL_WINDOW_SHOWN);
//		if (game.Window == NULL)
//		{
//			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
//			success = false;
//		}
//		else
//		{
//			game.ScreenSurface = SDL_GetWindowSurface(game.Window);
//		}
//	}
//	return success;
//}
//bool loadMedia(Surface& game)
//{
//	bool success = true;
//
//	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
//	{
//		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
//		success = false;
//	}
//	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
//	{
//		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
//		success = false;
//	}
//
//	game.music1 = Mix_LoadMUS("sound\\music1.wav");
//	game.music2 = Mix_LoadMUS("sound\\music1.wav");
//	if (game.music1 == NULL)
//	{
//		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
//		success = false;
//	}
//	if (game.music2 == NULL)
//	{
//		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
//		success = false;
//	}
//	game.button = Mix_LoadWAV("sound\\button.wav");
//	game.box = Mix_LoadWAV("sound\\box.wav");
//	game.intro = Mix_LoadWAV("sound\\intro.wav");
//	//Если что-то пошло не так
//	if ((game.button == NULL) || (game.box == NULL))
//	{
//		return false;
//	}
//	game.button = Mix_LoadWAV("sound\\button.wav");
//	game.box = Mix_LoadWAV("sound\\box.wav");
//	game.intro = Mix_LoadWAV("sound\\intro.wav");
//	//Если что-то пошло не так
//	if ((game.button == NULL) || (game.box == NULL))
//	{
//		return false;
//	}
//	game.Wallps[0] = loadSurface("Wallps\\teamLogo.bmp");
//	game.Wallps[1] = loadSurface("Wallps\\gameLogo.bmp");
//	game.Wallps[2] = loadSurface("Wallps\\MainMenu.bmp");
//	game.Wallps[MENU_EXIT] = loadSurface("Wallps\\MenuExit.bmp");
//	game.Wallps[WIN_WALP] = loadSurface("Wallps\\Win.bmp");
//	game.Wallps[LOSE] = loadSurface("Wallps\\Lose.bmp");
//
//	game.Buttons[0] = loadSurface("buttons\\PlayGame1.bmp");
//	game.Buttons[1] = loadSurface("buttons\\HowToPlay1.bmp");
//	game.Buttons[2] = loadSurface("buttons\\Exit1.bmp");
//	game.Buttons[YES] = loadSurface("buttons\\Yes1.bmp");
//	game.Buttons[NO] = loadSurface("buttons\\No1.bmp");
//	game.Buttons[NEXT] = loadSurface("buttons\\Next1.bmp");
//	game.Buttons[BACK] = loadSurface("buttons\\Back1.bmp");
//	game.Buttons[RETRY] = loadSurface("buttons\\Retry.bmp");
//	game.PressedButtons[0] = loadSurface("pressed_buttons\\PlayGame2.bmp");
//	game.PressedButtons[1] = loadSurface("pressed_buttons\\HowToPlay2.bmp");
//	game.PressedButtons[2] = loadSurface("pressed_buttons\\Exit2.bmp");
//	game.PressedButtons[YES] = loadSurface("pressed_buttons\\Yes2.bmp");
//	game.PressedButtons[NO] = loadSurface("pressed_buttons\\No2.bmp");
//	game.PressedButtons[NEXT] = loadSurface("pressed_buttons\\Next2.bmp");
//	game.PressedButtons[BACK] = loadSurface("pressed_buttons\\Back2.bmp");
//	game.PressedButtons[RETRY] = loadSurface("pressed_buttons\\Retry.bmp");
//	for (int i = 0; i < CountOfButtons; i++)
//	{
//		if (game.Buttons[i] == NULL || game.PressedButtons[i] == NULL) {
//			printf("Failed to load up button!\n");
//			success = false;
//		}
//	}
//	game.Texture[EMPTY] = loadSurface("textures\\empty.bmp");
//	game.Texture[WALL] = loadSurface("textures\\wall.bmp");
//	game.Texture[FLOOR] = loadSurface("textures\\floor.bmp");
//	game.Texture[CAT] = loadSurface("textures\\mainCat.bmp");
//	game.Texture[PRESENT] = loadSurface("textures\\PresentBox.bmp");
//	game.Texture[PLACEHERE] = loadSurface("textures\\PlaceHere.bmp");
//	game.Texture[BACKGROUND] = loadSurface("textures\\Background.bmp");
//	game.Texture[BOX_IN_PLACEHERE] = loadSurface("textures\\BoxInPlaceHere.bmp");
//	game.Texture[BACKGROUND_TIME] = loadSurface("textures\\BackgroundTime.bmp");
//
//	game.WindowsHowToPlay[FIRST] = loadSurface("how_to_play\\1.bmp");
//	game.WindowsHowToPlay[SECOND] = loadSurface("how_to_play\\2.bmp");
//	game.WindowsHowToPlay[THIRD] = loadSurface("how_to_play\\3.bmp");
//	game.WindowsHowToPlay[FOURTH] = loadSurface("how_to_play\\4.bmp");
//	game.WindowsHowToPlay[FIFTH] = loadSurface("how_to_play\\5.bmp");
//	game.WindowsHowToPlay[SIXTH] = loadSurface("how_to_play\\6.bmp");
//
//	game.Numbers[0] = loadSurface("numbers\\0 number.bmp");
//	game.Numbers[1] = loadSurface("numbers\\1 number.bmp");
//	game.Numbers[2] = loadSurface("numbers\\2 number.bmp");
//	game.Numbers[3] = loadSurface("numbers\\3 number.bmp");
//	game.Numbers[4] = loadSurface("numbers\\4 number.bmp");
//	game.Numbers[5] = loadSurface("numbers\\5 number.bmp");
//	game.Numbers[6] = loadSurface("numbers\\6 number.bmp");
//	game.Numbers[7] = loadSurface("numbers\\7 number.bmp");
//	game.Numbers[8] = loadSurface("numbers\\8 number.bmp");
//	game.Numbers[9] = loadSurface("numbers\\9 number.bmp");
//	game.Numbers[10] = loadSurface("numbers\\colon.bmp");
//	game.Numbers[11] = loadSurface("numbers\\slash.bmp");
//
//	game.WindowLevel[0] = loadSurface("windowlevel\\1.bmp");
//	game.WindowLevel[1] = loadSurface("windowlevel\\2.bmp");
//	game.WindowLevel[2] = loadSurface("windowlevel\\3.bmp");
//	game.WindowLevel[3] = loadSurface("windowlevel\\4.bmp");
//	game.WindowLevel[4] = loadSurface("windowlevel\\5.bmp");
//
//	game.Comic[0] = loadSurface("comic\\0.bmp");
//	game.Comic[1] = loadSurface("comic\\1.bmp");
//	game.Comic[2] = loadSurface("comic\\2.bmp");
//	game.Comic[3] = loadSurface("comic\\3.bmp");
//	game.Comic[4] = loadSurface("comic\\4.bmp");
//
//	for (int i = 0; i < CountOfComic; i++)
//	{
//		if (game.Comic[i] == NULL)
//		{
//			printf("Failed to load up comic!\n");
//			success = false;
//		}
//	}
//	for (int i = 0; i < CountOfLeveles; i++)
//	{
//		if (game.Numbers[i] == NULL)
//		{
//			printf("Failed to load up image!\n");
//			success = false;
//		}
//	}
//	for (int i = 0; i < 12; i++)
//	{
//		if (game.Numbers[i] == NULL)
//		{
//			printf("Failed to load up image!\n");
//			success = false;
//		}
//	}
//	for (int i = 0; i < CountOdArrs::CountOfTexture; i++)
//	{
//		if (game.Texture[i] == NULL)
//		{
//			printf("Failed to load up image!\n");
//			success = false;
//		}
//	}
//
//	return success;
//}
//void close(Surface& game)
//{
//	//После уничтожения окна не забудь указатели указать на NULL
//	//Освободить поверхность
//	Mix_FreeMusic(game.music1);
//	game.music1 = NULL;
//	for (int i = 0; i < CountOfWallps; ++i)
//	{
//		SDL_FreeSurface(game.Wallps[i]);
//		game.Wallps[i] = NULL;
//	}
//	//Уничтожить окно
//	SDL_DestroyWindow(game.Window);
//	game.Window = NULL;
//	SDL_Quit();
//	Mix_Quit();
//}
bool isPressed(int keyCode)
{
	return 1;
}
bool isReleased(int keyCode)
{
	return 0;
}


