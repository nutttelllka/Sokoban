
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Structures.h"
#include "Enums.h"
#include <vector>
#include <stdio.h>
#include <string>
#include <sstream>

//#include "LTexture(temp).h"

//#include "ClTexture.h"
//#include "ClTimer.h"
using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
//#define KMOD_CTRL_z (SDLK_LCTRL|SDLK_z)
void intro(Surface& game);
bool init(Surface& game);
bool loadMedia(Surface& game);
void close(Surface& game);
void menu(Surface& game, bool& quit, int i, int& i_for_buttons, int& current_pressed_button);
void playGame(Surface& game, bool& quit);
void showButton(Surface& game, int i, SDL_Rect stretchRectб, int y_of_button1 = 250, int y_of_button2 = 250 + 70, int y_of_button3 = 250 + 140);
void backgroundMenu(Surface& game);
void exit(bool& quit, Surface& game);
void createMap(Surface& game, vector<vector<int>>& array, fstream& file);//
void field(Surface& game, vector<vector<int>> array, fstream& file, SDL_Rect posTexture);//
void characterMovement(Surface& game, fstream& file, fstream& fileCat, bool& quit);
void showTexture(int i, SDL_Rect posTexture, Surface& game);
bool isPressed(int keyCode);
bool isReleased(int keyCode);
void howToPlay(Surface& game, bool quit, int count = 0);
bool win(Surface& game, vector<vector<int>> copy_catAndGift);
int playingLevel(Surface& game, fstream& file, vector<vector<int>> catAndGift, vector < Texture> texture_of_elements, bool& quit, bool z = false);
void countOfStep(Surface& game, bool what);
bool pressed_keys[7] = {};

TTF_Font* gFont = NULL;

//class ClTexture
//{
//public:
//	//Initializes variables
//	ClTexture()
//	{
//		//Initialize
//		mTexture = NULL;
//		mWidth = 0;
//		mHeight = 0;
//	}
//
//	//Deallocates memory
//	~ClTexture()
//	{
//		//Deallocate
//		free();
//	}
//
//	//Loads image at specified path
//	bool loadFromFile(Surface game, string path)
//{
//	//Get rid of preexisting texture
//	free();
//
//	//The final texture
//	SDL_Texture* newTexture = NULL;
//
//	//Load image at specified path
//	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//	if (loadedSurface == NULL)
//	{
//		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
//	}
//	else
//	{
//		//Color key image
//		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
//
//		//Create texture from surface pixels
//		newTexture = SDL_CreateTextureFromSurface(game.gRenderer, loadedSurface);
//		if (newTexture == NULL)
//		{
//			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//		}
//		else
//		{
//			//Get image dimensions
//			mWidth = loadedSurface->w;
//			mHeight = loadedSurface->h;
//		}
//
//		//Get rid of old loaded surface
//		SDL_FreeSurface(loadedSurface);
//	}
//
//	//Return success
//	mTexture = newTexture;
//	return mTexture != NULL;
//}
//	//Creates image from font string
//	bool loadFromRenderedText(Surface game, string textureText, SDL_Color textColor)
//	{
//		//Get rid of preexisting texture
//		free();
//
//		//Render text surface
//		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
//		if (textSurface == NULL)
//		{
//			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
//		}
//		else
//		{
//			//Create texture from surface pixels
//			mTexture = SDL_CreateTextureFromSurface(game.gRenderer, textSurface);
//			if (mTexture == NULL)
//			{
//				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
//			}
//			else
//			{
//				//Get image dimensions
//				mWidth = textSurface->w;
//				mHeight = textSurface->h;
//			}
//
//			//Get rid of old surface
//			SDL_FreeSurface(textSurface);
//		}
//
//		//Return success
//		return mTexture != NULL;
//	}
//
//	//Deallocates texture
//	void free()
//	{
//		//Free texture if it exists
//		if (mTexture != NULL)
//		{
//			SDL_DestroyTexture(mTexture);
//			mTexture = NULL;
//			mWidth = 0;
//			mHeight = 0;
//		}
//	}
//
//	//Set color modulation
//	void setColor(Uint8 red, Uint8 green, Uint8 blue)
//	{
//		//Modulate texture rgb
//		SDL_SetTextureColorMod(mTexture, red, green, blue);
//	}
//
//
//	//Set blending
//	void setBlendMode(SDL_BlendMode blending)
//	{
//		//Set blending function
//		SDL_SetTextureBlendMode(mTexture, blending);
//	}
//
//
//	//Set alpha modulation
//	void setAlpha(Uint8 alpha)
//	{
//		//Modulate texture alpha
//		SDL_SetTextureAlphaMod(mTexture, alpha);
//	}
//
//	//Renders texture at given point
//	void render(Surface game, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
//	{
//		//Set rendering space and render to screen
//		SDL_Rect renderQuad = { x, y, mWidth, mHeight };
//
//		//Set clip rendering dimensions
//		if (clip != NULL)
//		{
//			renderQuad.w = clip->w;
//			renderQuad.h = clip->h;
//		}
//
//		//Render to screen
//		SDL_RenderCopyEx(game.gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
//	}
//
//	//Gets image dimensions
//	int getWidth() {
//		return mWidth;
//	}
//	int getHeight() 
//	{
//		return mHeight;
//	}
//
//private:
//	//The actual hardware texture
//	SDL_Texture* mTexture;
//
//	//Image dimensions
//	int mWidth;
//	int mHeight;
//};
//ClTexture gTimeTextTexture;
//ClTexture gPausePromptTexture;
//ClTexture gStartPromptTexture;

