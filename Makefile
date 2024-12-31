main: main.o star.o bullet.o player.o utils.o quadtree.o enemy.o
	gcc -g -rpath /usr/local/lib -L/usr/local/lib -lSDL3.0  bin/*.o -o main 

test: test.o quadtree.o
	gcc -rpath /usr/local/lib -L/usr/local/lib -lSDL3.0 test.o bin/quadtree.o bin/enemy.o -o test
	./test > output.log


main.o: src/main.c
	mkdir -p bin
	gcc -g -I/usr/local/include/SDL3 -c src/main.c -o bin/main.o

star.o: src/star.c
	gcc -g -I/usr/local/include/SDL3 -c src/star.c -o bin/star.o

bullet.o: src/bullet.c
	gcc -g -I/usr/local/include/SDL3 -c src/bullet.c -o bin/bullet.o

player.o: src/player.c
	gcc -g -I/usr/local/include/SDL3 -c src/player.c -o bin/player.o

utils.o: src/utils.c
	gcc -g -I/usr/local/include/SDL3 -c src/utils.c -o bin/utils.o

enemy.o: src/enemy.c
	gcc -g -I/usr/local/include/SDL3 -c src/enemy.c -o bin/enemy.o

quadtree.o: src/quadtree.c
	gcc -g -I/usr/local/include/SDL3 -c src/quadtree.c -o bin/quadtree.o

test.o: test.c
	gcc -g -c test.c -o test.o