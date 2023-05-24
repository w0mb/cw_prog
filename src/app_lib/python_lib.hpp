#pragma once

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;
const int FIELD_WIDTH = 70;
const int FIELD_HEIGHT = 20;
const char TARGET_CHAR = 'X';
const char OBSTACLE_CHAR = '#';
const char SNAKE_CHAR = '*';

struct Character {
    int x;
    int y;
    char symbol;
};

enum Direction { UP, DOWN, LEFT, RIGHT };

int getRandomNumber(int min, int max);

void setCursorPosition(int x, int y);

void drawCharacter(Character character);

void eraseCharacter(Character character);

void moveCharacter(Character& character, int dx, int dy);

void clearScreen();

void showMainMenu();

void showSettingsMenu(int& speedFactor);

void drawBorders();