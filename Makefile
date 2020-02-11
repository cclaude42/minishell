NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -I includes/

LIBFT = -L libft -lft

HEADER = minishell.h

SRC = $(addsuffix .c, $(addprefix srcs/, minishell))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) -o $(NAME) $(LIBFT) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette $(SRC) $(HEADER)
