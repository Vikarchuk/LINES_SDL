#include "Graphics.h"

Graphics::Graphics(int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Screen = SDL_SetVideoMode(width,height,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
}

Image* Graphics::NewImage(char* file)
{
	Image* image = new Image();
	image->surf = SDL_DisplayFormat(SDL_LoadBMP(file));

	return image;
}

Image* Graphics::NewImage(char* file, int r, int g, int b)
{
	Image* image = new Image();
	image->surf = SDL_DisplayFormat(SDL_LoadBMP(file));

	SDL_SetColorKey(image->surf, SDL_SRCCOLORKEY | SDL_RLEACCEL,
		SDL_MapRGB(image->surf->format, r, g, b));

	return image;
}

bool Graphics::DrawImage(Image* img, int x, int y)
{
	if(Screen == NULL || img->surf == NULL)
        return false;
 
    SDL_Rect Area;
    Area.x = x;
    Area.y = y;
 
    SDL_BlitSurface(img->surf, NULL, Screen, &Area);
 
	return true;
}

bool Graphics::DrawImage(Image* img, int x, int y, int startX, int startY, int endX, int endY)
{
	if(Screen == NULL || img->surf == NULL)
        return false;
 
    SDL_Rect Area;
    Area.x = x;
    Area.y = y;

    SDL_Rect SrcArea;
	SrcArea.x = startX;
	SrcArea.y = startY;
	SrcArea.w = endX;
	SrcArea.h = endY;

	SDL_BlitSurface(img->surf, &SrcArea, Screen, &Area);

	return true;
}

bool Graphics::Click_Animation(Image* img,int x, int y, int startX, int startY, int widthX, int heightY,int amountFrame)
{
	int currentFrame=0;
	if(Screen ==NULL|| img->surf==NULL)
		return false;
	
	SDL_Rect Area;
	Area.x=x;
	Area.y=y;
	SDL_Rect* SrcArea=new SDL_Rect[amountFrame];
	
	for(int i=0; i<amountFrame; i++)
	{
		SrcArea[i].x=startX+i*widthX;
		SrcArea[i].y=startY;
		SrcArea[i].w=widthX;
		SrcArea[i].h=heightY;
	}

	for(int i=0; i<=amountFrame;i++)
	{ 
		if (currentFrame==amountFrame)
		{
			SDL_BlitSurface(img->surf, &SrcArea[0], Screen, &Area);
			break;
		}
		SDL_BlitSurface(img->surf, &SrcArea[currentFrame], Screen, &Area);
		SDL_Flip(Screen);
		currentFrame++;
		SDL_Delay(100);
    }
	return true;
}

bool Graphics::AnimationDeleteLine(Image* img, vector <vector <int>> coordDeleteLine, int startX, int startY, int widthX, int heightY,int amountFrame)
{
	int currentFrame=0;
	int size=coordDeleteLine.size();
	if(Screen ==NULL|| img->surf==NULL)
		return false;
	SDL_Rect* Area=new SDL_Rect[size];
	for(int i=0; i<size; i++)
	{
		Area[i].x=coordDeleteLine[i][0]*45+6;
		Area[i].y=coordDeleteLine[i][1]*45+56;
		Area[i].w=widthX;
		Area[i].h=heightY;
	}
	SDL_Rect* SrcArea=new SDL_Rect[amountFrame];
	for(int i=0; i<amountFrame; i++)
	{
		SrcArea[i].x=startX+i*widthX;
		SrcArea[i].y=startY;
		SrcArea[i].w=widthX;
		SrcArea[i].h=heightY;
	}
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<amountFrame; j++)
		{
			if (currentFrame==amountFrame)
			{
				SDL_BlitSurface(img->surf, &SrcArea[j], Screen, &Area[i]);
				break;
			}
			SDL_BlitSurface(img->surf, &SrcArea[j],Screen, &Area[currentFrame]);
			SDL_Flip(Screen);
			currentFrame++;
			SDL_Delay(100);
		}
	}
	return true;
}

bool Graphics::AnimationMovingBall(Image* img, vector <vector <int>> coordMovingBall, int startX, int startY, int widthX, int heightY,int amountFrame)
{
	int currentFrame=0;
	int size=(coordMovingBall.size())/2;
	if(Screen ==NULL|| img->surf==NULL)
		return false;
	SDL_Rect* Area=new SDL_Rect[size];
	for(int i=0; i<size; i++)
	{
		Area[i].x=coordMovingBall[size-1-i][0]*45+6;
		Area[i].y=coordMovingBall[size-1-i][1]*45+56;
		Area[i].w=widthX;
		Area[i].h=heightY;
	}
	SDL_Rect* SrcArea=new SDL_Rect[amountFrame+1];
	for(int i=0; i<amountFrame; i++)
	{
		SrcArea[i].x=startX+i*widthX;
		SrcArea[i].y=startY;
		SrcArea[i].w=widthX;
		SrcArea[i].h=heightY;
	}
	SrcArea[amountFrame].x=21*widthX;
	SrcArea[amountFrame].y=startY;
	SrcArea[amountFrame].w=widthX;
	SrcArea[amountFrame].h=heightY;

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<amountFrame; j++)
		{
			if (j==amountFrame-1)
			{
				SDL_BlitSurface(img->surf, &SrcArea[amountFrame], Screen, &Area[i]);
				break;
			}
			SDL_BlitSurface(img->surf, &SrcArea[j],Screen, &Area[i]);
			SDL_Flip(Screen);
			currentFrame++;
			SDL_Delay(100);
		}
		SDL_BlitSurface(img->surf, &SrcArea[amountFrame],Screen, &Area[i]);
		SDL_Flip(Screen);
	}
	return true;
}


void Graphics::Flip()
{
	SDL_Flip(Screen);
	SDL_FillRect(Screen,NULL, 0x000000);
}