#include "minishell.h"

void	print_args(t_token *start)
{
	int		i = 0;
	char	*s[8] = {"(EMPTY)", "(CMD)", "(ARG)", "(APPEND)",
					"(TRUNC)", "(REDIR)", "(PIPE)", "(END)"};

	while (start->next)
	{
		printf("#%d %-8s [%s]\n", i++, s[start->type], start->tok);
		start = start->next;
	}
	printf("#%d %-8s [%s]\n", i++, s[start->type], start->tok);
}

int		main(void)
{
	t_mini  mini;
    char    *line;

	mini.run = 1;
	while (mini.run)
	{
		write(1, "minishell > ", 13);
		get_next_line(0, &line);
		mini.start = get_args(line);
		ft_memdel(line);
		print_args(mini.start);
		if (mini.start == NULL)
			;
		else if (ft_strcmp(mini.start->tok, "exit") == 0)
			mini.run = 0;
		else
			;
		del_args(mini.start);
	}
	return (0);
}
