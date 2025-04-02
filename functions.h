#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "position.h"

#define WIDTH 20  // Width of the game board
#define HEIGHT 10 // Height of the game board
#define INITIAL_LENGTH 3 // Initial length of the snake


// Global variables for game state
Position snake[WIDTH * HEIGHT]; // Array to store snake's body
int snake_length = INITIAL_LENGTH; // Current length of the snake
Position food; // Position of the food
int direction = 'd'; // Initial movement direction (right)
int score = 0; // Player's score

// Function to move cursor to a specific console position
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to initialize the game
void init_game() {
    system("cls"); // Clear the console screen
    
    // Place the snake in the middle of the board
    snake[0] = (Position){WIDTH / 2, HEIGHT / 2};
    for (int i = 1; i < snake_length; i++) {
        snake[i] = (Position){snake[i-1].x - 1, snake[i-1].y}; // Extending the snake to the left initially
    }
    
    srand(time(0)); // Seed random number generator
    food.x = rand() % (WIDTH - 2) + 1; // Generate random food position within the board
    food.y = rand() % (HEIGHT - 2) + 1;
}

// Function to draw the game board
void draw_game() {
    system("cls"); // Clear the screen before redrawing
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                printf("#"); // Walls of the game board
            } else if (i == food.y && j == food.x) {
                printf("*"); // Food symbol
            } else {
                int is_snake = 0;
                for (int k = 0; k < snake_length; k++) {
                    if (snake[k].x == j && snake[k].y == i) {
                        printf("O"); // Snake body
                        is_snake = 1;
                        break;
                    }
                }
                if (!is_snake) printf(" "); // Empty space
            }
        }
        printf("\n"); // Move to the next row
    }
    printf("Score: %d\n", score); // Display current score
}

// Function to move the snake
void move_snake() {
    Position new_head = snake[0]; // Get the current head position
    
    // Move the snake in the current direction
    switch (direction) {
        case 'w': new_head.y--; break; // Move up
        case 's': new_head.y++; break; // Move down
        case 'a': new_head.x--; break; // Move left
        case 'd': new_head.x++; break; // Move right
    }
    
    // Check for collision with walls
    if (new_head.x == 0 || new_head.x == WIDTH - 1 ||
        new_head.y == 0 || new_head.y == HEIGHT - 1) {
        printf("Game Over! Final Score: %d\n", score);
        exit(0);
    }
    
    // Check for collision with itself
    for (int i = 1; i < snake_length; i++) {
        if (snake[i].x == new_head.x && snake[i].y == new_head.y) {
            printf("Game Over! Final Score: %d\n", score);
            exit(0);
        }
    }
    
    // Move the snake by shifting its body forward
    for (int i = snake_length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    snake[0] = new_head; // Update the new head position
    
    // Check if the snake ate the food
    if (new_head.x == food.x && new_head.y == food.y) {
        snake_length++; // Increase snake length
        score++; // Increase score
        
        // Generate new food position
        food.x = rand() % (WIDTH - 2) + 1;
        food.y = rand() % (HEIGHT - 2) + 1;
    }
}

// Main game loop
void game_loop() {
    while (1) {
        if (_kbhit()) { // Check if a key was pressed
            char ch = _getch(); // Get the key
            if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {
                direction = ch; // Update the movement direction
            }
        }
        move_snake(); // Move the snake
        draw_game(); // Redraw the game board
        Sleep(150); // Slow down the game loop
    }
}