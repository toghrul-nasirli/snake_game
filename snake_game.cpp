#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool Game_Over;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100];
int nTail;

int MENU_1, MENU_2, MENU_3, MENU_4, MENU_5, MENU_6, MENU_7, MENU_8;
int max_1 = score, max_2 = score, max_3 = score;

FILE *records_file;

enum Move {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
Move dir;

void Setup();
void Show();
void Input();
void Logic();
void Records_File();

int main()
{
MainMenu:

    cout << "|------------------------------------------|" << endl;
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
    cout << "|*$ ~ $ ~ $ ~ + ~SNAKE_GAME~ + ~ $ ~ $ ~ $*|" << endl;
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
    cout << "|                                          |" << endl;
    cout << "| 1. Start Game                            |" << endl;
    cout << "| 2. Controls                              |" << endl;
    cout << "| 3. Records                               |" << endl;
    cout << "| 4. Theme                                 |" << endl;
    cout << "| 5. About                        |********|" << endl;
    cout << "|                                 |6. Exit |" << endl;
    cout << "|------------------------------------------|" << endl;

    cin >> MENU_1;

    if (MENU_1 == 1)
    {
        system("cls");
        goto Start;
    }
    else if (MENU_1 == 2)
    {
        system("cls");

        cout << "|------------------------------------------|" << endl;
        cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
        cout << "|*$ ~ $ ~ $ ~ + ~SNAKE_GAME~ + ~ $ ~ $ ~ $*|" << endl;
        cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
        cout << "|_____________Control__Options_____________|" << endl;
        cout << "|                                          |" << endl;
        cout << "| 1. W,A,S,D(default)    2. Direction keys |" << endl;
        cout << "|                                          |" << endl;
        cout << "|                            |*************|" << endl;
        cout << "|                            |3. Main Menu |" << endl;
        cout << "|                            |4. Exit      |" << endl;
        cout << "|------------------------------------------|" << endl;

        cin >> MENU_7;

        if (MENU_7 == 1)
        {
            system("cls");
            goto MainMenu;
        }
        else if (MENU_7 == 2)
        {
            system("cls");
            goto MainMenu;
        }
        else if (MENU_7 == 3)
        {
            system("cls");
            goto MainMenu;
        }
        else if (MENU_7 == 4)
        {
            exit(CONSOLE_APPLICATION_16BIT);
        }
    }
    else if (MENU_1 == 3)
    {
        system("cls");
        cout << "|------------------------------------------|" << endl;
        cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
        cout << "|*$ ~ $ ~ $ ~ + ~SNAKE_GAME~ + ~ $ ~ $ ~ $*|" << endl;
        cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
        cout << "|_________________Recordss_________________|" << endl;
        cout << "| 1'st - " << max_1 << "                                |" << endl;
        cout << "| 2'nd - " << max_2 << "                                |" << endl;
        cout << "| 3'rd - " << max_3 << "                                |" << endl;
        cout << "|                            |*************|" << endl;
        cout << "|                            |1. Main Menu |" << endl;
        cout << "|                            |2. Exit      |" << endl;
        cout << "|------------------------------------------|" << endl;

        cin >> MENU_5;

        if (MENU_5 == 1)
        {
            system("cls");
            goto MainMenu;
        }
        else if (MENU_5 == 2)
        {
            exit(CONSOLE_APPLICATION_16BIT);
        }
    }
    else if (MENU_1 == 4)
    {
        system("cls");
        cout << "|------------------------------------------|" << endl;
        cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
        cout << "|*$ ~ $ ~ $ ~ + ~SNAKE_GAME~ + ~ $ ~ $ ~ $*|" << endl;
        cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
        cout << "|~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~|" << endl;
        cout << "|~ 1. White-Black  ~ ~~ ~  2. Light Aqua  ~|" << endl;
        cout << "|~ 3. Light Yellow ~ ~~ ~  4. Light White ~|" << endl;
        cout << "|~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~|" << endl;
        cout << "|                            |*************|" << endl;
        cout << "|                            |5. Main Menu |" << endl;
        cout << "|                            |6. Exit      |" << endl;
        cout << "|------------------------------------------|" << endl;

        cin >> MENU_8;

        if (MENU_8 == 1)
        {
            system("color 70");
            system("cls");
            goto MainMenu;
        }
        else if (MENU_8 == 2)
        {
            system("color B");
            system("cls");
            goto MainMenu;
        }
        else if (MENU_8 == 3)
        {
            system("color E");
            system("cls");
            goto MainMenu;
        }
        else if (MENU_8 == 4)
        {
            system("color F");
            system("cls");
            goto MainMenu;
        }
        else if (MENU_8 == 5)
        {
            system("cls");
            goto MainMenu;
        }
        else if (MENU_8 == 6)
        {
            exit(CONSOLE_APPLICATION_16BIT);
        }
    }
    else if (MENU_1 == 5)
    {
        system("cls");
        cout << "|------------------------------------------|" << endl;
        cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
        cout << "|*$ ~ $ ~ $ ~ + ~SNAKE_GAME~ + ~ $ ~ $ ~ $*|" << endl;
        cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
        cout << "|..........................................|" << endl;
        cout << "|..........................................|" << endl;
        cout << "|..........................................|" << endl;
        cout << "|..........................................|" << endl;
        cout << "|..._By.Nasirli..............|*************|" << endl;
        cout << "|............................|1. Main Menu |" << endl;
        cout << "|............................|2. Exit      |" << endl;
        cout << "|------------------------------------------|" << endl;

        cin >> MENU_6;

        if (MENU_6 == 1)
        {
            system("cls");
            goto MainMenu;
        }
        else if (MENU_6 == 2)
        {
            exit(CONSOLE_APPLICATION_16BIT);
        }
    }
    else if (MENU_1 == 6)
    {
        exit(CONSOLE_APPLICATION_16BIT);
    }

Start:

    system("cls");

Difficulity:

    cout << "|------------------------------------------|" << endl;
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
    cout << "|*$ ~ $ ~ $ ~ + ~SNAKE_GAME~ + ~ $ ~ $ ~ $*|" << endl;
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
    cout << "|                                          |" << endl;
    cout << "| 1. Easy                                  |" << endl;
    cout << "| 2. Medium                                |" << endl;
    cout << "| 3. Hard                    |*************|" << endl;
    cout << "|                            |4. Main Menu |" << endl;
    cout << "|                            |5. Exit      |" << endl;
    cout << "|------------------------------------------|" << endl;

    cin >> MENU_4;

    if (MENU_4 == 4)
    {
        system("cls");
        goto MainMenu;
    }
    else if (MENU_4 == 5)
    {
        exit(CONSOLE_APPLICATION_16BIT);
    }

    system("cls");
    cout << "|------------------------------------------|" << endl;
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
    cout << "|*$ ~ $ ~ $ ~ + ~SNAKE_GAME~ + ~ $ ~ $ ~ $*|" << endl;
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
    cout << "|                                          |" << endl;
    cout << "| 1. Normal                                |" << endl;
    cout << "| 2. Infinity                |*************|" << endl;
    cout << "|                            |3. Back      |" << endl;
    cout << "|                            |4. Main Menu |" << endl;
    cout << "|                            |5. Exit      |" << endl;
    cout << "|------------------------------------------|" << endl;

    cin >> MENU_3;

    if (MENU_3 == 3)
    {
        system("cls");
        goto Difficulity;
    }
    else if (MENU_3 == 4)
    {
        system("cls");
        goto MainMenu;
    }
    else if (MENU_3 == 5)
    {
        exit(CONSOLE_APPLICATION_16BIT);
    }

    Setup();

    while (!Game_Over)
    {
        Show();
        Input();
        Logic();
    }

    Records_File();

    if (Game_Over == true)
    {
        system("cls");
        cout << "|------------------------------------------|" << endl;
        cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
        cout << "|~ ~ ~ ~ ~ ~ ~ ~ Game__Over ~ ~ ~ ~ ~ ~ ~ ~|" << "\a\n";
        cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
        cout << "|                                          |" << endl;
        cout << "| 1. Restart Game                          |" << endl;
        cout << "|                                          |" << endl;
        cout << "|                            |*************|" << endl;
        cout << "|                            |2. Main Menu |" << endl;
        cout << "|                            |3. Exit      |" << endl;
        cout << "|------------------------------------------|" << endl;

        cin >> MENU_2;

        if (MENU_2 == 1)
        {
            goto Start;
        }
        else if (MENU_2 == 2)
        {
            system("cls");
            goto MainMenu;
        }
        else if (MENU_2 == 3)
        {
            exit(CONSOLE_APPLICATION_16BIT);
        }

        system("cls");
        goto MainMenu;
    }

    return 0;
}

void Setup()
{
    Game_Over = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    nTail = 0;
    score = 0;
}

void Show() {
    system("cls");
    srand(time(0));

    for (int i = 0; i < width + 2; i++)
    {
        cout << '-';
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "|";
            }
            if (i == y && j == x) {
                cout << "O";
            }
            else if (i == fruitY && j == fruitX)
            {
                cout << "*";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
            }
            if (j == width - 1)
            {
                cout << "|";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
    {
        cout << "-";
    }
    cout << endl;

    cout << "Score : " << score << endl;
    cout << "Exit(x)" << endl;
}

void Input()
{
    if (!MENU_7 || MENU_7 == 1)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
                if (dir != RIGHT)
                    dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT)
                    dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN)
                    dir = UP;
                break;
            case 's':
                if (dir != UP)
                    dir = DOWN;
                break;
            case 'x':
                Game_Over = true;
                break;

            }
        }
    }
    else if (MENU_7 == 2)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 75:
                if (dir != RIGHT)
                    dir = LEFT;
                break;
            case 77:
                if (dir != LEFT)
                    dir = RIGHT;
                break;
            case 72:
                if (dir != DOWN)
                    dir = UP;
                break;
            case 80:
                if (dir != UP)
                    dir = DOWN;
                break;
            case 'x':
                Game_Over = true;
                break;
            }
        }
    }

    if (MENU_4 == 1)
    {
        Sleep(100);
    }
    else if (MENU_4 == 2)
    {
        Sleep(60);
    }
    else if (MENU_4 == 3)
    {
        Sleep(30);
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (MENU_3 == 1)
    {
        if (x > width || x < 0 || y > height || y < 0)
        {
            Game_Over = true;
        }
    }
    else if (MENU_3 == 2)
    {
        if (x >= width)
        {
            x = 0;
        }
        else if (x < 0)
        {
            x = width - 1;
        }

        if (y >= height)
        {
            y = 0;
        }
        else if (y < 0)
        {
            y = height - 1;
        }
    }

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }

    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            Game_Over = true;
        }
    }
}

void Records_File()
{
    fopen_s(&records_file, "Records_1.txt", "r");
    fscanf_s(records_file, "1. %d", &max_1);
    fclose(records_file);

    fopen_s(&records_file, "Records_2.txt", "r");
    fscanf_s(records_file, "2. %d", &max_2);
    fclose(records_file);

    fopen_s(&records_file, "Records_3.txt", "r");
    fscanf_s(records_file, "3. %d", &max_3);
    fclose(records_file);

    if (max_1 <= score)
    {
        fopen_s(&records_file, "Records_1.txt", "w");

        max_1 = score;
        fprintf_s(records_file, "1. %d", max_1);

        fclose(records_file);
    }
    else if (max_2 <= score)
    {
        fopen_s(&records_file, "Records_2.txt", "w");

        max_2 = score;
        fprintf_s(records_file, "2. %d", max_2);

        fclose(records_file);
    }
    else if (max_3 <= score)
    {
        fopen_s(&records_file, "Records_3.txt", "w");

        max_3 = score;
        fprintf_s(records_file, "3. %d", max_3);

        fclose(records_file);
    }
}

