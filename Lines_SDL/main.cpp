#include "Project.h"

// Размер поля. Размер шариков должен быть 40x40 пикселей
const int N=9;
int Scale=45;
bool selectBall=false;
bool animationRun=false;
bool START=true;
int width=N*Scale+2;
int height=N*Scale+54;
int x(0),y(0);
int count_bubbles=0;
int ballWidth=40;
int ballHeight=40;
int top_margin=56;
int left_margin=6;
int score=0, countScore=0;




class BallScreen : public Screen
{
private:
    Input* input;
    Graphics* graphics;
	

    // Изображения фона и шариков 
    Image* back;
	Image* nxtTtr;
	Image* digits;
    (Image* ball)[7];

    // Массив, обозначающий поле
    int field[N][N];
	int workField[N][N];
	int futureAdding[3];
	int digitsScore[3];
	vector<vector<int>> coordPath;
	vector<vector<int>> coordCheck;
	vector<vector<int>> coordAdd;
	vector<int> Coordinate;
	

	void StartSettings()
    {
        // Берем объекты Graphics и Input и устанавливаем заголовок окна

        input = game->GetInput();
        graphics = game->GetGraphics();
        SDL_WM_SetCaption("LINES",0);
    }

    void LoadingImage()
    {
        // Загрузка изображений
		back = graphics->NewImage("data/BKG.bmp");
		nxtTtr = graphics->NewImage("data/NEXT.bmp");
		digits = graphics->NewImage("data/DIGITS.bmp");
		ball[0] = graphics->NewImage("data/BALLS1.bmp",255,255,255);
        ball[1] = graphics->NewImage("data/BALLS2.bmp",255,255,255);
		ball[2] = graphics->NewImage("data/BALLS3.bmp",255,255,255);
        ball[3] = graphics->NewImage("data/BALLS4.bmp",255,255,255);
        ball[4] = graphics->NewImage("data/BALLS5.bmp",255,255,255);
		ball[5] = graphics->NewImage("data/BALLS6.bmp",255,255,255);
		ball[6] = graphics->NewImage("data/BALLS7.bmp",255,255,255);
    }
	// Заполнение и добавление шариков в поле
	void createField()
	{		
		int numberColumn(0), numberLine(0);
		if (START==true)
		{
			for(int i=0; i<5; i++)
			{
				numberColumn=rand()%9;
				numberLine=rand()%9;
				if(field[numberColumn][numberLine]==0)
				{
					field[numberColumn][numberLine]=(rand()%7+100);
					count_bubbles++;
				}
			}
			for(int i=0; i<3; i++)
			{
				futureAdding[i]=(rand()%7+100);
			}
			START=false;
		}
		else if(score==0&&count_bubbles==N*N-2)
		{
			int i=0;
			while(i<2)
			{
				numberColumn=rand()%9;
				numberLine=rand()%9;
				if(field[numberColumn][numberLine]==0)
				{
					field[numberColumn][numberLine]=futureAdding[i];
					/*Coordinate.push_back(numberColumn);
					Coordinate.push_back(numberLine);
					coordAdd.push_back(Coordinate);
					Coordinate.clear();*/
					count_bubbles++;
					i++;
				}
			}
		}
		else if(score!=0&&count_bubbles==N*N-1)
		{
			while(1)
			{
				numberColumn=rand()%9;
				numberLine=rand()%9;
				if(field[numberColumn][numberLine]==0)
				{
					field[numberColumn][numberLine]=futureAdding[0];
					/*Coordinate.push_back(numberColumn);
					Coordinate.push_back(numberLine);
					coordAdd.push_back(Coordinate);
					Coordinate.clear();*/
					count_bubbles++;
				}

			}
		}
		else
		{	
			int i=0;
			while(i<3)
			{
				numberColumn=rand()%9;
				numberLine=rand()%9;
				if (field[numberColumn][numberLine]==0)
				{
					field[numberColumn][numberLine]=futureAdding[i];
					/*Coordinate.push_back(numberColumn);
					Coordinate.push_back(numberLine);
					coordAdd.push_back(Coordinate);
					Coordinate.clear();*/
					count_bubbles++;
					i++;
				}
			}
			for(int i=0; i<3; i++)
			{
				futureAdding[i]=(rand()%7+100);
			}
		}
	}
	
