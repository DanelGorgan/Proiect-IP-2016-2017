#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

ifstream fin("highscore.txt");
ofstream fout("highscore.txt");



bool gameOver;
bool gameOn = true;
char choice, choice1;
int width;
int height;
int score;
int ghost, bonus, cut, slow, fast;
int highscore[100],pos;
int miliseconds, seconds, minutes, hours;
enum eDirection {STOP=0, LEFT,RIGHT,UP,DOWN};
eDirection dir;

struct Snake
{
    int x, y;
} snake;

struct Fruit
{
    int x, y;
} fruit;

struct Tail
{
    int x[100];
    int y[100];
    int lenght;
} tail;

struct PowerUp
{
    int x,y;
    float bonus, ghost, cut, slow, fast;
} powerUp;

void clear_screen ()
{
    COORD coord = {0};
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    SetConsoleCursorPosition ( h, coord );
}

timer ()
{
    if (miliseconds==10)
    {
        ++seconds;
        miliseconds=0;
    }
    if (seconds==60)
    {
        ++minutes;
        seconds=0;
    }
    if (minutes==60)
    {
        ++hours;
        minutes=0;
    }
    miliseconds++;
}
void InitGame()
{
    seconds=0;
    minutes=0;
    hours=0;
    gameOver=false;
    score=0;
    width=60;
    height=36;
    snake.x= width /2 ;
    snake.y= height / 2;
    fruit.x=rand()%width;
    fruit.y=rand()%height;
    powerUp.x=100;
    powerUp.y=100;
    tail.lenght=0;
    dir=STOP;
}
void Board (int x, int y)
{
    if (x==6 && y==width-1)
    {
        cout<<"    Powerup: ";
        if (ghost) cout<<"GHOST";
        else if (bonus) cout<<"BONUS";
        else if (cut) cout<<"CUT";
        else if (slow) cout<<"SLOW";
        else if (fast) cout<<"FAST";
        else cout<<"NONE";
    }
    if (x==7 && y==width-1) cout<<"    SCORE: "<<score;
}

void Draw()
{
    int i, j;

    clear_screen();

    for (i=0; i<width+2; i++)
        cout<<"#";
    cout<<endl;

    for(i =0 ; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            if(j==0)
                cout<<"#";
            if (i==snake.y && j==snake.x)
                cout<<"O";
            else if (i==fruit.y && j==fruit.x)
                cout<<"F";
            else if (i==powerUp.y && j==powerUp.x)
                cout<<"@";
            else
            {
                bool ok=false;
                for (int k=0; k<tail.lenght; k++)
                {
                    if (tail.x[k]==j && tail.y[k]==i)
                    {
                        cout<<"o";
                        ok=true;
                    }
                }
                if (ok==false) cout<<" ";
            }
            if(j==width-1)
                cout<<"#";
            Board(i, j);
        }
        cout<<endl;
    }

    for (i=0; i<width+2; i++)
        cout<<"#";
    cout<<endl;

}

void Input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'a':
            if (dir!=RIGHT)
                dir=LEFT;
            break;
        case 'd':
            if (dir!=LEFT)
                dir=RIGHT;
            break;
        case 's':
            if(dir!=UP)
                dir=DOWN;
            break;
        case 'w':
            if(dir!=DOWN)
                dir=UP;
            break;
        case 'p':
            system("pause");
            break;
        case 'x':
            gameOver=true;
            break;
        }
    }
}

void Logic()
{
    int prevX=tail.x[0];
    int prevY=tail.y[0];
    int prevX1, prevY1;
    tail.x[0]=snake.x;
    tail.y[0]=snake.y;
    for (int i=1; i<tail.lenght; i++)
    {
        prevX1=tail.x[i];
        prevY1=tail.y[i];
        tail.x[i]=prevX;
        tail.y[i]=prevY;
        prevY=prevY1;
        prevX=prevX1;
    }

    switch(dir)
    {
    case LEFT:
        snake.x--;
        break;
    case RIGHT:
        snake.x++;
        break;
    case UP:
        snake.y--;
        break;
    case DOWN:
        snake.y++;
        break;
    }

    if (ghost==0)
        if(snake.x>width-2 || snake.x<0 || snake.y>height-1 || snake.y <0)
            gameOver=true;
    if (ghost==1)
    {
        if (snake.x>=width-1) snake.x=0;
        else if (snake.x<0) snake.x=width-2;
        if (snake.y>=height) snake.y=0;
        else if (snake.y<0) snake.y=height-1;
    }

    if (ghost==0)
        for (int i=0; i<tail.lenght; i++)
            if (tail.x[i]==snake.x && tail.y[i]==snake.y)
                gameOver=1;

    if(snake.x==fruit.x && snake.y==fruit.y)
    {
        tail.lenght++;
        if (bonus==1)
            score+=50;
        else score+=10;
        fruit.x=rand()%width;
        fruit.y=rand()%height;
    }
    if (seconds==30 && miliseconds==5 || seconds==0 && miliseconds==5 && minutes>0)
    {
        Sleep(0);
        bonus=ghost=cut=fast=slow=0;
        powerUp.x=rand()%width;
        powerUp.y=rand()%height;
        powerUp.bonus=rand()%5;
        powerUp.ghost=rand()%5;
        powerUp.cut=rand()%5;
        powerUp.slow=rand()%5;
        powerUp.fast=rand()%5;
    }
    else if (seconds==15 || seconds==45)
    {
        powerUp.x=100;
        powerUp.y=100;

    }

    if(snake.x==powerUp.x && snake.y==powerUp.y)
    {
        tail.lenght++;
        if (powerUp.bonus==1)
            bonus=1;
        else if (powerUp.ghost==1)
            ghost=1;
        else if (powerUp.cut==1)
            cut=1;
        else if (powerUp.fast==1)
            fast=1;
        else slow=1;
        if (cut==1)
            if (tail.lenght<5) tail.lenght=0;
            else
                tail.lenght= tail.lenght-5;
        powerUp.x=100;
        powerUp.y=100;
        powerUp.bonus=rand()%5;
        powerUp.ghost=rand()%5;
        powerUp.cut=rand()%5;
        powerUp.slow=rand()%5;
        powerUp.fast=rand()%5;
    }
}

