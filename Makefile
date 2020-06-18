NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/includes/

LIBFT = -L libft -lft

HEADER = minishell.h

BUILTINS = cd echo env export pwd

ENV = env

EXEC = bin builtin exec

MINISHELL = minishell redir

PARSING = line tokens tools

TOOLS = fd free token

SRC = $(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix srcs/minishell/, $(MINISHELL))) \
	  $(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  $(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	@echo "\033[0;31mCleaning libft..."
	make clean -C libft/
	@echo
	@echo "Removing binaries..."
	rm -f $(OBJ)

fclean:
	@echo "\033[0;31mCleaning libft..."
	make fclean -C libft/
	@echo
	@echo "Cleaning binaries..."
	rm -f $(OBJ)
	@echo
	@echo "Cleaning executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

test: all
	./minishell

norm:
	norminette $(SRC) includes/$(HEADER)

.PHONY: clean fclean re test norm
