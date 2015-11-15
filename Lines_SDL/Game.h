#ifndef _GAME_H_
#define _GAME_H_

#include "Project.h"

#include "Graphics.h"
class Graphics;
#include "Input.h"
class Input;
#include "Screen.h"
class Screen;

class Game
{
private:
	bool run;

	Graphics* graphics;
	Input* input;
	Screen* screen;

public:
	Game();
	
	int Execute(Screen* startscreen, int width, int height);

	Graphics* GetGraphics();
	Input* GetInput();
	Screen* GetScreen();
	void SetScreen(Screen* screen);

	void Exit();
};

#endif