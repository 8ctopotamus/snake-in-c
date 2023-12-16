#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

void main() {
	WINDOW* win = initscr();
	keypad(win, true);
	nodelay(win, true);
	noecho();
	curse_set(0);

	int posX = 0;
	int posY = 0;
	int dirX = 1;
	int dirY = 0;
	int foodX = rand() % 20;
	int foodY = rand() % 20;
	
	while(true) {
		// keyboard input
		int pressed = wgetch(win);
		
		if (pressed == KEY_LEFT) {
			dirX = -1;
			dirY = 0;
		}
		if (pressed == KEY_RIGHT) {
			dirX = 1;
			dirY = 0;
		}
		if (pressed == KEY_UP) {
			dirX = 0;
			dirY = -1;
		}
		if (pressed == KEY_DOWN) {
			dirX = 0;
			dirY = 1;
		}
		
		// movement
		posX += dirX;
		posY += dirY;
		erase();
		
		// draw
		mvaddstr(posY, posX, "*");
		mvaddstr(foodY, foodX, "&");
		
		usleep(100000);

		// eating food
		if (foodX == posX && foodY == posY) {
			foodX = rand() % 20;
			foodY = rand() % 20;
		}
	}

	endwin();
}
