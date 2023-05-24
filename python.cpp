#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <deque>

using namespace std;

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;
const int FIELD_WIDTH = 70;
const int FIELD_HEIGHT = 50;
const char TARGET_CHAR = 'X';
const char OBSTACLE_CHAR = '#';

struct Character
{
    int x;
    int y;
    char symbol;
};

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

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

void moveCharacter(Character &character, int dx, int dy)
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

void showMenu()
{
    clearScreen();
    cout << "Hello, it's the Python game.\nChoose an action:\n";
    cout << "1) Start game\n";
    cout << "2) Settings\n";
    cout << "3) Exit\n";
}

void showSettingsMenu(int &speedFactor)
{
    clearScreen();
    cout << "Settings:\n";
    cout << "1) + Speed\n";
    cout << "2) +++ Speed\n";
    cout << "3) - Speed\n";
    cout << "4) --- Speed\n";
    cout << "5) Back\n";

    int settingChoice;
    cin >> settingChoice;

    switch (settingChoice)
    {
    case 1:
        speedFactor = 1;
        break;
    case 2:
        speedFactor = 2;
        break;
    case 3:
        speedFactor = -1;
        break;
    case 4:
        speedFactor = -2;
        break;
    case 5:
        return;  // Go back to the previous menu
    default:
        cout << "Invalid choice.\n";
        return;  // Go back to the settings menu
    }

    clearScreen();
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    deque<Character> snake;
    snake.push_front({FIELD_WIDTH / 2, FIELD_HEIGHT / 2, '*'});

    Character target;
    target.x = getRandomNumber(0, FIELD_WIDTH - 1);
    target.y = getRandomNumber(0, FIELD_HEIGHT - 1);
    target.symbol = TARGET_CHAR;

    drawCharacter(snake.front());
    drawCharacter(target);

    deque<Character> obstacles;
    for (int x = 0; x < FIELD_WIDTH; ++x)
    {
        obstacles.push_back({x, 0, OBSTACLE_CHAR});
        drawCharacter(obstacles.back());
        obstacles.push_back({x, FIELD_HEIGHT - 1, OBSTACLE_CHAR});
        drawCharacter(obstacles.back());
    }
    for (int y = 1; y < FIELD_HEIGHT - 1; ++y)
    {
        obstacles.push_back({0, y, OBSTACLE_CHAR});
        drawCharacter(obstacles.back());
        obstacles.push_back({FIELD_WIDTH - 1, y, OBSTACLE_CHAR});
        drawCharacter(obstacles.back());
    }

    int speedFactor = 1;

    while (true)
    {
        showMenu();
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            showSettingsMenu(speedFactor);
        }
        else if (choice == 2)
        {
            clearScreen();
            cout << "Goodbye!\n";
            return 0;
        }
        else if (choice == 3)
        {
            clearScreen();
            cout << "Invalid choice.\n";
            continue;
        }

        int delay = 100 / speedFactor;

        Direction direction = RIGHT;

        while (true)
        {
            if (GetAsyncKeyState('W') & 0x8000)
            {
                if (direction != DOWN)
                    direction = UP;
            }
            else if (GetAsyncKeyState('S') & 0x8000)
            {
                if (direction != UP)
                    direction = DOWN;
            }
            else if (GetAsyncKeyState('A') & 0x8000)
            {
                if (direction != RIGHT)
                    direction = LEFT;
            }
            else if (GetAsyncKeyState('D') & 0x8000)
            {
                if (direction != LEFT)
                    direction = RIGHT;
            }

            int dx = 0, dy = 0;
            switch (direction)
            {
            case UP:
                dy = -1;
                break;
            case DOWN:
                dy = 1;
                break;
            case LEFT:
                dx = -1;
                break;
            case RIGHT:
                dx = 1;
                break;
            }

            Character newHead = snake.front();
            moveCharacter(newHead, dx, dy);

            if (newHead.x < 0 || newHead.x >= FIELD_WIDTH || newHead.y < 0 || newHead.y >= FIELD_HEIGHT)
                break;

            for (const Character &segment : snake)
            {
                if (newHead.x == segment.x && newHead.y == segment.y)
                {
                    return 0;
                }
            }

            bool collidedWithObstacle = false;
            for (const Character &obstacle : obstacles)
            {
                if (newHead.x == obstacle.x && newHead.y == obstacle.y)
                {
                    collidedWithObstacle = true;
                    break;
                }
            }

            if (collidedWithObstacle)
                break;

            snake.push_front(newHead);

            if (newHead.x == target.x && newHead.y == target.y)
            {
                target.x = getRandomNumber(0, FIELD_WIDTH - 1);
                target.y = getRandomNumber(0, FIELD_HEIGHT - 1);
                drawCharacter(target);
            }
            else
            {
                eraseCharacter(snake.back());
                snake.pop_back();
            }

            for (const Character &segment : snake)
            {
                drawCharacter(segment);
            }

            Sleep(delay);
        }
    }

    return 0;
}
