#pragma once
#include"Libraries.h"
#include "Enums.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
using namespace std;
bool stop_timer = false;

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
	PlayField() 
	{
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
	//Mix_Music* music1;
	//Mix_Music* music2;
	//Mix_Chunk* box;
	//Mix_Chunk* button;
	//Mix_Chunk* win;
	//Mix_Chunk* intro;
public:
	PlayField infOfFild;
	SDL_Event e;

	//Getter
	SDL_Surface* GetNumber(int what) const
	{
		return Numbers[what];
	}
	SDL_Surface* GetWallp(int what)const
	{
		return Wallps[what];
	}
	SDL_Surface* GetPressedButton(int what)const
	{
		return PressedButtons[what];
	}
	SDL_Surface* GetButton(int what)const
	{
		return Buttons[what];
	}
	SDL_Surface* GetWindowLevel(int what)const
	{
		return WindowLevel[what];
	}
	SDL_Surface* GetWindowHowToPlay(int what)const
	{
		return WindowsHowToPlay[what];
	}
	SDL_Surface* GetComic(int what)const
	{
		return Comic[what];
	}
	SDL_Surface* GetTexture(int what)const
	{
		return Texture[what];
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
		Buttons[NEXT] = loadSurface("buttons\\Next1.bmp");
		Buttons[BACK] = loadSurface("buttons\\Back1.bmp");
		PressedButtons[NEXT] = loadSurface("pressed_buttons\\Next2.bmp");
		PressedButtons[BACK] = loadSurface("pressed_buttons\\Back2.bmp");
	}
	void loadLogos()
	{
		Wallps[0] = loadSurface("Wallps\\teamLogo.bmp");
		Wallps[1] = loadSurface("Wallps\\gameLogo.bmp");
	}
	void freeSurf(SDL_Surface* current_surf)
	{
		SDL_FreeSurface(current_surf);
		current_surf = NULL;
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
	void loadNumbers()
	{
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
	void freeAfterNumbers() 
	{
		for (int i = 0; i < CountOfNumbers; ++i)
		{
			SDL_FreeSurface(Numbers[i]);
			Numbers[i] = NULL;
		}
	}
	void freeAfterExit()
	{
		SDL_FreeSurface(Wallps[MENU_EXIT]);
		Wallps[MENU_EXIT] = NULL;
		SDL_FreeSurface(PressedButtons[YES]);
		PressedButtons[YES] = NULL;
		SDL_FreeSurface(PressedButtons[NO]);
		PressedButtons[NO] = NULL;
		SDL_FreeSurface(Buttons[YES]);
		Buttons[YES] = NULL;
		SDL_FreeSurface(Buttons[NO]);
		Buttons[NO] = NULL;
	}
	void freeAfterHowToPlay()
	{
		for (int i = 0; i < CountOfWindows; i++)
		{
			SDL_FreeSurface(WindowsHowToPlay[i]);
			WindowsHowToPlay[i] = NULL;
		}
		SDL_FreeSurface(Buttons[NEXT]);
		Buttons[NEXT] = NULL;
		SDL_FreeSurface(Buttons[BACK]);
		Buttons[BACK] = NULL;
		SDL_FreeSurface(PressedButtons[NEXT]);
		PressedButtons[NEXT] = NULL;
		SDL_FreeSurface(PressedButtons[BACK]);
		PressedButtons[BACK] = NULL;
	}
	void freeAfterComics()
	{
		for (int i = 0; i < CountOfComic; i++)
		{
			SDL_FreeSurface(Comic[i]);
		}
	}
	void freeAfterTextures()
	{
		for (int i = 0; i < CountOfTexture; ++i)
		{
			SDL_FreeSurface(Texture[i]);
			Texture[i] = NULL;
		}
	}
	void loadMedia()
	{
		bool success = true;

		//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		//if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		//{
		//	printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		//	success = false;
		//}

		//music1 = Mix_LoadMUS("sound\\menu.wav");
		//music2 = Mix_LoadMUS("sound\\game.wav");
		//button = Mix_LoadWAV("sound\\button.wav");
		//box = Mix_LoadWAV("sound\\box.wav");
		//intro = Mix_LoadWAV("sound\\intro.wav");
		////Если что-то пошло не так
		//button = Mix_LoadWAV("sound\\button.wav");
		//box = Mix_LoadWAV("sound\\box.wav");
		//intro = Mix_LoadWAV("sound\\intro.wav");
		//Если что-то пошло не так
		
		Wallps[2] = loadSurface("Wallps\\MainMenu.bmp");
		Wallps[WIN_WALP] = loadSurface("Wallps\\Win.bmp");
		Wallps[LOSE] = loadSurface("Wallps\\Lose.bmp");
		Wallps[BLACK] = loadSurface("comic\\0.bmp");
		Wallps[BACKGROUND_TIME] = loadSurface("textures\\BackgroundTime.bmp");

		Buttons[0] = loadSurface("buttons\\PlayGame1.bmp");
		Buttons[1] = loadSurface("buttons\\HowToPlay1.bmp");
		Buttons[2] = loadSurface("buttons\\Exit1.bmp");
		Buttons[NEXT] = loadSurface("buttons\\Next1.bmp");
		Buttons[BACK] = loadSurface("buttons\\Back1.bmp");
		Buttons[RETRY] = loadSurface("buttons\\Retry.bmp");
		PressedButtons[0] = loadSurface("pressed_buttons\\PlayGame2.bmp");
		PressedButtons[1] = loadSurface("pressed_buttons\\HowToPlay2.bmp");
		PressedButtons[2] = loadSurface("pressed_buttons\\Exit2.bmp");
		PressedButtons[NEXT] = loadSurface("pressed_buttons\\Next2.bmp");
		PressedButtons[BACK] = loadSurface("pressed_buttons\\Back2.bmp");
		PressedButtons[RETRY] = loadSurface("pressed_buttons\\Retry.bmp");

		WindowLevel[0] = loadSurface("windowlevel\\1.bmp");
		WindowLevel[1] = loadSurface("windowlevel\\2.bmp");
		WindowLevel[2] = loadSurface("windowlevel\\3.bmp");
		WindowLevel[3] = loadSurface("windowlevel\\4.bmp");
		WindowLevel[4] = loadSurface("windowlevel\\5.bmp");
	}
	/*void playIntro(int channel, int num)
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
	}*/
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
		//while (!Mix_FadeOutMusic(2000) && Mix_PlayingMusic()) {
		//	// wait for any fades to complete
		//	SDL_Delay(40);
		//}
		//if (Mix_FadeInMusic(music2, -1, 2000) == -1) {
		//	printf("Mix_FadeInMusic: %s\n", Mix_GetError());

		//}
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

};
class TextureNasledovanie : public Surf
{

	SDL_Surface* PicTexture;
public:
	SDL_Rect posTexture;
	int X;
	int Y;
	int size_texture;
	TextureNasledovanie() : TextureNasledovanie("textures\\empty.bmp")
	{

	}
	TextureNasledovanie(string path) : TextureNasledovanie(path, 0, 0)
	{

	}
	TextureNasledovanie(string path, int X, int Y)
	{
		this->X = X;
		this->Y = Y;
		SetPicTexture(path);
		size_texture = 50;
		posTexture.x = 0;
		posTexture.y = 0;
	}
	//Setters
	void SetPosTextureY(unsigned int y)
	{
		posTexture.y = y;
	}
	void SetPosTextureX(unsigned int x)
	{
		posTexture.x = x;
	}
	void SetX(unsigned int X)
	{
		this->X = X;
	}
	void SetY(unsigned int Y)
	{
		this->Y = Y;
	}
	//Getters
	int GetX()
	{
		return X;
	}
	int GetY()
	{
		return Y;
	}
	SDL_Surface* GetPicTexture()
	{
		return PicTexture;
	}
	SDL_Rect GetPosTexture()
	{
		return posTexture;
	}
	int GetPosTextureY()
	{
		return posTexture.y;
	}
	int GetPosTextureX()
	{
		return posTexture.x;
	}
	int Getsize_texture()
	{
		return size_texture;
	}
	void SetPicTexture(string path)
	{
		PicTexture = loadSurface(path);
	}
	void movementLeftCat()
	{
		X--;
		posTexture.x -= size_texture;
	}
	void movementRightCat()
	{
		Y++;
		posTexture.y += size_texture;
	}
	void movementUpCat()
	{
		Y--;
		posTexture.y -= size_texture;
	}
	void movementDownCat()
	{
		X++;
		posTexture.x += size_texture;
	}
	void movementLeftBox(TextureNasledovanie copy_texture)
	{
		posTexture.y = copy_texture.posTexture.y;
		posTexture.x = copy_texture.posTexture.x - copy_texture.size_texture;
		Y = copy_texture.Y;
		X = copy_texture.X - 1;
	}
	void movementRightBox(TextureNasledovanie copy_texture)
	{
		posTexture.y = copy_texture.posTexture.y;
		posTexture.x = copy_texture.posTexture.x + copy_texture.size_texture;
		Y = copy_texture.Y;
		X = copy_texture.X + 1;
	}

};
class Counter
{
	int size;
	int count_step;
	int last_number;
	int max_number;
	SDL_Rect texture_of_number;
	void increase()
	{
		count_step++;
	}
	void decrease()
	{
		count_step--;
	}

public:
	Counter() : Counter(200) {}
	Counter(int max_number)
	{
		size = 20;
		count_step = 0;
		last_number = 0;
		texture_of_number.y = 35;
		this->max_number = max_number;
	}
	void printAll(Surf& game)
	{
		texture_of_number.x = size * 7;
		int c = max_number;
		for (int i = 0; i < 3; i++)
		{
			last_number = c % 10;
			c /= 10;
			game.showPic(game.GetNumber(last_number), texture_of_number);
			texture_of_number.x -= size;
		}
		texture_of_number.x = size * 4;
		game.showPic(game.GetNumber(11), texture_of_number);

		texture_of_number.x = size * 3;
		c = count_step;
		for (int i = 0; i < 3; i++) {
			last_number = c % 10;
			c /= 10;
			game.showPic(game.GetNumber(last_number), texture_of_number);
			texture_of_number.x -= size;
		}
	}
	void printCount(Surf& game, bool what) 
	{
		if (what)increase();
		else decrease();

		if (what && count_step % 10 == 0 || !what && count_step % 10 == 9)
		{
			last_number = count_step / 10 % 10;
			texture_of_number.x = size * 2;
			game.showPic(game.GetNumber(last_number), texture_of_number);
		}
		if (what && (count_step / 10) % 10 == 0 || !what && (count_step / 10) % 10 == 9)
		{
			last_number = count_step / 100;
			texture_of_number.x = size;
			game.showPic(game.GetNumber(last_number), texture_of_number);
		}
		last_number = count_step % 10;
		texture_of_number.x = size * 3;
		game.showPic(game.GetNumber(last_number), texture_of_number);
	}
	//Setters
	void SetCountStep(int count) 
	{
		count_step = count;
	}
	//Getters
	int GetCountStep() 
	{
		return count_step;
	}
	int GetMaxNumber()
	{
		return max_number;
	}
};
class Timer 
{
	int size;
	int min;//минуты
	int sec;
	int count_of_sec = 0;
	int x = 0, y = 0, z = 0, w = 0; //изменение определенных цифр во времени
	SDL_Rect texture_of_number;
public:
	Timer() : Timer(90) {}
	Timer(int count_of_sec)
	{
		this->count_of_sec = count_of_sec;
		size = 20;
		min = 0;
		texture_of_number.y = 35;
		sec = this->count_of_sec;
	}
	void Converter()
	{
		while (sec > 60)
		{
			min++;
			sec -= 60;
		}
	}
	void PrintAll(Surf game)
	{
		x = sec % 10;
		texture_of_number.x = SCREEN_WIDTH - size * 2;
		game.showPic(game.GetNumber(x), texture_of_number);

		y = (sec / 10);
		texture_of_number.x -= size;
		game.showPic(game.GetNumber(y), texture_of_number);

		texture_of_number.x -= size;
		game.showPic(game.GetNumber(10), texture_of_number);

		z = min % 10;
		texture_of_number.x -= size;
		game.showPic(game.GetNumber(z), texture_of_number);

		w = (min / 10);
		texture_of_number.x -= size;
		game.showPic(game.GetNumber(w), texture_of_number);

	}
	void timeGo(Surf& game)
	{
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
					game.showPic(game.GetNumber(z), texture_of_number);
					if ((min / 10) - 1 >= 0) {
						w = (min / 10);
						texture_of_number.x = SCREEN_WIDTH - size * 6;
						game.showPic(game.GetNumber(w), texture_of_number);

					}
				}
			}
			sec--;
			if (x == 0) {
				y = (sec / 10) % 10;
				texture_of_number.x = SCREEN_WIDTH - size * 3;
				game.showPic(game.GetNumber(y), texture_of_number);
			}
			x = sec % 10;
			texture_of_number.x = SCREEN_WIDTH - size * 2;
			game.showPic(game.GetNumber(x), texture_of_number);
			count_of_sec--;
			if (min == 0 && sec == 0) {
				stop_timer = true;
				return;
			}

			this_thread::sleep_for(chrono::milliseconds(1000));
		}
	}

	//Getters
	int GetCountSec()
	{
		return count_of_sec;
	}
	//Setters
	void SetCountSec(unsigned int digit)
	{

		count_of_sec = digit;
	}
};


