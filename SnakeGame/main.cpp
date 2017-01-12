#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <ctime>
#include <cstring>

using namespace std;

bool gameOver;
bool gameOn = true;
bool ok=false;
char choice, choice1, nameChar[7][20]= {"Bpatrut ","DoubleG ","FREE ","Thek ","BogdanP "}, name[6];;
int width;
int height;
int score;
int ghost, bonus, cut, slow, fast;
int highscore[6]= {50,30,20,10,0},pos=5, pos1=5;
int miliseconds, seconds, minutes, hours;
enum eDirection {STOP=0, LEFT,RIGHT,UP,DOWN};
eDirection dir;
HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);

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
    ghost=0;
    cut=0;
    slow=0;
    fast=0;
    srand(time(NULL));
}
void Board (int x, int y)
{
    if (x==6 && y==width-1)
    {
        cout<<"   Powerup: ";
        if (ghost) cout<<"GHOST";
        else if (bonus) cout<<"BONUS";
        else if (cut) cout<<"CUT  ";
        else if (slow) cout<<"SLOW ";
        else if (fast) cout<<"FAST ";
        else cout<<"NONE ";
    }
    if (x==7 && y==width-1)
        cout<<"  SCORE: "<<score;
}

void Draw()
{
    int i, j;

    clear_screen();

    for (i=0; i<width+2; i++)
        cout<<(unsigned char)(219);
    cout<<endl;

    for(i =0 ; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            if(j==0)
                cout << (unsigned char)(219);
            if (i==snake.y && j==snake.x)
            {
                SetConsoleTextAttribute(color,5);
                cout<<(unsigned char)(219);
                SetConsoleTextAttribute(color,12);
            }
            else if (i==fruit.y && j==fruit.x)
            {
                SetConsoleTextAttribute(color,1);
                cout<<"O";
                SetConsoleTextAttribute(color,12);
            }
            else if (i==powerUp.y && j==powerUp.x)
            {
                SetConsoleTextAttribute(color,14);
                cout<<"@";
                SetConsoleTextAttribute(color,12);
            }
            else
            {
                ok=false;
                for (int k=0; k<tail.lenght; k++)
                {

                    if (tail.x[k]==j && tail.y[k]==i)
                    {
                        SetConsoleTextAttribute(color,21);
                        cout<<(unsigned char)(219);
                        SetConsoleTextAttribute(color,12);
                        ok=true;
                    }
                }
                if (ok==false) cout<<" ";
            }

            if(j==width-1)
                cout<<(unsigned char)(219);
            Board(i, j);
        }
        cout<<endl;
    }

    for (i=0; i<width+2; i++)
        cout<<(unsigned char)(219);

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
    for (int i=1; i<=tail.lenght; i++)
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
        if(snake.x>width-1 || snake.x<0 || snake.y>height-1 || snake.y <0)
            gameOver=true;

    if (ghost==1)
    {
        if (snake.x>width-1) snake.x=0;
        else if (snake.x<0) snake.x=width-2;
        if (snake.y>=height) snake.y=0;
        else if (snake.y<0) snake.y=height-1;
    }

    if (ghost==0)
        for (int i=0; i<tail.lenght; i++)
            if (tail.x[i]==snake.x && tail.y[i]==snake.y)
                gameOver=true;

    if(snake.x==fruit.x && snake.y==fruit.y)
    {
        tail.lenght++;
        if (bonus==1)
            score+=50;
        else score+=10;
        fruit.x=rand()%width;
        fruit.y=rand()%height;
    }
    if (seconds%20==0 && miliseconds==5 || seconds==0 && miliseconds==5 && minutes>0)
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

void HighScore(int score, char name[100])
{
    if(score!=0)
    {
        highscore[pos]=score;
        strcpy(nameChar[pos1],name);

        for(int i=0; i<5; i++)
            for(int j=i+1; j<6; j++)
                if(highscore[i]<highscore[j])
                {
                    int aux=highscore[i];
                    highscore[i]=highscore[j];
                    highscore[j]=aux;
                    char auxChar[100];
                    strcpy(auxChar,nameChar[i]);
                    strcpy(nameChar[i],nameChar[j]);
                    strcpy(nameChar[j],auxChar);
                }

    }

}



int main()
{
    HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color,12);

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
                cout<<"INSERT YOUR NAME HERE: ";
                cin>>name;
                HighScore(score, name);
                gameOver=false;
                //system("pause");
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
            system("cls");
            cout << "                                SNAKE GAME                                     \n";
            cout << "                                                          by TwinsG            \n";
            cout << "*******************************************************************************\n";
            for(int i=0; i<5; i++)
            {

                cout<<i+1<<". "<<nameChar[i]<<" ";
                cout<<highscore[i];
                cout<<'\n';
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
