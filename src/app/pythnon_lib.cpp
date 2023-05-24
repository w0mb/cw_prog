#include "../app_lib/python_lib.hpp"

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void setCursorPosition(int x, int y)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(output, pos);
}

void drawCharacter(Character character)
{
    setCursorPosition(character.x, character.y);
    cout << character.symbol;
}

void eraseCharacter(Character character)
{
    setCursorPosition(character.x, character.y);
    cout << ' ';
}

void moveCharacter(Character& character, int dx, int dy)
{
    eraseCharacter(character);
    character.x += dx;
    character.y += dy;
    drawCharacter(character);
}

void clearScreen()
{
    system("cls");
}

void showMainMenu()
{
    clearScreen();
    cout << "Snake Game\n";
    cout << "1) Start the game\n";
    cout << "2) Exit\n";
}

void showSettingsMenu(int& speedFactor)
{
    clearScreen();
    cout << "Difficulty Settings:\n";
    cout << "1) Easy\n";
    cout << "2) Normal\n";
    cout << "3) Hard\n";
    cout << "4) Back\n";

    int settingChoice;
    cin >> settingChoice;

    switch (settingChoice) {
    case 1:
        speedFactor = 1;
        break;
    case 2:
        speedFactor = 2;
        break;
    case 3:
        speedFactor = 3;
        break;
    case 4:
        return; // Go back to the previous menu
    default:
        cout << "Invalid choice.\n";
        return; // Go back to the settings menu
    }

    clearScreen();
    cout << "Difficulty set to: ";
    if (speedFactor == 1)
        cout << "Easy\n";
    else if (speedFactor == 2)
        cout << "Normal\n";
    else if (speedFactor == 3)
        cout << "Hard\n";

    cout << "Press Spacebar to continue...";
    while (true) {
        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
            break;
    }
}

void drawBorders()
{
    for (int x = 0; x < FIELD_WIDTH; ++x) {
        drawCharacter({x, 0, '#'});
        drawCharacter({x, FIELD_HEIGHT - 1, '#'});
    }

    for (int y = 1; y < FIELD_HEIGHT - 1; ++y) {
        drawCharacter({0, y, '#'});
        drawCharacter({FIELD_WIDTH - 1, y, '#'});
    }
}

void exitGame()
{
    clearScreen();
    cout << "Game Over! Press any key to exit..." << endl;
    while (!_kbhit()) {} // Wait for a key press
    exit(0);
}

void displaySnakeLength(int length)
{
    setCursorPosition(0, FIELD_HEIGHT);
    cout << "Snake Length: " << length << endl;
}