	//Проверка на линию
	bool checkOnLine(int x, int y)
	{
		int rightX=x, upY=y, leftX=x, downY=y;
		int left(1), right(1), up(1), down(1), height(0), width(0);
		while(x-left!=-1&&field[x][y]==field[x-left][y])
		{
			leftX=x-left;
			left++;
		}
		while(x+right!=N&&field[x][y]==field[x+right][y])
		{
			rightX=x+right;
			right++;
		}
		while(y-down!=-1&&field[x][y]==field[x][y-down])
		{
			downY=y-down;
			down++;
		}
		while(y+up!=N&&field[x][y]==field[x][y+up])
		{
			upY=y+up;
			up++;
		}
		width=left+right-1;
		height=down+up-1;

		if(width>=5)
		{
			while(leftX<=rightX)
			{
				
				Coordinate.push_back(rightX);
				Coordinate.push_back(y);
				coordCheck.push_back(Coordinate);
				Coordinate.clear();
				rightX--;
			}
			countScore=width;
			return true;
		}
		if(height>=5)
		{
			while(downY<=upY)
			{
				Coordinate.push_back(x);
				Coordinate.push_back(upY);
				coordCheck.push_back(Coordinate);
				Coordinate.clear();
				upY--;
			}
			countScore=height;
			
			return true;
		}
		return false;
	}
	
	void createWave(int startX, int startY)
	{
		
		for(int i=0;i<N; i++)
		{
			for(int j=0; j<N; j++)
			{
				if(field[i][j]==0)
				{
					workField[i][j]=N*N+1;
				}
				else
				{
					workField[i][j]=N*N+2;
				}
				if(i==startX&&j==startY)
				{
					workField[i][j]=0;
				}
			}
		}
		// start wave
		int iter=0;
		int iterK=N*N;// max amount of iteration
		while(iter<iterK)
		{
			for(int i=0; i<N; i++)
			{
				for(int j=0; j<N; j++)
				{
					if(workField[i][j]==iter)
					{
						//top side----------------------------------------------------
						if(workField[i-1][j]==N*N+1&&i>0)
						{
							workField[i-1][j]=iter+1;
						}
						
						//bottom side---------------------------------------------------
						
						if(workField[i+1][j]==N*N+1&&i<(N-1))
						{
							workField[i+1][j]=iter+1;
						}
						
						//left side--------------------------------------------------------------
						if(workField[i][j-1]==N*N+1&&j>0)
						{
							workField[i][j-1]=iter+1;
						}
						
						//right side--------------------------------------------------------------------------
						if(workField[i][j+1]==N*N+1&&j<(N-1))
						{
							workField[i][j+1]=iter+1;
						}
					}
					
				}
			}
			iter++;
		}
	}
	//building path------------------------------------------------------------------------------------------------
	bool buildPath(int startX, int startY, int targetX, int targetY)
	{
		bool find=0;
		if(startX==targetX&&startY==targetY)
		{
			return false;
		}
		
		//-------------build path--------------------------------------
		int duplStartX(targetX), duplStartY(targetY), moveX(0), moveY(0);
		int minNum(N*N+2);
		while(1)//targetX==startX&&targetY==startY
		{
			if(moveX==startX&&moveY==startY)
			{
				break;
			}
			if(workField[duplStartX+1][duplStartY]<minNum&&duplStartX<(N-1))
			{
				minNum=workField[duplStartX+1][duplStartY];
				moveX=duplStartX+1;
				moveY=duplStartY;
				find=true;
			}
			if(workField[duplStartX-1][duplStartY]<minNum&&duplStartX>0)
			{
				minNum=workField[duplStartX-1][duplStartY];
				moveX=duplStartX-1;
				moveY=duplStartY;
				find=true;
			}
			if(workField[duplStartX][duplStartY+1]<minNum&&duplStartY<(N-1))
			{
				minNum=workField[duplStartX][duplStartY+1];
				moveX=duplStartX;
				moveY=duplStartY+1;
				find=true;
			}
			if(workField[duplStartX][duplStartY-1]<minNum&&duplStartY>0)
			{
				minNum=workField[duplStartX][duplStartY-1];
				moveX=duplStartX;
				moveY=duplStartY-1;
				find=true;
			}
			
			Coordinate.push_back(moveX);
			Coordinate.push_back(moveY);
			coordPath.push_back(Coordinate);
			Coordinate.clear();
			duplStartX=moveX;
			duplStartY=moveY;
			
			if(find==false)
			{
				return true;
			}
			find=false;
			
		}
		Coordinate.push_back(targetX);
		Coordinate.push_back(targetY);
		coordPath.push_back(Coordinate);
		Coordinate.clear();
		return false;
	}
	
