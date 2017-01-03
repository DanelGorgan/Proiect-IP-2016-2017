#include <iostream>
#include <windows.h>

using namespace std;

bool gameover;
int width;
int height;

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
    height=20;
    snake.x= width /2 ;
    snake.y= height / 2;
    fruit.x=rand()%width;
    fruit.y=rand()%height;
}

void Draw()
{
    int i, j;

    system("cls");

    for (i=0; i<width; i++)
        cout<<"#";
    cout<<endl;

    for(i =0 ; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            if(j==0 || j==width-1)
                cout<<"#";
            else if (i==snake.x && j==snake.y)
                cout<<"O";
            else if (i==fruit.x && j==fruit.y)
                cout<<"F";
            else cout<<" ";
        }
        cout<<endl;
    }
    for (i=0; i<width; i++)
        cout<<"#";
    cout<<endl;
}

int main()
{
    InitGame();
    Draw();
}


