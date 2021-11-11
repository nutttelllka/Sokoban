#pragma once
enum KeyPress
{
	KEY_PRESS_DEFAULT,
	KEY_PRESS_UP,
	KEY_PRESS_DOWN,
	KEY_PRESS_LEFT,
	KEY_PRESS_RIGHT,
	KEY_PRESS_LEFT_CTRL,
	KEY_PRESS_Z
};
enum Object
{
	EMPTY,
	WALL,
	FLOOR,
	CAT,
	PRESENT,
	BACKGROUND,
	PLACEHERE,
	BOX_IN_PLACEHERE, 
	//BACKGROUND_TIME
};
enum Buttons
{
	GAME,
	HOW_TO_PLAY,
	EXIT,
	YES,
	NO,
	NEXT,
	BACK,
	RETRY
};
enum Wallps
{
	LOGO_OF_GROUP,
	LOGO_OF_GAME,
	MAIN_MENU,
	MENU_EXIT,
	WIN_WALP,
	LOSE,
	BLACK,
	BACKGROUND_TIME
};
enum CountOdArrs
{
	CountOfWallps = 8,
	CountOfButtons = 8,
	CountOfPressedButtons = CountOfButtons,
	CountOfTexture = 8,
	CountOfWindows = 6,
	CountOfNumbers = 12,
	CountOfLeveles = 5,
	CountOfComic = 4
	//CountOfWindowsHowToPlay = 5

};
enum SomeWindows
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH,
	SIXTH
};
enum ReturningValues
{
	EXIT_TO_MENU,
	WIN,
	RECURSION, 
	
};
enum Surfaces
{
    WALLPS,
	BUTTONS,
	PRESSED_BUTTONS,
	TEXTURES,
	WINDOWS, 
	NUMBERS,
	LEVELES,
	COMIC
};
enum Music
{
	INTRO,
	MENU,
	SOUND_GAME,
	BOX,
	BUTTON
};