main: main.o star.o bullet.o player.o utils.o
	gcc -rpath /usr/local/lib -L/usr/local/lib -lSDL3.0  bin/*.o -o main 
	./main

main.o: src/main.c
	mkdir -p bin
	gcc -I/usr/local/include/SDL3 -c src/main.c -o bin/main.o

star.o: src/star.c
	gcc -I/usr/local/include/SDL3 -c src/star.c -o bin/star.o

bullet.o: src/bullet.c
	gcc -I/usr/local/include/SDL3 -c src/bullet.c -o bin/bullet.o

player.o: src/player.c
	gcc -I/usr/local/include/SDL3 -c src/player.c -o bin/player.o

utils.o: src/utils.c
	gcc -I/usr/local/include/SDL3 -c src/utils.c -o bin/utils.o


test: test.o
	gcc  test.o -o test
	./test

test.o: test.c
	gcc -c test.c
	