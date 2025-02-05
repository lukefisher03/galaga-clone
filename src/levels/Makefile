CC = clang
CFLAGS = -g -I/usr/local/include/SDL3
BIN = ../../bin
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

%.o : %.c 
	$(CC) -c $< -o $(BIN)/$@ $(CFLAGS)

game: $(OBJ)
	echo "BUILT LEVELS DIRECTORY"