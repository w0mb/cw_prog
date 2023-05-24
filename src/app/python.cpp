#include "../app_lib/python_lib.hpp"

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    deque<Character> snake;
    snake.push_front({FIELD_WIDTH / 2, FIELD_HEIGHT / 2, SNAKE_CHAR});

    Character target;
    target.x = getRandomNumber(2, FIELD_WIDTH - 3);
    target.y = getRandomNumber(2, FIELD_HEIGHT - 3);
    target.symbol = TARGET_CHAR;

    deque<Character> obstacles;
    for (int x = 0; x < FIELD_WIDTH; ++x) {
        obstacles.push_back({x, 0, OBSTACLE_CHAR});
        obstacles.push_back({x, FIELD_HEIGHT - 1, OBSTACLE_CHAR});
    }
    for (int y = 1; y < FIELD_HEIGHT - 1; ++y) {
        obstacles.push_back({0, y, OBSTACLE_CHAR});
        obstacles.push_back({FIELD_WIDTH - 1, y, OBSTACLE_CHAR});
    }

    int speedFactor = 1;

    while (true) {
        showMainMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            showSettingsMenu(speedFactor);
            clearScreen();
            drawBorders();
            drawCharacter(target);
            for (const Character& obstacle : obstacles) {
                drawCharacter(obstacle);
            }
            for (const Character& segment : snake) {
                drawCharacter(segment);
            }
            Sleep(1000); // Delay for better visualization
        } else if (choice == 2) {
            clearScreen();
            cout << "Goodbye!\n";
            break;
        } else {
            clearScreen();
            cout << "Invalid choice.\n";
            continue;
        }

        int delay = 100 / speedFactor;
        int snakeLength = 1;

        Direction direction = RIGHT;

        while (true) {
            if (GetAsyncKeyState('W') & 0x8000) {
                if (direction != DOWN)
                    direction = UP;
            } else if (GetAsyncKeyState('S') & 0x8000) {
                if (direction != UP)
                    direction = DOWN;
            } else if (GetAsyncKeyState('A') & 0x8000) {
                if (direction != RIGHT)
                    direction = LEFT;
            } else if (GetAsyncKeyState('D') & 0x8000) {
                if (direction != LEFT)
                    direction = RIGHT;
            }

            int dx = 0, dy = 0;
            switch (direction) {
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

            if (newHead.x < 1 || newHead.x >= FIELD_WIDTH - 1 || newHead.y < 1
                || newHead.y >= FIELD_HEIGHT - 1)
                exitGame();

            for (const Character& segment : snake) {
                if (newHead.x == segment.x && newHead.y == segment.y)
                    exitGame();
            }

            bool collidedWithObstacle = false;
            for (const Character& obstacle : obstacles) {
                if (newHead.x == obstacle.x && newHead.y == obstacle.y) {
                    collidedWithObstacle = true;
                    break;
                }
            }

            if (collidedWithObstacle)
                exitGame();

            snake.push_front(newHead);

            if (newHead.x == target.x && newHead.y == target.y) {
                target.x = getRandomNumber(2, FIELD_WIDTH - 3);
                target.y = getRandomNumber(2, FIELD_HEIGHT - 3);

                bool targetOnSnake = true;
                while (targetOnSnake) {
                    targetOnSnake = false;
                    for (const Character& segment : snake) {
                        if (target.x == segment.x && target.y == segment.y) {
                            targetOnSnake = true;
                            target.x = getRandomNumber(2, FIELD_WIDTH - 3);
                            target.y = getRandomNumber(2, FIELD_HEIGHT - 3);
                            break;
                        }
                    }
                }

                drawCharacter(target);
                snakeLength++;
                displaySnakeLength(snakeLength);
            } else {
                eraseCharacter(snake.back());
                snake.pop_back();
            }

            // Redraw the entire snake
            for (const Character& segment : snake) {
                drawCharacter(segment);
            }

            Sleep(delay);
        }
    }

    return 0;
}