	void Reset()
    {
        // Очистка поля и вывод фона
		if(GameOver()==false)
		{
			for(int i = 0; i < N; i++)
			{
				for(int j = 0; j < N; j++)
				{field[i][j] = 0;}
			}
			for(int i=0; i<3; i++)
			{
				digitsScore[i]=0;
			}
		}
		createField();
		graphics->DrawImage(back,0,0);
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
			{
				if(field[i][j]!=0)
				{
					graphics->DrawImage(ball[field[i][j]-100], (i * Scale)+left_margin, (j * Scale)+top_margin, 0, 0, ballWidth, ballHeight);
				}
			}
		}
		for(int i=0; i<3; i++)
		{
			graphics->DrawImage(nxtTtr, (Scale*3+left_margin)+Scale*i+5, 20, (futureAdding[i]-100)*25, 0, 25, 25);
		}
		for(int i=0; i<3; i++)
		{
			graphics->DrawImage(digits, 7*Scale+left_margin+i*24, left_margin, digitsScore[i]*18, 0, 18, 35);
		}
		graphics->Flip();
		GameOverHandle(GameOver());
    }

    bool GameOver()
    {
		if (count_bubbles>=N*N-1)
		{
			count_bubbles=0;
			score=0;
			START=true;
			return true;
		}
		return false;
    }

    void GameOverHandle(bool over)
    {
        // Обработка конца игры

        char* message;

        switch(over)
        {
        case 1:
            message = "Желаете сыграть еще раз?";
            break;
        // Если игра не окончена, возвращаемся из функции
        default:
            return;
        }

        // Спрашиваем пользователя, хочет ли он сыграть еще раз
        if(MessageBox(0,message,"Игра окончена",MB_YESNO) == IDYES)
            Reset();
        else
            game->Exit();
    }

