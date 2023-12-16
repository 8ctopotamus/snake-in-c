all: build

build: snake.c
	cc snake.c -lncurses -o snake
