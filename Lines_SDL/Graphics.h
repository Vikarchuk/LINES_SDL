#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "Project.h"

#include "Input.h"
#include "Image.h"
class Image;
class Input;


class Graphics
{
private:
	SDL_Surface* Screen;

public:
	Graphics(int width, int height);

	Image* NewImage(char* file);
	Image* NewImage(char* file, int r, int g, int b);
	bool DrawImage(Image* img, int x, int y);
	bool DrawImage(Image* img, int x, int y, int startX, int startY, int endX, int endY);
	bool Click_Animation(Image* img,int x, int y, int startX, int startY, int widthX, int heightY, int amountFrame);
	bool AnimationDeleteLine(Image* img, std::vector <std::vector <int>> coordDeleteLine, int startX, int startY, int widthX, int heightY,int amountFrame);
	bool AnimationMovingBall(Image* img, std::vector <std::vector <int>> coordMovingBall, int startX, int startY, int widthX, int heightY,int amountFrame);
	

	void Flip();
};

#endif