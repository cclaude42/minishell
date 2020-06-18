NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/includes/

LIBFT = -L libft -lft

HEADER = minishell.h

BUILTINS = cd echo env export pwd

ENV = env

EXEC = bin builtin exec

MAIN = minishell redir

PARSING = line tokens tools

TOOLS = fd free token

SRC = $(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  $(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \

OBJ = $(SRC:c=o)

all: yellow $(NAME)

yellow:
	@echo "\033[0;33mGenerating minishell binaries..."

$(NAME): $(OBJ)
	@echo
	@make -C libft/
	@echo "\033[0;32mCompiling minishell..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "\033[0m"

%.o: %.c
	@printf "${CC} ${CFLAGS} -c $< -o $@        \r"
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\033[0;31mCleaning libft..."
	@make clean -C libft/
	@echo
	@echo "Removing binaries..."
	rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C libft/
	@echo
	@echo "Removing binaries..."
	rm -f $(OBJ)
	@echo
	@echo "Removing executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

test: all
	./minishell

norm:
	norminette $(SRC) includes/$(HEADER)

.PHONY: clean fclean re test norm yellow
