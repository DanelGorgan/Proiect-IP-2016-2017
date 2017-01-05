#include <iostream>
#include <windows.h>
#include<conio.h>

using namespace std;

bool gameOver;
int width;
int height;
int score;
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

void timer ()
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
    gameOver=false;
    score=0;
    width=30;
    height=18;
    snake.x= width /2 ;
    snake.y= height / 2;
    fruit.x=rand()%width;
    fruit.y=rand()%height;
    tail.lenght=0;
}


void Draw()
{
    int i, j;

    system("cls");

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
            if (j==width-1)
                cout<<"#";
        }
        cout<<endl;
    }

    for (i=0; i<width+2; i++)
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
    if(snake.x>width-1 || snake.x<1 || snake.y>height-1 || snake.y <0)
        gameOver=true;

    for (int i=0; i<tail.lenght; i++)
        if (tail.x[i]==snake.x && tail.y[i]==snake.y)
            gameOver=1;

    if(snake.x==fruit.x && snake.y==fruit.y)
    {
        tail.lenght++;
        score+=10;
        fruit.x=rand()%width;
        fruit.y=rand()%height;
    }
}



int main()
{
    int choice;
    bool gameOn = true;
    while (gameOn != false)
    {
        cout << "                                SNAKE GAME                                \n";
        cout << "                                             by TwinsG                    \n";
        cout << "*******************************\n";
        cout << " 1 - Start the game.\n";
        cout << " 2 - Game modes.\n";
        cout << " 3 - Help.\n";
        cout << " 4 - Exit.\n";
        cout << "*******************************\n";
        cout << " Enter your choice and press return: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            InitGame();
                while(!gameOver)
                {
                    timer();
                    Draw();
                    Input();
                    Logic();
                    Sleep(65);
                }
            system("cls");
            cout<<"GAME OVER!"<<endl;
            cout<<hours<<":"<<minutes<<":"<<seconds<<"."<<miliseconds<<endl;
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            cout << "Come on... it's the classic snake, no game modes.\n";
            system("pause");
            system("cls");
            break;
        case 3:
            cout << "Ahahah, you really think I will help you?\n";
            system("cls");
            cout<<"No help!";
            cout<<endl;
            system("pause");
            system("cls");
            break;
        case 4:
            system("cls");
            cout << "End of Program.\n";
            gameOn = false;
            break;
        default:
            cout << "Not a Valid Choice. \n";
            cout << "Choose again.\n";
            cin >> choice;
            break;
        }

    }
    return 0;
}
