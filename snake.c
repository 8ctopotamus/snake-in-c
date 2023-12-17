#include <stdio.h>

#define cols 20
#define rows 20

char board[cols * rows];

void fill_board() {
	int x, y;
	for (x = 0; x < rows; x++) {
		for (y = 0; y < cols; y++) {
			// detect border
			if (x == 0 || y == 0 || x == cols - 1 || y == rows - 1) {
				board[y * cols + x] = '#';
			}
		}
	}
}

void print_board() {
	int x, y;
	for (x = 0; x < rows; x++) {
		for (y = 0; y < cols; y++) {
			putchar(board[y * cols + x]);
		}
		putchar('\n');
	}
}

int main(int argc, char **argv) {
	fill_board();
	print_board();

	return 0;
}
