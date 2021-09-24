#pragma once
enum KeyPress
{
	//KEY_PRESS_DEFAULT,
	//KEY_PRESS_UP,
	//KEY_PRESS_DOWN,
	//KEY_PRESS_LEFT,
	//KEY_PRESS_RIGHT,
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
};
enum Buttons
{
	GAME,
	HOW_TO_PLAY,
	EXIT,
	YES,
	NO,
	NEXT,
	BACK
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
	CountOfButtons = 7,
	CountOfPressedButtons = CountOfButtons,
	CountOfTexture = 6,
	CountOfWindows = 4
};
enum WindowsInHowToPlay
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
};