#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <limits>

#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

using namespace std;

// Game state variables
bool Game_Over;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum Move { STOP = 0, LEFT, RIGHT, UP, DOWN };
Move dir = STOP;
int controlMode = 1; // 1: WASD, 2: Arrow keys
int gameSpeed = 100;
int max_1 = 0, max_2 = 0, max_3 = 0; // High score records
bool isInfiniteMode = false;

// Function declarations
void Setup();
void Draw();
void Input();
void Logic();
void Records_File();
void clearConsole();
void MainMenu();
void GameOverMenu();
void HandleControls();
void HandleTheme();
void HandleRecords();
void HandleAbout();
void SetDifficulty();
void SelectGameMode();
int kbhit();
char getch();

// ANSI codes or console attributes for themes
#ifdef _WIN32
void setConsoleColor(int color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); }
void resetConsoleColor() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); }
#else
void setConsoleColor(const string& colorCode) { cout << colorCode; }
void resetConsoleColor() { cout << "\033[0m"; }
const string WHITE_BLACK = "\033[37;40m";
const string LIGHT_AQUA = "\033[36;40m";
const string LIGHT_YELLOW = "\033[33;40m";
const string LIGHT_WHITE = "\033[37;40m";
#endif

string current_theme = WHITE_BLACK;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    bool exitGame = false;

    while (!exitGame) {
        MainMenu();
        int choice;
        cin >> choice;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice, try again.\n";
            MainMenu();
            cin >> choice;
        }

        switch (choice) {
            case 1:
                SetDifficulty();
                SelectGameMode();
                Setup();
                while (!Game_Over) {
                    Draw();
                    Input();
                    Logic();
                }
                Records_File();
                GameOverMenu();
                break;

            case 2:
                HandleControls();
                break;

            case 3:
                HandleRecords();
                break;

            case 4:
                HandleTheme();
                break;

            case 5:
                HandleAbout();
                break;

            case 6:
                exitGame = true;
                break;

            default:
                cout << "Invalid choice, try again.\n";
                break;
        }
    }

    return 0;
}

void MainMenu() {
    clearConsole();
    cout << "|------------------------------------------|\n";
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|\n";
    cout << "|*$ ~ $ ~ $ ~ + ~SNAKE_GAME~ + ~ $ ~ $ ~ $*|\n";
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|\n";
    cout << "|                                          |\n";
    cout << "| 1. Start Game                            |\n";
    cout << "| 2. Controls                              |\n";
    cout << "| 3. Records                               |\n";
    cout << "| 4. Theme                                 |\n";
    cout << "| 5. About                        |********|\n";
    cout << "|                                 |6. Exit |\n";
    cout << "|------------------------------------------|\n";
}

void SetDifficulty() {
    clearConsole();
    cout << "|------------------------------------------|\n";
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|\n";
    cout << "|*$ ~ $ ~ $ ~ + ~SNAKE_GAME~ + ~ $ ~ $ ~ $*|\n";
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|\n";
    cout << "|                                          |\n";
    cout << "| 1. Easy                                  |\n";
    cout << "| 2. Medium                                |\n";
    cout << "| 3. Hard                    |*************|\n";
    cout << "|                            |4. Main Menu |\n";
    cout << "|                            |5. Exit      |\n";
    cout << "|------------------------------------------|\n";

    int difficulty;
    cin >> difficulty;

    while (cin.fail() || difficulty < 1 || difficulty > 5) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice, please select a valid option (1-5).\n";
        cin >> difficulty;
    }

    if (difficulty == 4) { // Main Menu
        MainMenu();
    } else if (difficulty == 5) { // Exit
        exit(0);
    } else {
        gameSpeed = (difficulty == 1) ? 150 : (difficulty == 2) ? 100 : 60;
    }
}

void SelectGameMode() {
    clearConsole();
    cout << "|------------------------------------------|\n";
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|\n";
    cout << "|*$ ~ $ ~ $ ~ + ~SNAKE_GAME~ + ~ $ ~ $ ~ $*|\n";
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|\n";
    cout << "|                                          |\n";
    cout << "| 1. Normal                                |\n";
    cout << "| 2. Infinity                |*************|\n";
    cout << "|                            |3. Back      |\n";
    cout << "|                            |4. Main Menu |\n";
    cout << "|                            |5. Exit      |\n";
    cout << "|------------------------------------------|\n";

    int gameMode;
    cin >> gameMode;

    while (cin.fail() || gameMode < 1 || gameMode > 5) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice, please select a valid option (1-5).\n";
        cin >> gameMode;
    }

    switch (gameMode) {
        case 1:
            isInfiniteMode = false;
            break;
        case 2:
            isInfiniteMode = true;
            break;
        case 3: // Back to difficulty selection
            SetDifficulty();
            SelectGameMode(); // Ensure game mode is selected after difficulty
            break;
        case 4: // Main Menu
            MainMenu();
            break;
        case 5: // Exit
            exit(0);
            break;
        default:
            break;
    }
}

void Setup() {
    Game_Over = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    nTail = 0;
    score = 0;
}

void Draw() {
    clearConsole();
#ifdef _WIN32
    setConsoleColor(7);  // Default console
#else
    setConsoleColor(current_theme);
#endif

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "|";
            if (i == y && j == x) cout << "O";
            else if (i == fruitY && j == fruitX) cout << "*";
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        printTail = true;
                        break;
                    }
                }
                if (!printTail) cout << " ";
            }
            if (j == width - 1) cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << "\nScore: " << score << "\nExit(x)\n";
    resetConsoleColor();
}

