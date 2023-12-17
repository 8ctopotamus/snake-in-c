#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define cols 20
#define rows 20

int isGameOver = 0;

char board[cols * rows];

void fill_board() {
	int x, y;
	for (x = 0; x < rows; x++) {
		for (y = 0; y < cols; y++) {
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

	for (x = 0; x < rows; x++) {
		for (y = 0; y < cols; y++) {
			putchar(board[y * cols + x]);
		}
		putchar('\n');
	}
}

int snakeX = 5;
int snakeY = 5;
void draw_snake() {
	board[snakeY * cols + snakeX] = '@';
}

void move_snake(int deltaX, int deltaY) {
	snakeX += deltaX;
	snakeY += deltaY;
}

void read_keyboard() {
	int ch = getch();
	switch(ch) {
		case 'w': move_snake(0, -1); break;
		case 's': move_snake(0, 1); break;
		case 'a': move_snake(-1, 0); break;
		case 'd': move_snake(1, 0); break;
		case 'q': exit(EXIT_SUCCESS);
	}
}

int main(int argc, char **argv) {
	while (!isGameOver) {
		fill_board();
		draw_snake();
		print_board();
		read_keyboard();
	}
	return 0;
}
