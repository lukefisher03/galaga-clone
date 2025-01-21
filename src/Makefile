CC = clang
CFLAGS = -g -I/usr/local/include/SDL3
BIN = ../bin
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

%.o : %.c 
	$(CC) -c $< -o $(BIN)/$@ $(CFLAGS)

game: $(OBJ)
	echo "BUILT MAIN DIRECTORY"
	$(MAKE) -C levels
	gcc -g -rpath /usr/local/lib -L/usr/local/lib -lSDL3.0  $(BIN)/*.o -o main 

dir:
	mkdir -p $(BIN)

all: dir game