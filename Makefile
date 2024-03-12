GAME = so_long
FILES = map_checker.c rendring.c so_long.c etc.c player.c scaner.c finish_game.c animatoins.c
OBJ_FILES = $(FILES:.c=.o)
frameworks = -framework OpenGL -framework AppKit libmlx.a
C_flags =  -Wall -Wextra -Werror

$(GAME): $(OBJ_FILES)
	cc $(C_flags) $(frameworks) $(OBJ_FILES) -o $(GAME)

all: $(B_GAME) $(GAME)

clean:
	rm -f $(OBJ_FILES)
fclean: clean
	rm -f $(GAME)
re: fclean $(GAME)
