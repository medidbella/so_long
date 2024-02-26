GAME = so_long
FILES = map_checker.c rendring.c so_long.c etc.c player.c scaner.c animatoins.c finish_game.c
mlx = -lmlx -framework OpenGL -framework AppKit 
C_flags = -Wall -Wextra -Werror

all: $(GAME)

$(GAME): $(FILES)
	cc $(C_flags) $(mlx) $(FILES) -o $(GAME)
clean:
	rm -f $(GAME)
fclean: clean

re: clean all