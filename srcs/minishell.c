#include "minishell.h"

int		main(void)
{
	t_mini  mini;
    char    *line;

	mini.run = true;
	while (mini.run)
	{
		write(1, "minishell > ", 13);
		get_next_line(0, &line);
		mini.start = get_args(line);
		ft_memdel(line);
		if (mini.start == NULL)
			;
		else if (ft_strcmp(mini.start->tok, "exit") == 0)
			mini.run = false;
		else
			;
		del_args(args);
	}
	return (0);
}