public:
	void Start()
    {
        StartSettings();
        LoadingImage();
        Reset();
    }

    void Update()
    {
        if(input->IsExit())
            game->Exit();
		// if left mouse button press---------------------------------------
		if(input->IsMouseButtonDown(1))
		{
			// if ball select------------------------------------------------------------
			if(selectBall)
			{
				// if select other ball-----------------------------------------------------------------------------------------
				if(field[(input->GetButtonDownCoords().x-left_margin)/Scale][(input->GetButtonDownCoords().y-top_margin)/Scale]!=0)
				{
					x=(input->GetButtonDownCoords().x-left_margin)/Scale;// remember coordinate Х in array field
					y=(input->GetButtonDownCoords().y-top_margin) /Scale;// remember coordinate У in array field
					createWave(x,y);// create wave
					// redraw 
					graphics->DrawImage(back,0,0);
					for(int i=0; i<3; i++)
					{
						graphics->DrawImage(nxtTtr, (Scale*3+left_margin)+Scale*i+5, 20, (futureAdding[i]-100)*25, 0, 25, 25);
					}
					for(int i = 0; i < N; i++)
					{
						for(int j = 0; j < N; j++)
						{
							if(field[i][j] != 0)
							{
								graphics->DrawImage(ball[field[i][j]-100], (i * Scale)+left_margin, (j * Scale)+top_margin, 0, 0, ballWidth, ballHeight);
							}
						}
					}
					for(int i=0; i<3; i++)
					{
						graphics->DrawImage(digits, 7*Scale+left_margin+i*24, left_margin, digitsScore[i]*18, 0, 18, 35);
					}
					graphics->Click_Animation(ball[field[x][y]-100], (x * Scale)+left_margin, (y * Scale)+top_margin, 0, 0, ballWidth, ballHeight, 5);
					graphics->Flip();
					animationRun=true;
				}
				// 
				else
				{
					//функция проверки пути
					buildPath(x, y, (input->GetButtonDownCoords().x-left_margin)/Scale, (input->GetButtonDownCoords().y-top_margin)/Scale);
					if(buildPath(x, y, (input->GetButtonDownCoords().x-left_margin)/Scale, (input->GetButtonDownCoords().y-top_margin)/Scale)==false)
					{
						//анимация перемещения с (х,у) в точку((input->GetButtonDownCoords().x-left_margin)/Scale,  (input->GetButtonDownCoords().y-top_margin)/Scale)
						graphics->DrawImage(back,0,0);
						for(int i=0; i<3; i++)
						{
							graphics->DrawImage(nxtTtr, (Scale*3+left_margin)+Scale*i+5, 20, (futureAdding[i]-100)*25, 0, 25, 25);
						}
						for(int i = 0; i < N; i++)
						{
							for(int j = 0; j < N; j++)
							{
								if(field[i][j] != 0)
								{
									graphics->DrawImage(ball[field[i][j]-100], (i * Scale)+left_margin, (j * Scale)+top_margin, 0, 0, ballWidth, ballHeight);
								}
							}
						}
						for(int i=0; i<3; i++)
						{
							graphics->DrawImage(digits, 7*Scale+left_margin+i*24, left_margin, digitsScore[i]*18, 0, 18, 35);
						}
						graphics->AnimationMovingBall(ball[field[x][y]-100], coordPath, 0, 0, ballWidth, ballHeight, 5);
						graphics->Flip();
						coordPath.clear();
						//функция проверки на линию(если линия, то анимация сгорания; если нет добавление 3 шариков)
						field[(input->GetButtonDownCoords().x-left_margin)/Scale][(input->GetButtonDownCoords().y-top_margin)/Scale]=field[x][y];
						checkOnLine((input->GetButtonDownCoords().x-left_margin)/Scale, (input->GetButtonDownCoords().y-top_margin)/Scale);
						field[x][y]=0;
						if(checkOnLine((input->GetButtonDownCoords().x-left_margin)/Scale,(input->GetButtonDownCoords().y-top_margin)/Scale)==true)
						{
							count_bubbles-=countScore;
							score+=countScore;
							digitsScore[0]=score/100;
							digitsScore[1]=(score-digitsScore[0]*100)/10;
							digitsScore[2]=score-digitsScore[0]*100-digitsScore[1]*10;
							graphics->DrawImage(back,0,0);
							for(int i=0; i<3; i++)
							{
								graphics->DrawImage(nxtTtr, (Scale*3+left_margin)+Scale*i+5, 20, (futureAdding[i]-100)*25, 0, 25, 25);
							}
							for(int i = 0; i < N; i++)
							{
								for(int j = 0; j < N; j++)
								{
									if(field[i][j] != 0)
									{
										graphics->DrawImage(ball[field[i][j]-100], (i * Scale)+left_margin, (j * Scale)+top_margin, 0, 0, ballWidth, ballHeight);
									}
								}
							}
							for(int i=0; i<3; i++)
							{
								graphics->DrawImage(digits, 7*Scale+left_margin+i*24, left_margin, digitsScore[i]*18, 0, 18, 35);
							}
							graphics->AnimationDeleteLine(ball[field[(input->GetButtonDownCoords().x-left_margin)/Scale][(input->GetButtonDownCoords().y-top_margin)/Scale]-100], coordCheck, 6*ballWidth , 0, ballWidth, ballHeight, 11);
							graphics->Flip();
							for(int i=0; i<coordCheck.size(); i++)
							{
								field[coordCheck[i][0]][coordCheck[i][1]]=0;
							}
						}
						else
						{
							createField();
						}
						coordCheck.clear();// clear vector
						graphics->DrawImage(back,0,0);
						for(int i=0; i<3; i++)
						{
							graphics->DrawImage(nxtTtr, (Scale*3+left_margin)+Scale*i+5, 20, (futureAdding[i]-100)*25, 0, 25, 25);
						}
						for(int i = 0; i < N; i++)
						{
							for(int j = 0; j < N; j++)
							{
								if(field[i][j] != 0)
								{
									graphics->DrawImage(ball[field[i][j]-100], (i * Scale)+left_margin, (j * Scale)+top_margin, 0, 0, ballWidth, ballHeight);
								}
							}
						}
						for(int i=0; i<3; i++)
						{
							graphics->DrawImage(digits, 7*Scale+left_margin+i*24, left_margin, digitsScore[i]*18, 0, 18, 35);
						}
						selectBall=false;
						animationRun=false;
						graphics->Flip();
						GameOverHandle(GameOver());
					}
					else
					{
						selectBall=false;
						animationRun=false;
					}
				}//else
			}
			// если ничего не выбрано
			else
			{
				if(field[(input->GetButtonDownCoords().x-left_margin)/Scale][(input->GetButtonDownCoords().y-top_margin)/Scale]!=0)
				{
					x=(input->GetButtonDownCoords().x-left_margin)/Scale;// запоминаем координату Х в масиве field
					y=(input->GetButtonDownCoords().y-top_margin)/Scale;// запоминаем координату У в масиве field
					createWave(x,y);// пускаем волну с точки (х, у)
					//------------------------
					graphics->DrawImage(back,0,0);
					for(int i=0; i<3; i++)
					{
						graphics->DrawImage(nxtTtr, (Scale*3+left_margin)+Scale*i+5, 20, (futureAdding[i]-100)*25, 0, 25, 25);
					}
					for(int i = 0; i < N; i++)
					{
						for(int j = 0; j < N; j++)
						{
							if(field[i][j] != 0)
							{
								graphics->DrawImage(ball[field[i][j]-100], (i * Scale)+left_margin, (j * Scale)+top_margin, 0, 0, ballWidth, ballHeight);
							}
						}
					}
					for(int i=0; i<3; i++)
					{
						graphics->DrawImage(digits, 7*Scale+left_margin+i*24, left_margin, digitsScore[i]*18, 0, 18, 35);
					}
					graphics->Click_Animation(ball[field[x][y]-100], (x * Scale)+left_margin, (y * Scale)+top_margin, 0, 0, ballWidth, ballHeight, 5);
					graphics->Flip();
				
					//---------------------------------
					selectBall=true;
					animationRun=true;
					GameOverHandle(GameOver());
				}
			}
		}
	}
};

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	srand((unsigned)time(NULL));
	

    Game game;
	return game.Execute(new BallScreen(),width,height);
}