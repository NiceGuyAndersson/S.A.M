#include "Display.h"
#include "Game.h"
#include "SoundManager.h"
#include "Input.h"

#define WIDTH 640;
#define HEIGHT 480;

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int _width = WIDTH;
	int _height = HEIGHT;
	Display _display(hInstance, hPrevInstance, lpCmdLine, nCmdShow, _width, _height);
	HWND _hWnd = _display.GethWnd();
	// display the window on the screen
	ShowWindow(_hWnd, nCmdShow);
	
	//Create and initialize Input
	Input _input;
	_input.Initialize(hInstance, _hWnd, _width, _height);

	//Create, initialize and START the game
	Game _Game;
	_Game.InitGame(&_input, &_display);
	WPARAM test = _Game.MainLoop();
	return test;
}