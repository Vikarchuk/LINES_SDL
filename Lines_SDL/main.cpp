#include "Project.h"

// The size of the field. Beads size should be 40x40 pixels
const int N=9;
int Scale=45;
bool selectBall=false;
bool START=true;
int width=N*Scale+2;
int height=N*Scale+54;
int count_bubbles=0;
int ballWidth=40;
int ballHeight=40;
int top_margin=56;
int left_margin=6;
int score=0, countScore=0;
int currentX(0), currentY(0), previousX(0), previousY(0);




class BallScreen : public Screen
{
private:
    Input* input;
    Graphics* graphics;
	

    
    Image* back;
	Image* nxtTtr;
	Image* digits;
    (Image* ball)[7];

    
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
        // Take a Graphics object and Input and set the window title

        input = game->GetInput();
        graphics = game->GetGraphics();
        SDL_WM_SetCaption("LINES",0);
    }

    void LoadingImage()
    {
        // Load image
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
	// Filling and adding balls in the box
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
		else
		{	
			int i=0;
			while(i<3)
			{
				if(count_bubbles!=N*N)
				{
					numberColumn=rand()%9;
					numberLine=rand()%9;
					if (field[numberColumn][numberLine]==0)
					{
						field[numberColumn][numberLine]=futureAdding[i];
						count_bubbles++;
						i++;
						Coordinate.push_back(numberColumn);
						Coordinate.push_back(numberLine);
						coordAdd.push_back(Coordinate);
						Coordinate.clear();
					}
				}
				else{break;}
			}
			for(int i=0; i<3; i++)
			{
				futureAdding[i]=(rand()%7+100);
			}
		}
	}
	
	//check on line
	bool checkOnLine(int x, int y)
	{
		int rightX=x, upY=y, leftX=x, downY=y;
		int left(1), right(1), up(1), down(1), leftuUp(1), leftDown(1), rightUp(1), rightDown(1), height(0), width(0), diagonalBeginEnd(0), diagonalEndBegin(0);
		/*while(x-left!=-1&&y-up!=-1&&field[x][y]==field[x-left][y-up])
		{

		}
		while(x+right!=N&&y+down!=N&&field[x][y]==field[x+right][y+down])
		{

		}
		while(x-left!=-1&&y+down!=N&&field[x][y]==field[x-left][y+down])
		{

		}
		while(x+right!=N&&y-up!=-1&&field[x][y]==field[x+right][y-up])
		{

		}*/
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
				coordPath.clear();
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
        // Cleaning the field and concluded background
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
        // Processing end of the game

        char* message;

        switch(over)
        {
        case 1:
            message = "Желаете сыграть еще раз?";
            break;
        // If the game is not over, we return from the function
        default:
            return;
        }

        // Asks the user whether he wants to play again
        if(MessageBox(0,message,"Игра окончена",MB_YESNO) == IDYES)
            Reset();
        else
            game->Exit();
    }

	void redrawScreen()
	{
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
			//determine in which cage poked his arm
			currentX=(input->GetButtonDownCoords().x-left_margin)/Scale;
			currentY=(input->GetButtonDownCoords().y-top_margin) /Scale;
			//if no ball is not selected
			if(selectBall==false)
			{
				//if the cell is not empty
				if(field[currentX][currentY]!=0)
				{
					selectBall=true;
					createWave(currentX,currentY);
					redrawScreen();
					graphics->Click_Animation(ball[field[currentX][currentY]-100], (currentX * Scale)+left_margin, (currentY * Scale)+top_margin, 0, 0, ballWidth, ballHeight, 5);
					graphics->Flip();
					previousX=currentX;
					previousY=currentY;
				}
			}
			else
			{
				//if empty cell
				if(field[currentX][currentY]==0)
				{
					if(buildPath(previousX, previousY, currentX, currentY)==false)
					{
						//move the ball in it
						buildPath(previousX, previousY, currentX, currentY);
						redrawScreen();
						graphics->AnimationMovingBall(ball[field[previousX][previousY]-100], coordPath, 0, 0, ballWidth, ballHeight, 5);
						graphics->Flip();
						coordPath.clear();
						field[currentX][currentY]=field[previousX][previousY];
						field[previousX][previousY]=0;
						//check whether the line is not built from 5 and more balls
						checkOnLine(currentX, currentY);
						redrawScreen();
						graphics->Flip();
						//if line lined
						if(checkOnLine(currentX, currentY)==true)
						{
							count_bubbles-=countScore;
							score+=countScore;
							digitsScore[0]=score/100;
							digitsScore[1]=(score-digitsScore[0]*100)/10;
							digitsScore[2]=score-digitsScore[0]*100-digitsScore[1]*10;
							redrawScreen();
							graphics->AnimationDeleteLine(ball[field[currentX][currentY]-100], coordCheck, 7*ballWidth , 0, ballWidth, ballHeight, 10);
							graphics->Flip();
							//remove the line
							for(unsigned int i=0; i<coordCheck.size(); i++)
							{
								field[coordCheck[i][0]][coordCheck[i][1]]=0;
							}
							coordCheck.clear();
						}
						else
						{
							//add a few balls in the empty cells
							createField();
							for(unsigned int i=0; i<coordAdd.size(); i++)
							{
								//check whether the line is not built from 5 and more balls
								checkOnLine(coordAdd[i][0], coordAdd[i][1]);
								if(checkOnLine(coordAdd[i][0], coordAdd[i][1])==true)
								{
									count_bubbles-=countScore;
									score+=countScore;
									digitsScore[0]=score/100;
									digitsScore[1]=(score-digitsScore[0]*100)/10;
									digitsScore[2]=score-digitsScore[0]*100-digitsScore[1]*10;
									redrawScreen();
									graphics->AnimationDeleteLine(ball[field[coordAdd[i][0]][coordAdd[i][1]]-100], coordCheck, 7*ballWidth , 0, ballWidth, ballHeight, 10);
									graphics->Flip();
									for(unsigned int i=0; i<coordCheck.size(); i++)
									{
										field[coordCheck[i][0]][coordCheck[i][1]]=0;
									}
									coordCheck.clear();
								}
							}
							coordAdd.clear();
						}
						redrawScreen();
						graphics->Flip();
						GameOverHandle(GameOver());
						selectBall=false;
					}
				}
				else
				{
					//memorize the new position of the selected ball
					selectBall=true;
					createWave(currentX,currentY);
					redrawScreen();
					graphics->Click_Animation(ball[field[currentX][currentY]-100], (currentX * Scale)+left_margin, (currentY * Scale)+top_margin, 0, 0, ballWidth, ballHeight, 5);
					graphics->Flip();
					previousX=currentX;
					previousY=currentY;
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