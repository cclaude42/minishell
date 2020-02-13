NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/includes/

LIBFT = -L libft -lft

HEADER = minishell.h

FILES = minishell builtin bin parse echo cd pwd export unset env minitools

SRC = $(addsuffix .c, $(addprefix srcs/, $(FILES)))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: re
	./minishell

norm:
	norminette $(SRC) includes/$(HEADER)

lftre:
	make re -C libft/

.PHONY: clean fclean re norm test
