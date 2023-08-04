all: compile link

CFLAGS=-Wall -Wextra

compile:
	g++ ${CFLAGS} -I src/include -c main.cpp
link:
	g++ ${CFLAGS} main.o -o main -L src/lib -l Sfml-graphics -l sfml-window -l sfml-system