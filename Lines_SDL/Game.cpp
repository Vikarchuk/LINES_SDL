#include "Game.h"

Game::Game()
{
	run = true;
}

int Game::Execute(Screen* startscreen, int width, int height)
{
	graphics = new Graphics(width,height);
	input = new Input();
	screen = startscreen;

	screen->SetController(this);
	this->screen->Start();

	while(run)
	{
		input->Update();
		screen->Update();
	}

	screen->Destroy();
	
	delete graphics;
	delete input;
	delete screen;

	SDL_Quit();
	return 0;
}

Graphics* Game::GetGraphics()
{
	return graphics;
}

Input* Game::GetInput()
{
	return input;
}

Screen* Game::GetScreen()
{
	return screen;
}
	
void Game::SetScreen(Screen* screen)
{
	this->screen->Destroy();
	delete this->screen;
	this->screen = screen;
	this->screen->SetController(this);
	this->screen->Start();
}

void Game::Exit()
{
	run = false;
}