void Input() {
    if (kbhit()) {
        char key = getch();
        if (key == 'x' || key == 'X') { Game_Over = true; return; }

        if (controlMode == 1) { // WASD
            switch (key) {
                case 'a': if (dir != RIGHT) dir = LEFT; break;
                case 'd': if (dir != LEFT) dir = RIGHT; break;
                case 'w': if (dir != DOWN) dir = UP; break;
                case 's': if (dir != UP) dir = DOWN; break;
            }
        }
        else if (controlMode == 2) { // Arrow keys
            if (key == '\033') { // Escape sequence for arrow keys
                getch(); // skip '['
                switch (getch()) {
                    case 'A': if (dir != DOWN) dir = UP; break; // Up arrow
                    case 'B': if (dir != UP) dir = DOWN; break; // Down arrow
                    case 'C': if (dir != LEFT) dir = RIGHT; break; // Right arrow
                    case 'D': if (dir != RIGHT) dir = LEFT; break; // Left arrow
                }
            }
        }
    }

#ifdef _WIN32
    Sleep(gameSpeed);
#else
    usleep(gameSpeed * 1000);
#endif
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
    }

    if (!isInfiniteMode) {
        if (x >= width || x < 0 || y >= height || y < 0)
            Game_Over = true;
    } else {
        if (x >= width) x = 0; else if (x < 0) x = width - 1;
        if (y >= height) y = 0; else if (y < 0) y = height - 1;
    }

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            Game_Over = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

void Records_File() {
    ifstream records_file;
    records_file.open("Records_1.txt");
    if (records_file.is_open()) {
        records_file >> max_1;
        records_file.close();
    }
    records_file.open("Records_2.txt");
    if (records_file.is_open()) {
        records_file >> max_2;
        records_file.close();
    }
    records_file.open("Records_3.txt");
    if (records_file.is_open()) {
        records_file >> max_3;
        records_file.close();
    }

    ofstream record_file;
    if (max_1 <= score) {
        record_file.open("Records_1.txt");
        max_1 = score;
        record_file << max_1;
        record_file.close();
    }
    else if (max_2 <= score) {
        record_file.open("Records_2.txt");
        max_2 = score;
        record_file << max_2;
        record_file.close();
    }
    else if (max_3 <= score) {
        record_file.open("Records_3.txt");
        max_3 = score;
        record_file << max_3;
        record_file.close();
    }
}

void GameOverMenu() {
    clearConsole();
    cout << "|------------------------------------------|" << endl;
    cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
    cout << "|~ ~ ~ ~ ~ ~ ~ ~ Game__Over ~ ~ ~ ~ ~ ~ ~ ~|" << endl;
    cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
    cout << "|                                          |" << endl;
    cout << "| 1. Restart Game                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                            |*************|" << endl;
    cout << "|                            |2. Main Menu |" << endl;
    cout << "|                            |3. Exit      |" << endl;
    cout << "|------------------------------------------|" << endl;

    char choice;
    cin >> choice;
    switch (choice) {
        case '1':
            Setup();
            break;
        case '2':
            Game_Over = false;
            break;
        case '3':
            exit(0);
    }
}

void HandleControls() {
    clearConsole();
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

    int controlChoice;
    cin >> controlChoice;
    if (controlChoice == 1 || controlChoice == 2)
        controlMode = controlChoice;
    else if (controlChoice == 4)
        exit(0);
}

void HandleTheme() {
    clearConsole();
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

    int themeChoice;
    cin >> themeChoice;

    switch (themeChoice) {
        case 1:
            current_theme = WHITE_BLACK;
            break;
        case 2:
            current_theme = LIGHT_AQUA;
            break;
        case 3:
            current_theme = LIGHT_YELLOW;
            break;
        case 4:
            current_theme = LIGHT_WHITE;
            break;
        case 6:
            exit(0);
            break;
        default:
            break;
    }
}

void HandleRecords() {
    clearConsole();
    cout << "|------------------------------------------|" << endl;
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
    cout << "|*$ ~ $ ~ $ ~ + ~SNAKE_GAME~ + ~ $ ~ $ ~ $*|" << endl;
    cout << "|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|" << endl;
    cout << "|_________________Records_________________|" << endl;
    cout << "| 1'st - " << max_1 << "                                |" << endl;
    cout << "| 2'nd - " << max_2 << "                                |" << endl;
    cout << "| 3'rd - " << max_3 << "                                |" << endl;
    cout << "|                            |*************|" << endl;
    cout << "|                            |1. Main Menu |" << endl;
    cout << "|                            |2. Exit      |" << endl;
    cout << "|------------------------------------------|" << endl;

    int menuChoice;
    cin >> menuChoice;
    if (menuChoice == 2)
        exit(0);
}

void HandleAbout() {
    clearConsole();
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

    int menuChoice;
    cin >> menuChoice;
    if (menuChoice == 2)
        exit(0);
}

#ifdef _WIN32
int kbhit() {
    return _kbhit();
}

char getch() {
    return _getch();
}

#else
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF) {
      ungetc(ch, stdin);
      return 1;
    }

    return 0;
}

char getch() {
    struct termios oldt, newt;
    char ch;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}