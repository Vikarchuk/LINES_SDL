#ifndef SCREEN_H
#define SCREEN_H

#include "Project.h"

#include "Game.h"
class Game;

class Screen
{
protected:
	Game* game;

private:
	friend class Game;
	void SetController(Game* game);

public:
	virtual void Start();
	virtual void Update();
	virtual void Destroy();
};

#endif