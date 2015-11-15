#ifndef _INPUT_H_
#define _INPUT_H_

#include "Project.h"

class Input
{
private:
	SDL_Event evt;

public:
	Input();

    void Update();

	bool IsMouseButtonDown(byte key);
	bool IsMouseButtonUp(byte key);
	POINT GetButtonDownCoords();

	bool IsKeyDown(byte key);
	bool IsKeyUp(byte key);
	byte GetPressedKey();

	bool IsExit();
};

#endif