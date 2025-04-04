#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "position.h"

#define WIDTH 20
#define HEIGHT 10
#define INITIAL_LENGTH 3

void main_menu();  
void game_loop();
void init_game();
void draw_game();
void move_snake();
void game_over();

Position snake[WIDTH * HEIGHT];
int snake_length = INITIAL_LENGTH;
Position food;
int direction = 'd';
int score = 0;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void init_game() {
    system("cls");
    snake[0] = (Position){WIDTH / 2, HEIGHT / 2};
    for (int i = 1; i < snake_length; i++) {
        snake[i] = (Position){snake[i-1].x - 1, snake[i-1].y};
    }
    srand(time(0));
    food.x = rand() % (WIDTH - 2) + 1;
    food.y = rand() % (HEIGHT - 2) + 1;
}

void draw_game() {
    system("cls");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                printf("#");
            } else if (i == food.y && j == food.x) {
                printf("*");
            } else {
                int is_snake = 0;
                for (int k = 0; k < snake_length; k++) {
                    if (snake[k].x == j && snake[k].y == i) {
                        printf("O");
                        is_snake = 1;
                        break;
                    }
                }
                if (!is_snake) printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void game_over() {
    system("cls");
    printf("\nGAME OVER!\n");
    printf("Final Score: %d\n", score);
    printf("Press any key to return to Main Menu...\n");
    _getch();
    main_menu();
}

void move_snake() {
    Position new_head = snake[0];
    switch (direction) {
        case 'w': new_head.y--; break;
        case 's': new_head.y++; break;
        case 'a': new_head.x--; break;
        case 'd': new_head.x++; break;
    }
    if (new_head.x == 0 || new_head.x == WIDTH - 1 ||
        new_head.y == 0 || new_head.y == HEIGHT - 1) {
        game_over();
    }
    for (int i = 1; i < snake_length; i++) {
        if (snake[i].x == new_head.x && snake[i].y == new_head.y) {
            game_over();
        }
    }
    for (int i = snake_length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    snake[0] = new_head;
    if (new_head.x == food.x && new_head.y == food.y) {
        snake_length++;
        score++;
        food.x = rand() % (WIDTH - 2) + 1;
        food.y = rand() % (HEIGHT - 2) + 1;
    }
}

void game_loop() {
    init_game();
    while (1) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {
                direction = ch;
            }
        }
        move_snake();
        draw_game();
        Sleep(150);
    }
}

void main_menu() {
    system("cls");
    printf("SNAKE GAME\n");
    printf("1. Start Game\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
    char choice = _getch();
    if (choice == '1') {
        game_loop();
    } else if (choice == '2') {
        exit(0);
    } else {
        main_menu();
    }
}
