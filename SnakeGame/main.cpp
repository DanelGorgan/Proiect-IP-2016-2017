#include <iostream>
#include <windows.h>
#include<conio.h>

using namespace std;

bool gameover;
int width;
int height;
int score;
enum eDirection {STOP=0, LEFT,RIGHT,UP,DOWN};
eDirection dir;

struct Snake
{
    int x, y;
}snake;

struct Fruit
{
    int x, y;
}fruit;

void InitGame()
{
    width=30;
    height=18;
    snake.x= width /2 ;
    snake.y= height / 2;
    fruit.x=rand()%width;
    fruit.y=rand()%height;
}

void Draw()
{
    int i, j;

    system("cls");

    for (i=0; i<width+1; i++)
        cout<<"#";
    cout<<endl;

    for(i =0 ; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            if(j==0)
                cout<<"#";
            else if (i==snake.y && j==snake.x)
                cout<<"O";
            else if (i==fruit.y && j==fruit.x)
                cout<<"F";
            else cout<<" ";
            if (j==width-1)
                cout<<"#";
        }
        cout<<endl;
    }

    for (i=0; i<width+1; i++)
        cout<<"#";
    cout<<endl;
    cout<<"Score: "<<score;
}

void Input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'a':
            dir=LEFT;
            break;
        case 'd':
            dir=RIGHT;
            break;
            if(dir!=UP)
        case 's':
            dir=DOWN;
            break;
        case 'w':
            dir=UP;
            break;
        case 'x':
            gameover=true;
            break;
        }
    }
    if(snake.x>width-1 || snake.x<1 || snake.y>height-1 || snake.y <0)
        gameover=true;

    if(snake.x==fruit.x && snake.y==fruit.y)
    {
        score+=10;
        fruit.x=rand()%width;
        fruit.y=rand()%height;
    }
}

void Logic()
{

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
}

int main()
{
    InitGame();
    while(!gameover)
    {
        Draw();
        Input();
        Logic();
        Sleep(75);
    }
    system("cls");
    cout<<"GAME OVER!";

}