//ClTexture::ClTexture()
//{
//	//Initialize
//	mTexture = NULL;
//	mWidth = 0;
//	mHeight = 0;
//}
//
//ClTexture::~ClTexture()
//{
//	//Deallocate
//	free();
//}
//
//bool ClTexture::loadFromFile(Surface game, string path)
//{
//	//Get rid of preexisting texture
//	free();
//
//	//The final texture
//	SDL_Texture* newTexture = NULL;
//
//	//Load image at specified path
//	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//	if (loadedSurface == NULL)
//	{
//		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
//	}
//	else
//	{
//		//Color key image
//		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
//
//		//Create texture from surface pixels
//		newTexture = SDL_CreateTextureFromSurface(game.gRenderer, loadedSurface);
//		if (newTexture == NULL)
//		{
//			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//		}
//		else
//		{
//			//Get image dimensions
//			mWidth = loadedSurface->w;
//			mHeight = loadedSurface->h;
//		}
//
//		//Get rid of old loaded surface
//		SDL_FreeSurface(loadedSurface);
//	}
//
//	//Return success
//	mTexture = newTexture;
//	return mTexture != NULL;
//}
//
//bool ClTexture::loadFromRenderedText(Surface game, string textureText, SDL_Color textColor)
//{
//	//Get rid of preexisting texture
//	free();
//
//	//Render text surface
//	SDL_Surface* textSurface = TTF_RenderText_Solid(game.gFont, textureText.c_str(), textColor);
//	if (textSurface == NULL)
//	{
//		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
//	}
//	else
//	{
//		//Create texture from surface pixels
//		mTexture = SDL_CreateTextureFromSurface(game.gRenderer, textSurface);
//		if (mTexture == NULL)
//		{
//			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
//		}
//		else
//		{
//			//Get image dimensions
//			mWidth = textSurface->w;
//			mHeight = textSurface->h;
//		}
//
//		//Get rid of old surface
//		SDL_FreeSurface(textSurface);
//	}
//
//	//Return success
//	return mTexture != NULL;
//}
//
//void ClTexture::free()
//{
//	//Free texture if it exists
//	if (mTexture != NULL)
//	{
//		SDL_DestroyTexture(mTexture);
//		mTexture = NULL;
//		mWidth = 0;
//		mHeight = 0;
//	}
//}
//
//void ClTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
//{
//	//Modulate texture rgb
//	SDL_SetTextureColorMod(mTexture, red, green, blue);
//}
//
//void ClTexture::setBlendMode(SDL_BlendMode blending)
//{
//	//Set blending function
//	SDL_SetTextureBlendMode(mTexture, blending);
//}
//
//void ClTexture::setAlpha(Uint8 alpha)
//{
//	//Modulate texture alpha
//	SDL_SetTextureAlphaMod(mTexture, alpha);
//}
//
//void ClTexture::render(Surface game, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
//{
//	//Set rendering space and render to screen
//	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
//
//	//Set clip rendering dimensions
//	if (clip != NULL)
//	{
//		renderQuad.w = clip->w;
//		renderQuad.h = clip->h;
//	}
//
//	//Render to screen
//	SDL_RenderCopyEx(game.gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
//}
//
//int ClTexture::getWidth()
//{
//	return mWidth;
//}
//
//int ClTexture::getHeight()
//{
//	return mHeight;
//}



//тут был Степа
SDL_Surface* loadSurface(string path);


