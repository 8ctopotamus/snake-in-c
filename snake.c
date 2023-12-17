#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define cols 20
#define rows 20
#define SNAKE_MAX_LENGTH 256
#define foods 10

int isGameOver = 0;

char board[cols * rows];

struct Food {
	int x, y;
	int consumed;
};

struct Food food[foods];

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
	for (i = snake.length-1; i > 0; i--) {
		board[snake.parts[i].y * cols + snake.parts[i].x] = '*';
	}
	// head
	board[snake.parts[0].y * cols + snake.parts[0].x] = '@';
}

void move_snake(int deltaX, int deltaY) {
	// body
	int i;
	for (i = snake.length-1; i > 0; i--) {
		snake.parts[i] = snake.parts[i - 1];
	}
	// head
	snake.parts[0].x += deltaX;
	snake.parts[0].y += deltaY;
}

void draw_food() {
	int i;
	for (i = 0; i < foods; i++) {
		if ( !food[i].consumed ) {
			board[food[i].y * cols + food[i].x] = '.';
		}
	}
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

	printf("SNAKE | w,a,s,d to move. q to quit\n");
	printf("Score: %d\n", snake.length * 100);

	for (y = 0; y < rows; y++) {
		for (x = 0; x < cols; x++) {
			putchar(board[y * cols + x]);
		}
		putchar('\n');
	}

	int i;
	printf("headX: %d headY %d\n", snake.parts[0].x, snake.parts[0].y);

	for (i = 0; i < snake.length; i++) {
		printf("bodyX: %d bodyY %d\n", snake.parts[i].x, snake.parts[i].y);
		if ( snake.parts[0].x == snake.parts[i].x && 
				 snake.parts[0].y == snake.parts[i].y ) {
			printf("BODY HIT\n");
		}
	}

	printf("%d %d\n", snake.parts[0].x, snake.parts[0].y);
	printf("%d %d\n", snake.parts[1].x, snake.parts[1].y);
	printf("%d %d\n", snake.parts[2].x, snake.parts[2].y);
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

void setup_food() {
	int i;
	for (i = 0; i < foods; i++) {
		food[i].x = rand() % (cols - 2);
		food[i].y = rand() % (rows - 2);
		food[i].consumed = 0;
	}
}

void setup_snake() {
	snake.length = 1;
	snake.parts[0].x = rand() % (cols - 2);
	snake.parts[0].y = rand() % (rows - 2);
}

void game_rules() {
	int i;

	// consume food
	for (i = 0; i < foods; i++) {
		if (!food[i].consumed) {
			if ( // snake is head on a piece of food
				food[i].x == snake.parts[0].x && 
				food[i].y == snake.parts[0].y
			) {
				food[i].consumed = 1;
				snake.length++;
			}
		}
	}
	
	// wall hit
	if ( snake.parts[0].x == 0 || snake.parts[0].x == cols-1 ||
			 snake.parts[0].y == 0 || snake.parts[0].y == rows-1 ) {
		isGameOver = 1;
	}

	// body hit
	for (i = 1; i < snake.length; i++) {
		if ( snake.parts[0].x == snake.parts[i].x && 
				 snake.parts[0].y == snake.parts[i].y ) {
			isGameOver = 1;
		}
	}
}

void game_over() {
	printf("Game over, Final score: %d\n", snake.length * 100);
	printf("r to replay, q to quit\n");
	char c;
	while(1) {
		c = getch();
		if (c == 'r') {
			printf("TODO: replay");
			break;
		} else if (c == 'q') {
			exit(EXIT_SUCCESS);
		}
	};
}

int main(int argc, char **argv) {
	srand(time(0));
	
	setup_snake();
	setup_food();

	while (!isGameOver) {
		fill_board();
		draw_food();
		draw_snake();
		game_rules();
		print_board();
		if (!isGameOver) {
			read_keyboard();
		}
	}

	game_over();

	return 0;
}
