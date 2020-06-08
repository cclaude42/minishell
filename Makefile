NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/includes/

LIBFT = -L libft -lft

HEADER = minishell.h

FILES = minishell parse

BUILTINS = echo pwd

SRC = $(addsuffix .c, $(addprefix srcs/, $(FILES))) \
	  $(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS)))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	make clean -C libft/
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all

test: re
	./minishell

norm:
	norminette $(SRC) includes/$(HEADER)

.PHONY: clean fclean re norm test