//void Stealth()
//{
//	HWND Stealth;
//	AllocConsole();
//	Stealth = FindWindowA("ConsoleWindowClass", NULL);
//	ShowWindow(Stealth, 0);
//}
void showPic(Surface& game, SDL_Rect coord, int what_kind_of_arr,  int what_kind_of_pic)
{
	switch (what_kind_of_arr)
	{
	case LOGOS:
		game.CurrentSurface = game.Logos[what_kind_of_pic];
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
						showPic(game, coord_for_wallp, LOGOS, i);
						SDL_Delay(2000);
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
	game.CurrentSurface = game.Logos[2];
	SDL_BlitSurface(game.CurrentSurface, NULL, game.ScreenSurface, NULL);
	SDL_UpdateWindowSurface(game.Window);
}
void menu(Surface& game,bool& quit, int i, int& i_for_buttons, int& current_pressed_button)
{
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
					showPic(game, stretchRect, PRESSED_BUTTONS, current_pressed_button);
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
	SDL_Rect stretchRect;
	SDL_Rect coord_for_wallp  ;
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
					switch (count)
					{
					case SECOND:
						showPic(game, coord_for_wallp, WINDOWS, SECOND);
						break;
					case THIRD:
						showPic(game, coord_for_wallp, WINDOWS, THIRD);
						break;
					case FOURTH:
						showPic(game, coord_for_wallp, WINDOWS, FOURTH);
						break;
					case FIFTH:
						showPic(game, coord_for_wallp, WINDOWS, FIFTH);
						break;
					default:
						return;
					}
					break;
				case SDLK_LEFT:
					count--;
					stretchRect.x = 170;
					showPic(game, stretchRect, PRESSED_BUTTONS, BACK);
					SDL_Delay(200);
					switch (count)
					{
					case FIRST:
						showPic(game, coord_for_wallp, WINDOWS, FIRST);
						break;
					case SECOND:
						showPic(game, coord_for_wallp, WINDOWS, SECOND);
						break;
					case THIRD:
						showPic(game, coord_for_wallp, WINDOWS, THIRD);
						break;
					case FOURTH:
						showPic(game, coord_for_wallp, WINDOWS, FOURTH);
						break;
					default:
						return;
					}
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
void playGame(Surface& game, bool& quit)
{
	fstream file("fields.TXT");
	fstream fileCat("position.TXT");

	//int** level;
	/*vector<vector<int>> level;
	int height = 0;
	int width = 0;*/

	//vector<vector<int>> level;
	/*int height = 0;
	int width = 0;*/
	int number_of_level = 0;
	SDL_Rect coord_for_wallp;
	while (number_of_level < game.count_levels) {
		
		inisialitCoordOfWallp(coord_for_wallp);
		showPic(game, coord_for_wallp, LOGOS, LOGO_OF_GAME);
		SDL_Delay(1000);
		game.count_step = 0;

		createMap(game, game.infOfFild.level, file);
		characterMovement(game, file, fileCat, quit);
		game.infOfFild.level.clear();
		game.infOfFild.catAndGift.clear();
		//game.infOfFild.level.swap(vector<vector<int>>());
		vector<vector<int>>().swap(game.infOfFild.level);
		vector<vector<int>>().swap(game.infOfFild.catAndGift);

		number_of_level++;

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
void movementOfCat(vector < Texture>& copy_texture, int keydown_for_cat)
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
void movementOfBox(vector < Texture>& copy_texture, int keydown_for_box)
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
int playingLevel(Surface& game, fstream& file, vector<vector<int>> catAndGift, vector < Texture> texture_of_elements, bool& quit, bool z)
{
	vector<Texture> copy_texture = texture_of_elements;
	vector<vector<int>> copy_catAndGift = catAndGift;
	static int keydown_for_cat;
	static int keydown_for_box = KEY_PRESS_DEFAULT;
	copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = 0;
	movementOfCat(copy_texture, keydown_for_cat);
	
	if (keydown_for_box != KEY_PRESS_DEFAULT)
	{
		movementOfBox(copy_texture, keydown_for_box);
		keydown_for_box = KEY_PRESS_DEFAULT;
		//showTexture(PRESENT, copy_texture[PRESENT].posTexture, game);
		copy_catAndGift[copy_texture[PRESENT].Y][copy_texture[PRESENT].X] = PRESENT;
		showPresent(game, game.infOfFild.level, copy_texture, PRESENT);
	}
	showTexture(CAT, copy_texture[CAT].posTexture, game);
	copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = CAT;
	if (win(game,/* level,*/ copy_catAndGift))
		quit = true;
	showArrInConsole(copy_catAndGift, 9, 9);
	bool flag = false;
	while (!quit)
	{
		while (SDL_PollEvent(&game.e) != 0)
		{
			if (game.e.type == SDL_QUIT || flag)
			{
				bool quit2 = false;
				exit(quit2, game);
				if (quit2)return EXIT_TO_MENU;
				flag = false;
				SDL_Rect coord;
				inisialitCoordOfWallp(coord);
				showPic(game, coord, TEXTURES, BACKGROUND);
				showTexture(BACKGROUND, copy_texture[BACKGROUND].posTexture, game);
				field(game, game.infOfFild.level, file, copy_texture[CAT].posTexture);
				field(game, copy_catAndGift, file, copy_texture[CAT].posTexture);
				break;
			}
			else if (game.e.type == SDL_KEYDOWN )
			{
				
				switch (game.e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					flag = true;
					break;
				case SDLK_LEFT:
					
					if (game.infOfFild.level[copy_texture[CAT].Y][copy_texture[CAT].X - 1] != WALL)
					{
						countOfStep(game, true);
						if (copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X - 1] != PRESENT)
						{
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							keydown_for_cat = SDLK_LEFT;
							
							int result = playingLevel(game, file, copy_catAndGift,/* level, */copy_texture, quit,true);
							if (result == WIN)
								return WIN;
							else if(result == RECURSION)
								showTexture(CAT, copy_texture[CAT].posTexture, game);
							else
								return EXIT_TO_MENU;
						}
						else if (copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X - 1] == PRESENT 
							&& game.infOfFild.level[copy_texture[CAT].Y][copy_texture[CAT].X - 2] != WALL
							&& copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X - 2] != PRESENT)
						{
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
							int result = playingLevel(game, file, copy_catAndGift,/* level,*/ copy_texture, quit, true);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, FLOOR);
								showTexture(CAT, copy_texture[CAT].posTexture, game);
								showPresent(game, game.infOfFild.level, copy_texture, PRESENT);
								//showTexture(PRESENT, copy_texture[PRESENT].posTexture, game);
							}
							else
								return EXIT_TO_MENU;
						}
					}
					break;
				case SDLK_RIGHT:
					
					if (game.infOfFild.level[copy_texture[CAT].Y][copy_texture[CAT].X + 1] != WALL)
					{
						countOfStep(game, true);
						if (copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X + 1] != PRESENT)
						{
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							keydown_for_cat = SDLK_RIGHT;
							int result = playingLevel(game, file, copy_catAndGift,/* level,*/ copy_texture, quit, true);
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
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							copy_texture[PRESENT].posTexture.y = copy_texture[CAT].posTexture.y ;
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
							int result = playingLevel(game, file, copy_catAndGift, /*level,*/ copy_texture, quit, true);

							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, FLOOR);
								showTexture(CAT, copy_texture[CAT].posTexture, game);
								showPresent(game, game.infOfFild.level, copy_texture, PRESENT);
							}
							else
								return EXIT_TO_MENU;
						}
					}
					break;
				case SDLK_UP:
					if (game.infOfFild.level[copy_texture[CAT].Y - 1][copy_texture[CAT].X] != WALL)
					{
						countOfStep(game, true);
						if (copy_catAndGift[copy_texture[CAT].Y - 1][copy_texture[CAT].X] != PRESENT)
						{
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							keydown_for_cat = SDLK_UP;
							int result = playingLevel(game, file, copy_catAndGift, /*level,*/ copy_texture, quit, true);
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
							int result = playingLevel(game, file, copy_catAndGift, /*level,*/ copy_texture, quit, true);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, FLOOR);
								showTexture(CAT, copy_texture[CAT].posTexture, game);
								showPresent(game, game.infOfFild.level, copy_texture, PRESENT);
								//showTexture(PRESENT, copy_texture[PRESENT].posTexture, game);
							}
							else
								return EXIT_TO_MENU;
						}
					}
					break;
				case SDLK_DOWN:
					if (game.infOfFild.level[copy_texture[CAT].Y + 1][copy_texture[CAT].X] != WALL)
					{
						countOfStep(game, true);
						if (copy_catAndGift[copy_texture[CAT].Y + 1][copy_texture[CAT].X] != PRESENT)
						{
							showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, CAT);
							keydown_for_cat = SDLK_DOWN;
							int result = playingLevel(game, file, copy_catAndGift, /*level,*/ copy_texture, quit, true);
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
							int result = playingLevel(game, file, copy_catAndGift, /*level,*/ copy_texture, quit, true);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
							{
								showFloorOfPlaceHere(game, game.infOfFild.level, copy_texture, FLOOR);
								showTexture(CAT, copy_texture[CAT].posTexture, game);
								showPresent(game, game.infOfFild.level, copy_texture, PRESENT);
								//showTexture(PRESENT, copy_texture[PRESENT].posTexture, game);
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
				showArrInConsole(copy_catAndGift, 9, 9);

				if (pressed_keys[KEY_PRESS_LEFT_CTRL] && pressed_keys[KEY_PRESS_Z] && z)
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
void characterMovement(Surface& game, fstream& file, fstream& fileCat, bool& quit)
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

	
	showTexture(BACKGROUND, texture_of_level[CAT].posTexture, game);
	field(game,  game.infOfFild.level, file, texture_of_level[CAT].posTexture);

	//vector<vector<int>> catAndGift;
	createMap(game, game.infOfFild.catAndGift, fileCat);
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

	//game.timer.start();
	playingLevel(game, file, game.infOfFild.catAndGift, /* game.infOfFild.level,*/ texture_of_level, quit);

	//return;
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
void countOfStep(Surface& game, bool what) {
	if (what) game.count_step++;
	else game.count_step--;
	cout << endl << game.count_step << endl;
}
void exit(bool& quit, Surface& game)
{
	bool quit2 = false;
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	showPic(game, stretchRect, LOGOS, MENU_EXIT);
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
			//game.gRenderer = SDL_CreateRenderer(game.Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			//if (game.gRenderer == NULL)
			//{
			//	printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			//	success = false;
			//}
			//else
			//{
			//	//Initialize renderer color
			//	SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			//	//Initialize PNG loading
			//	int imgFlags = IMG_INIT_PNG;
			//	if (!(IMG_Init(imgFlags) & imgFlags))
			//	{
			//		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			//		success = false;
			//	}
			//	//Initialize SDL_ttf
			//	if (TTF_Init() == -1)
			//	{
			//		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			//		success = false;
			//	}
			//}
		}
	}
	return success;
}
//ClTexture gStartPromptTexture;
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
	//if (Mix_PlayingMusic() == 0)
	//{
	//	//Play the music
	//	Mix_PlayMusic(game.music, -1);
	//}
	game.button = Mix_LoadWAV("sound\\button.wav");
	game.box = Mix_LoadWAV("sound\\box.wav");

	//добавление шрифта и его настройка
	//gFont = TTF_OpenFont("lazy.ttf", 28);
	//if (gFont == NULL)
	//{
	//	printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	//	success = false;
	//}
	//else
	//{
	//	//Set text color as black
	//	SDL_Color textColor = { 0, 0, 0, 0 };
	//	////Load stop prompt texture
	//	//if (!gStartPromptTexture.loadFromRenderedText("Press S to Start or Stop the Timer", textColor))
	//	//{
	//	//	printf("Unable to render start/stop prompt texture!\n");
	//	//	success = false;
	//	//}
	//	////Load pause prompt texture
	//	//if (!gPausePromptTexture.loadFromRenderedText("Press P to Pause or Unpause the Timer", textColor))
	//	//{
	//	//	printf("Unable to render pause/unpause prompt texture!\n");
	//	//	success = false;
	//	//}
	//}



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
	game.Texture[BOX_IN_PLACEHERE] = loadSurface("BoxInPlaceHere.bmp");
	if (game.Texture[BOX_IN_PLACEHERE] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.WindowsHowToPlay[FIRST] = loadSurface("1.bmp");
	if (game.WindowsHowToPlay[FIRST] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.WindowsHowToPlay[SECOND] = loadSurface("2.bmp");
	if (game.WindowsHowToPlay[SECOND] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.WindowsHowToPlay[THIRD] = loadSurface("3.bmp");
	if (game.WindowsHowToPlay[THIRD] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.WindowsHowToPlay[FOURTH] = loadSurface("4.bmp");
	if (game.WindowsHowToPlay[FOURTH] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	game.WindowsHowToPlay[FIFTH] = loadSurface("5.bmp");
	if (game.WindowsHowToPlay[FIFTH] == NULL)
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
	for (int i = 0; i < CountOfLogos; ++i)
	{
		SDL_FreeSurface(game.Logos[i]);
		game.Logos[i] = NULL;
	}
	SDL_DestroyWindow(game.Window);
	//game.Window = NULL;
	//game.gTimeTextTexture.free();
	//game.gStartPromptTexture.free();
	//game.gPausePromptTexture.free();

	////Free global font
	//TTF_CloseFont(game.gFont);
	//game.gFont = NULL;

	////Destroy window	
	//SDL_DestroyRenderer(game.gRenderer);
	////SDL_DestroyWindow(game.gWindow);
	////game.gWindow = NULL;
	//game.gRenderer = NULL;
	SDL_Quit();
	Mix_Quit();
	//TTF_Quit();
	//IMG_Quit();
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


