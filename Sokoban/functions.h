#pragma once
#include "Structures.h"
#include "Enums.h"

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void intro(Surf& game);
void menu(Surf& game, bool& quit);
void howToPlay(Surf& game, bool quit, int count = 0);
void playGame(Surf& game, bool& quit, fstream& file, fstream& fileCat);
void exit(bool& quit, Surf& game);
void createMap(Surf& game, vector<vector<int>>& array, fstream& file, bool new_level);
void field(Surf& game, vector<vector<int>> array, fstream& file, SDL_Rect posTexture);
bool characterMovement(Surf& game, Counter& counter, fstream& file, fstream& fileCat, bool& quit, bool new_level);
bool isPressed(int keyCode);
bool isReleased(int keyCode);

int playingLevel(Surf& game, Counter& counter, fstream& file, vector<vector<int>> catAndGift, vector < Texture> texture_of_elements, bool& quit, Timer& timer, bool first = false);

//void countOfStep(Surf& game, bool what, bool zero = false);
//void retry(Surface& game, bool& quit);

bool pressed_keys[7] = {};

bool stop_timer = false;


//тут был Степа
SDL_Surface* loadSurface(string path);

void Stealth()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}
void intro(Surf& game)
{
	game.init();
	game.playIntro(4, 0);
	game.loadLogos();
	bool quit = false;
	int i = 0;

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
				game.freeSurf(game.GetWallp(Wallps::LOGO_OF_GAME));
				game.freeSurf(game.GetWallp(Wallps::LOGO_OF_GROUP));
				menu(game, quit);
			}
		}
	}


}
void menu(Surf& game, bool& quit)
{
	game.playMusicInMenu(-1, 3000);
	fstream file("fields.TXT");
	fstream fileCat("position.TXT");
	SDL_Rect coords_button;
	coords_button.x = 270;
	coords_button.y = 250;
	int i_for_buttons = 0;
	int current_pressed_button = 0;
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
				//quit = true;
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
						howToPlay(game, quit);
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
			//if (quit == true)break;
		}
	}
}
void exit(bool& quit, Surf& game)
{
	game.loadExit();
	bool quit2 = false;
	SDL_Rect stretchRect;
	game.showPicWallp(game.GetWallp(MENU_EXIT));
	stretchRect.x = 160;
	stretchRect.y = 370;
	int i = 3;
	int a = 0;
	int current_pressed_button = i;

	game.showPic(game.GetPressedButton(YES), stretchRect);
	stretchRect.x += 300;
	i++;

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
						game.showPic(game.GetPressedButton(NO), stretchRect);
						stretchRect.x -= 300;
						game.showPic(game.GetButton(YES), stretchRect);
						current_pressed_button++;
					}
					break;
				case SDLK_LEFT:
					if (current_pressed_button == NO)
					{
						game.showPic(game.GetPressedButton(YES), stretchRect);
						stretchRect.x += 300;
						game.showPic(game.GetButton(NO), stretchRect);
						current_pressed_button--;
					}
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
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
	stretchRect.x = 170;
	stretchRect.y = 450;

	game.ShowOneWindowHowToPlay(FIRST);
	game.showPic(game.GetButton(BACK), stretchRect);
	stretchRect.x += 420;
	game.showPic(game.GetButton(NEXT), stretchRect);
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
				switch (game.e.key.keysym.sym)
				{
				case SDLK_RIGHT:
					count++;
					game.showPic(game.GetPressedButton(NEXT), stretchRect);
					game.playButton(3, 0);
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
					game.showPic(game.GetPressedButton(BACK), stretchRect);
					game.playButton(3, 0);
					SDL_Delay(200);
					if (!(game.showWindowHowToPlay(count)))
					{
						game.freeAfterHowToPlay();
						return;
					}
					break;
				}
				stretchRect.x = 170;
				game.showPic(game.GetButton(BACK), stretchRect);
				stretchRect.x += 420;
				game.showPic(game.GetButton(NEXT), stretchRect);
			}
			if (quit == true)break;
		}
	}
}
void playGame(Surf& game, bool& quit, fstream& file, fstream& fileCat)
{
	Counter counter;
	vector<vector<int>> level;
	counter.SetCountStep(0);
	int height = 0;
	int width = 0;
	static bool new_level = false;
	static int number_of_level = FIRST;

	if (number_of_level == FIRST)
	{
		game.loadComics();
		game.showComics();
		game.freeAfterComics();
	}
	while (number_of_level < game.infOfFild.GetCountLevels())
	{
		stop_timer = true;
		game.loadTextures();
		game.loadNumbers();
		game.showPicWallp(game.GetWindowLevel(number_of_level));
		SDL_Delay(1000);
		counter.SetCountStep(0);
		createMap(game, game.infOfFild.level, file, new_level);
		if (characterMovement(game, counter, file, fileCat, quit, new_level) == EXIT_TO_MENU)
		{
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
			game.freeAfterTextures();
			game.freeAfterNumbers();
			game.infOfFild.level.clear();
			game.infOfFild.catAndGift.clear();
			vector<vector<int>>().swap(game.infOfFild.level);
			vector<vector<int>>().swap(game.infOfFild.catAndGift);
			game.infOfFild.SetCountPlace(0);
			SDL_Delay(1000);
			if (game.infOfFild.GetResult() == WIN_WALP)
			{
				number_of_level++;
				new_level = true;
				game.showPicWallp(game.GetWallp(WIN_WALP));
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
bool win(Surf& game, vector<vector<int>> copy_catAndGift) 
{
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
	if (!first)
	{
		copy_catAndGift[copy_texture[CAT].Y][copy_texture[CAT].X] = 0;
		editCoordsMovementOfCat(copy_texture, keydown_for_cat);
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
	if (win(game, copy_catAndGift) || timer.GetCountSec() == 0 || counter.GetCountStep() == counter.GetMaxNumber())//getter
	{
		if (win(game, copy_catAndGift)) game.infOfFild.SetResult(WIN_WALP);
		else game.infOfFild.SetResult(LOSE);
		return WIN;
	}
	bool flag = false;
	while (!quit)
	{
		while (SDL_PollEvent(&game.e) != 0)
		{

			if (win(game, copy_catAndGift) || timer.GetCountSec() == 0 || counter.GetCountStep() == counter.GetMaxNumber())
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
				thread th(&Timer::timeGo, ref(timer), ref(game));
				th.detach();
				game.showPicWallp(game.GetWallp(BACKGROUND_TIME));
				field(game, game.infOfFild.level, file, copy_texture[CAT].posTexture);
				field(game, copy_catAndGift, file, copy_texture[CAT].posTexture);
				counter.printAll(game);
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
								game.showPic(game.GetTexture(CAT), copy_texture[CAT].posTexture);
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
								showAfterRecurs(game, copy_texture);
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
								game.showPic(game.GetTexture(CAT), copy_texture[CAT].posTexture);
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
								showAfterRecurs(game, copy_texture);
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
							keydown_for_cat = SDLK_UP;
							int result = playingLevel(game, counter, file, copy_catAndGift, /*level,*/ copy_texture, quit, timer);
							if (result == WIN)
								return WIN;
							else if (result == RECURSION)
								game.showPic(game.GetTexture(CAT), copy_texture[CAT].posTexture);
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
								showAfterRecurs(game, copy_texture);
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
								game.showPic(game.GetTexture(CAT), copy_texture[CAT].posTexture);
							else
								return EXIT_TO_MENU;
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
								showAfterRecurs(game, copy_texture);
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

	game.showPicWallp(game.GetWallp(BACKGROUND_TIME));
	field(game, game.infOfFild.level, file, texture_of_level[CAT].posTexture);

	createMap(game, game.infOfFild.catAndGift, fileCat, new_level);
	field(game, game.infOfFild.catAndGift, fileCat, texture_of_level[CAT].posTexture);

	game.infOfFild.SetCountPlace(0);
	for (int y = 0; y < (game.infOfFild.GetHeight()); y++)
	{
		for (int x = 0; x < (game.infOfFild.GetWidth()); x++)
		{
			if (game.infOfFild.catAndGift[y][x] == CAT)
			{
				texture_of_level[CAT].X = x;
				texture_of_level[CAT].Y = y;
			}
			if (game.infOfFild.level[y][x] == PLACEHERE)
			{
				game.infOfFild.SetCountPlace(game.infOfFild.GetCountPlace() + 1);
			}
		}
	}

	texture_of_level[CAT].posTexture.x = ((SCREEN_WIDTH / 2) - ((game.infOfFild.GetWidth()) / 2.0 * texture_of_level[CAT].sizeTexture)) + texture_of_level[CAT].X * texture_of_level[CAT].sizeTexture;
	texture_of_level[CAT].posTexture.y = ((SCREEN_HEIGHT / 2) - ((game.infOfFild.GetHeight()) / 2.0 * texture_of_level[CAT].sizeTexture)) + texture_of_level[CAT].Y * texture_of_level[CAT].sizeTexture;


	counter.printAll(game);

	if (playingLevel(game, counter, file, game.infOfFild.catAndGift, texture_of_level, quit, timer, true) == EXIT_TO_MENU)
	{
		return EXIT_TO_MENU;
	}
	else
	{
		return WIN;
	}
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

	double X = (SCREEN_WIDTH / 2) - (game.infOfFild.GetWidth() / 2.0 * sizeTexture);
	posTexture.x = X;
	posTexture.y = (SCREEN_HEIGHT / 2) - (game.infOfFild.GetHeight() / 2.0 * sizeTexture);
	for (int i = 0; i < game.infOfFild.GetHeight(); i++) {
		for (int j = 0; j < game.infOfFild.GetWidth(); j++) {
			switch (array[i][j])
			{

			case WALL:
				game.showPic(game.GetTexture(WALL), posTexture);
				break;
			case FLOOR:
				game.showPic(game.GetTexture(FLOOR), posTexture);
				break;
			case CAT:
				game.showPic(game.GetTexture(CAT), posTexture);
				break;
			case PRESENT:
				if (game.infOfFild.level[i][j] == PLACEHERE)
				{
					game.showPic(game.GetTexture(BOX_IN_PLACEHERE), posTexture);
				}
				else
				{
					game.showPic(game.GetTexture(PRESENT), posTexture);
				}
				break;
			case PLACEHERE:
				game.showPic(game.GetTexture(PLACEHERE), posTexture);
				break;
			}
			posTexture.x += sizeTexture;
		}
		posTexture.x = X;
		posTexture.y += sizeTexture;
	}

}
bool isPressed(int keyCode)
{
	return 1;
}
bool isReleased(int keyCode)
{
	return 0;
}


