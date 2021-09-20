//
//
//
//
//#include <iostream>
//#include <SDL.h>
//#include <stdio.h>
//#include <Windows.h>
//#include <string>
//#include <fstream>
////#include <sstream>
//
//
//#define SCREEN_WIDTH 800
//#define SCREEN_HEIGHT 600
//using namespace std;
////SDL_Surface* screen = NULL;
////SDL_Window* Window = NULL;
//
//enum KeyPressSurfaces
//{
//	KEY_PRESS_SURFACE_DEFAULT,
//	KEY_PRESS_SURFACE_UP,
//	KEY_PRESS_SURFACE_DOWN,
//	KEY_PRESS_SURFACE_LEFT,
//	KEY_PRESS_SURFACE_RIGHT,
//	KEY_PRESS_SURFACE_TOTAL
//};
//
//
//// Запускает SDL и создает окно 
//bool init();
//// Загружает медиа 
//bool loadMedia();
//// Освобождает носитель и закрывает SDL 
//void close();
//// Загружает отдельное изображение
//SDL_Surface* loadSurface(string path);
//void CreateArr(int**& arr, int* height, int* width);
//void Field();
//void create_arr(int**& arr, int height, int width);
//
//
//// Окно, которое мы будем визуализировать в 
//SDL_Window* Window = NULL;
//// Поверхность, содержащаяся в окне 
//SDL_Surface* ScreenSurface = NULL;
//// Изображение, которое мы загрузим и покажем на экране 
////SDL_Surface * picture = NULL;
//
//// Изображения, соответствующие нажатию клавиши(массив)
//const int CountOfLogos = 3;
//const int CountOfButtons = 3;
//const int CountOfPressedButtons = 3;
//SDL_Surface* Logos[CountOfLogos];
//SDL_Surface* Buttons[CountOfButtons];
//SDL_Surface* PressedButtons[CountOfPressedButtons];
//// Текущее отображаемое изображение
//SDL_Surface* CurrentSurface = NULL;
//
//
//
////Инициализация SDL и загрузка изображения
//int main(int argc, char* argv[])
//{
//
//	// Запускаем SDL и создаем окно 
//	if (!init()) {
//		printf("Failed to initialize!\n");
//	}
//	else {
//		if (!loadMedia())
//		{
//			printf("Failed to load media!\n");
//		}
//		else
//		{
//
//			//Флаг основного цикла
//			bool quit = false;
//
//			//Обработчик событий
//			//Структура
//			SDL_Event e;
//
//			int i = 0;
//			int i_for_buttons = 0;
//			int current_pressed_button = 0;
//			//SDL event это то, что отвечает за нажатие клавиши, кнопок-джостика и движение мишки
//			//Пока пользователь не закрыл приложение, окно работает
//			SDL_Rect stretchRect;
//			const int X = 270;
//			const int Y = 250;
//			stretchRect.x = 270;
//			stretchRect.y = 250;
//			int current_x = 270;
//			int current_y = 250;
//
//			int y_of_button1 = 270;
//			int y_of_button2 = y_of_button1 + 70;
//			int y_of_button3 = y_of_button2 + 70;
//			//stretchRect.w = SCREEN_WIDTH;
//			//stretchRect.h = SCREEN_HEIGHT;
//
//			while (!quit)
//			{
//				//Обработка событий в очереди, пока она не стала пустой
//				while (SDL_PollEvent(&e) != 0)
//				{
//					//SDL_PollEvent берет самое последнее событие 
//					//из очереди событий и помещает данные из события в SDL_Event,
//					//который мы передали в функцию.
//					//Пользовательские запросы завершаются
//					if (e.type == SDL_QUIT)
//					{
//						quit = true;
//						break;
//					}
//					else {
//						Field();
//						quit = true;
//						break;
//					}
//
//					//else if (i < CountOfLogos - 1)
//					//{
//
//					//	CurrentSurface = Logos[i];
//					//	//Применяем изображение
//					//	SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, NULL);
//					//	//Update the surface
//					//	SDL_UpdateWindowSurface(Window);
//
//					//	//Sleep(3000);
//					//	SDL_Delay(2000);
//					//	i++;
//					//}
//					//else if (i == 2)
//					//{
//					//	CurrentSurface = Logos[i];
//					//	SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, NULL);
//					//	SDL_UpdateWindowSurface(Window);
//					//	i++;
//					//}
//					//else if (i_for_buttons == 0)
//					//{
//					//	CurrentSurface = PressedButtons[i_for_buttons];
//					//	SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
//					//	stretchRect.y += 70;
//					//	SDL_UpdateWindowSurface(Window);
//					//	i_for_buttons++;
//					//}
//					//else if (i_for_buttons < CountOfButtons)
//					//{
//					//	//if (i_for_buttons == 1)stretchRect.y += 70;
//					//	CurrentSurface = Buttons[i_for_buttons];
//					//	SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
//					//	stretchRect.y += 70;
//					//	SDL_UpdateWindowSurface(Window);
//					//	i_for_buttons++;
//					//}
//					//else if (e.type == SDL_KEYDOWN)
//					//{
//
//					//	//Select surfaces based on key press
//					//	switch (e.key.keysym.sym)
//					//	{
//					//	case SDLK_UP:
//					//		//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
//
//					//		break;
//
//					//	case SDLK_DOWN:
//					//		if (current_pressed_button < 2)
//					//		{
//					//			CurrentSurface = Logos[2];
//
//					//			SDL_UpdateWindowSurface(Window);
//					//			current_pressed_button++;
//					//			if (current_pressed_button == 2)
//					//			{
//					//				CurrentSurface = Buttons[0];
//					//				stretchRect.y = Y;
//					//				SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
//					//				SDL_UpdateWindowSurface(Window);
//					//				CurrentSurface = Buttons[1];
//					//				stretchRect.y += 70;
//					//				SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
//					//				SDL_UpdateWindowSurface(Window);
//					//			}
//					//			else if (current_pressed_button == 1)
//					//			{
//					//				CurrentSurface = Buttons[0];
//					//				stretchRect.y = Y;
//					//				SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
//					//				SDL_UpdateWindowSurface(Window);
//					//				CurrentSurface = Buttons[2];
//					//				stretchRect.y += 140;
//					//				SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
//					//				SDL_UpdateWindowSurface(Window);
//					//			}
//					//			current_y += 70;
//					//			stretchRect.y = current_y;
//					//			//SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, NULL);
//					//			//SDL_UpdateWindowSurface(Window);
//					//			CurrentSurface = PressedButtons[current_pressed_button];
//					//			SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, &stretchRect);
//					//			SDL_UpdateWindowSurface(Window);
//					//			//current_pressed_button++;
//
//					//		}
//
//
//					//		//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
//					//		break;
//
//					//	default:
//					//		//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
//					//		break;
//					//	}
//					//}
//					
//
//				}
//
//
//				
//
//			}
//		}
//
//	}
//
//	close();
//	return 0;
//}
//
//void Field() {
//	int** raund;
//	int height = 0;
//	int width = 0;
//	CreateArr(raund ,&height, &width);
//}
//
//void CreateArr(int**& arr, int *height, int *width) {
//	//FILE* file;
//	fstream file ("fields.TXT");
//	//ifstream in_stream("fields.TXT");
//	if (!file.is_open())
//	{
//		std::cerr << "Error opening file!" << std::endl;
//		//More error handling code goes here
//	}
//	else {
//		string str;
//		//getline(file, str); // читает строку и переходит на новую, проблема - читаетцелую строку
//		file >> str;
//		(*height) = stoi(str);
//		file >> str;
//		(*width) = stoi(str);
//		create_arr(arr, *height, *width);
//		for (int i = 0; i < (*height); i++) {
//			for (int j = 0; j < (*width); j++) {
//				file >> str;
//				arr[i][j] = stoi(str);
//			}
//		}
//		for (int i = 0; i < (*height); i++) {
//			for (int j = 0; j < (*width); j++) {
//				cout << arr[i][j] << " ";
//			}
//			cout << endl;
//		}
//		
//	}
//
//}
//void create_arr(int**& arr, int height, int width) {
//	arr = new int* [height];
//	for (int i = 0; i < height; i++) {
//		arr[i] = new int[width];
//
//	}
//};
//void clear_memory(int**& arr, int height) {
//	for (int i = 0; i < height; i++) {
//		delete[] arr[i];
//	}
//	delete[] arr;
//	arr = nullptr;
//}
//bool init() {
//	// Флаг инициализации 
//	bool success = true;
//	// Инициализировать SDL 
//	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
//		success = false;
//	}
//	else {
//		// Создать окно 
//		Window = SDL_CreateWindow(" Book about SDL",
//			SDL_WINDOWPOS_UNDEFINED,
//			SDL_WINDOWPOS_UNDEFINED,
//			SCREEN_WIDTH, SCREEN_HEIGHT,
//			SDL_WINDOW_SHOWN);
//		if (Window == NULL) {
//			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
//			success = false;
//		}
//		else {
//			// Получить поверхность окна 
//			ScreenSurface = SDL_GetWindowSurface(Window);
//		}
//	}
//	return success;
//}
//bool loadMedia()
//{
//	//Флаг успешной загрузки
//	bool success = true;
//
//	//Лого командды
//	Logos[0] = loadSurface("teamLogo.bmp");
//	if (Logos[0] == NULL)
//	{
//		printf("Failed to load default image!\n");
//		success = false;
//	}
//
//	//Лого игры
//	Logos[1] = loadSurface("gameLogo.bmp");
//	if (Logos[1] == NULL)
//	{
//		printf("Failed to load up image!\n");
//		success = false;
//	}
//	Logos[2] = loadSurface("MainMenu.bmp");
//	if (Logos[2] == NULL)
//	{
//		printf("Failed to load up image!\n");
//		success = false;
//	}
//	Buttons[0] = loadSurface("PlayGame1.bmp");
//	if (Buttons[0] == NULL)
//	{
//		printf("Failed to load up image!\n");
//		success = false;
//	}
//	Buttons[1] = loadSurface("HowToPlay1.bmp");
//	if (Buttons[1] == NULL)
//	{
//		printf("Failed to load up image!\n");
//		success = false;
//	}
//	Buttons[2] = loadSurface("Exit1.bmp");
//	if (Buttons[2] == NULL)
//	{
//		printf("Failed to load up image!\n");
//		success = false;
//	}
//	PressedButtons[0] = loadSurface("PlayGame2.bmp");
//	if (PressedButtons[0] == NULL)
//	{
//		printf("Failed to load up image!\n");
//		success = false;
//	}
//	PressedButtons[1] = loadSurface("HowToPlay2.bmp");
//	if (PressedButtons[1] == NULL)
//	{
//		printf("Failed to load up image!\n");
//		success = false;
//	}
//	PressedButtons[2] = loadSurface("Exit2.bmp");
//	if (PressedButtons[2] == NULL)
//	{
//		printf("Failed to load up image!\n");
//		success = false;
//	}
//	return success;
//}
//void close()
//{
//	//После уничтожения окна не забудь указатели указать на NULL
//	//Освободить поверхность
//
//
//	for (int i = 0; i < CountOfLogos; ++i)
//	{
//		SDL_FreeSurface(Logos[i]);
//		Logos[i] = NULL;
//	}
//
//	//Уничтожить окно
//	SDL_DestroyWindow(Window);
//	Window = NULL;
//
//	//Выйим из подсистемы SDL
//	SDL_Quit();
//}
//
//SDL_Surface* loadSurface(std::string path)
//{
//	//Load image at specified path
//	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
//	if (loadedSurface == NULL)
//	{
//		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//	}
//
//	return loadedSurface;
//}
//
//
//
//// -  SDL_BlitSurface(picture, NULL, ScreenSurface, NULL);
////Применяем изображение (оно рисуется на заднем буфере)
////picture - изображение, которое покажем на экране
////ScreenSurface - поверхность
//
//// -  SDL_UpdateWindowSurface(Window);
//// Эта ф-ция меняет местами задний и передний буфер, таким образом у нас появляется картика
//
//// -  SDL_Delay(20000000); 
////Задерживаем изображение, чтобы оно не исчезло
