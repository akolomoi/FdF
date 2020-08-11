NAME = fdf

SRCNAME =	artist.c \
			events.c \
			fdf_input.c \
			fdf.c \
			info.c \
			new_win.c \
			parser.c \
			plot_line.c \
			rot_funcs.c \
			utils.c

SRC = $(addprefix src/, $(SRCNAME))
OBJECT = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
HDIR = include
LIBFT = libft/libft.a

.SILENT:

all: $(NAME)

$(NAME): $(OBJECT)
	make -C libft
	gcc $(OBJECT) $(LIBFT) -l mlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "(*) fdf"

%.o: %.c
	gcc $(FLAGS) -o $@ -c $< -I $(HDIR)
	@echo "(+) $@"

clean:
	rm -f $(OBJECT)
	make clean -C libft
	@echo "(-) *.o"

fclean: clean
	make fclean -C libft
	rm -f $(NAME)
	@echo "(-) libft"
	@echo "(-) fdf"

re: fclean all