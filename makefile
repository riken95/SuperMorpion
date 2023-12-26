CC = gcc
CFLAGS = -Wall -Wextra -g
SRCDIR = superMorpion
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:.c=.o)
EXEC = myprogram

all: $(EXEC)

$(EXEC): $(OBJ) main.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) main.o $(EXEC)

run: clean all
	./$(EXEC)
