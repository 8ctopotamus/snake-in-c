all: build

build: snake.c
	cc snake.c -o snake

run: 
ifeq ($(OS), Windows_NT) 
	./snake.exe
else
	./snake
endif