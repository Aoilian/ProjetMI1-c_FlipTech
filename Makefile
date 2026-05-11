CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -MMD -MP -fsanitize=address,undefined -g -O0 -fno-omit-frame-pointer

SRCDIR := src 
SRC := src/main.c src/score.c src/cartes.c src/manche.c src/affichage.c
OBJ := $(SRC:%.c=build/%.o)
DEP := $(SRC:%.c=build/%.d)

EXEC = programme

.PHONY: all clean fclean re

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -fsanitize=address,undefined

build/%.o: %.c
	mkdir -p build/src
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(EXEC)

re: fclean all