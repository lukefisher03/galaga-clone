main: main.o star.o bullet.o player.o utils.o
	gcc -rpath /usr/local/lib -L/usr/local/lib -lSDL3.0  bin/*.o -o main 
	./main

main.o: main.c
	mkdir -p bin
	gcc -I/usr/local/include/SDL3 -c main.c -o bin/main.o

star.o: star.c
	gcc -I/usr/local/include/SDL3 -c star.c -o bin/star.o

bullet.o: bullet.c
	gcc -I/usr/local/include/SDL3 -c bullet.c -o bin/bullet.o

player.o: player.c
	gcc -I/usr/local/include/SDL3 -c player.c -o bin/player.o

utils.o: utils.c
	gcc -I/usr/local/include/SDL3 -c utils.c -o bin/utils.o


test: test.o
	gcc  test.o -o test
	./test

test.o: test.c
	gcc -c test.c
	