void HighScore( int score)
{
    if(score!=0)
    {
        highscore[++pos]=score;
        for(int i=1; i<pos; i++)
            for(int j=i+1; j<=pos; j++)
                if(highscore[i]<highscore[j])
                {
                    int aux=highscore[i];
                    highscore[i]=highscore[j];
                    highscore[j]=aux;
                }

        for(int i=1; i<=5; i++)
        {
            fout<<i<<" "<<highscore[i];
            fin>>i>>highscore[i];
            fout<<endl;
        }
    }
}


int main()
{
    while (gameOn != false)
    {
        cout << "                                SNAKE GAME                                     \n";
        cout << "                                                          by TwinsG            \n";
        cout << "*******************************************************************************\n";
        cout << "                            1 - Game Modes\n";
        cout << "                            2 - Highscore.\n";
        cout << "                            3 - Help.\n";
        cout << "                            4 - Exit.\n";
        cout << "*******************************************************************************\n";
        cout << " Enter your choice and press return: ";

        cin >> choice;
        cout<<'\n';
        switch (choice)
        {
        case '1':
            system("cls");
            cout << "                                SNAKE GAME                                     \n";
            cout << "                                                          by TwinsG            \n";
            cout << "*******************************************************************************\n";
            cout<<" 1 - Single Player\n";
            cout<<" 2 - Player vs AI\n\n\n";
            cout << "*******************************************************************************\n";
            cout<<" Enter your choice and press return: ";
            cin>>choice1;
            if (choice1=='1')
            {
                InitGame();
                system("cls");
                while(!gameOver)
                {
                    timer();
                    Draw();
                    Input();
                    Logic();
                    if (slow==1)Sleep(100);
                    else if (fast==1) Sleep(0);
                    else if (slow==0 && fast==0) Sleep(50);
                }

                system("cls");
                cout<<"GAME OVER!"<<endl;
                HighScore(score);
                gameOver=false;
                system("pause");
                system("cls");
            }
            else if (choice1=='2')
            {
            system("cls");
            cout << "                                SNAKE GAME                                     \n";
            cout << "                                                          by TwinsG            \n";
            cout << "*******************************************************************************\n";
            cout<<" THIS GAME MODE WILL BE AVAILABLE SOON\n\n\n\n";
            cout << "*******************************************************************************\n";
            system("pause");
            system("cls");
            }
            else system("cls");
            break;
        case '2':
            system("cls");cout << "                                SNAKE GAME                                     \n";
            cout << "                                                          by TwinsG            \n";
            cout << "*******************************************************************************\n";
             for(int i=1; i<=5; i++)
            {
                cout<<i<<". "<<highscore[i]<<" ";
                cout<<endl;
            }
            cout << "*******************************************************************************\n";
            system("pause");
            system("cls");
            break;
        case '3':
            system("cls");
             cout << "                                SNAKE GAME                                     \n";
            cout << "                                                          by TwinsG            \n";
            cout << "*******************************************************************************\n";
            cout << "No help, It's the classic snake game...\n";
            cout << "We will write later the description of the game, the powerUps etc. \n\n\n";
            cout << "*******************************************************************************\n";
            cout<<endl;
            system("pause");
            system("cls");
            break;
        case '4':
            system("cls");
             cout << "                                SNAKE GAME                                     \n";
            cout << "                                                          by TwinsG            \n";
            cout << "*******************************************************************************\n";
            cout << "BYE, BYE\n\n\n\n";
            cout << "*******************************************************************************\n";
            cout<<endl;
            gameOn = false;
            break;
        default:
            system("cls");
            break;

        }

    }
    return 0;
}
