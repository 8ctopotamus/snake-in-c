#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define cols 20
#define rows 20
#define SNAKE_MAX_LENGTH 256

int isGameOver = 0;

char board[cols * rows];

struct SnakePart {
	int x, y;
};

struct Snake {
	int length;
	struct SnakePart parts[SNAKE_MAX_LENGTH];
};

struct Snake snake;

void draw_snake() {
	int i;
	// body
	for (i = snake.length - 1; i > 0; i--) {
		board[snake.parts[i].y * cols + snake.parts[i].x] = '*';
	}
	// head
	board[snake.parts[0].y * cols + snake.parts[0].x] = '@';
}

void move_snake(int deltaX, int deltaY) {
	// body
	int i;
	for (i = snake.length - 1; i > 0; i--) {
		snake.parts[i] = snake.parts[i - 1];
	}
	// head
	snake.parts[0].x += deltaX;
	snake.parts[0].y += deltaY;
}

void fill_board() {
	int x, y;
	for (y = 0; y < rows; y++) {
		for (x = 0; x < cols; x++) {
			int idx = y * cols + x;
			// detect border
			if (x == 0 || y == 0 || x == cols - 1 || y == rows - 1) {
				board[idx] = '#';
			} else {
				board[idx] = ' ';
			}
		}
	}
}

void clear_screen() {
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
		system("clear");
	#endif
	#if defined(_WIN32)
		system("cls");
	#endif
}

void print_board() {
	int x, y;

	clear_screen();

	for (y = 0; y < rows; y++) {
		for (x = 0; x < cols; x++) {
			putchar(board[y * cols + x]);
		}
		putchar('\n');
	}
}

void read_keyboard() {
	int ch = getch();
	switch(ch) {
		case 'w': move_snake( 0,-1); break;
		case 's': move_snake( 0, 1); break;
		case 'a': move_snake(-1, 0); break;
		case 'd': move_snake( 1, 0); break;        
		case 'q': exit(EXIT_SUCCESS); break;
	}
}

int main(int argc, char **argv) {
	
	snake.length = 3;
	snake.parts[0].x = 5;
	snake.parts[0].y = 5;
	snake.parts[1].x = 5;
	snake.parts[1].y = 6;
	snake.parts[2].x = 5;
	snake.parts[2].y = 7;

	while (!isGameOver) {
		fill_board();
		draw_snake();
		print_board();
		read_keyboard();
	}
	return 0;
}
