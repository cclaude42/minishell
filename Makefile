NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/includes/

LIBFT = -L libft -lft

HEADER = minishell.h

FILES = minishell builtin bin parse echo cd pwd export unset env

SRC = $(addsuffix .c, $(addprefix srcs/, $(FILES)))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: re
	./minishell

norm:
	norminette $(SRC) includes/$(HEADER)

.PHONY: clean fclean re norm test
