/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 19:41:53 by cclaude           #+#    #+#             */
/*   Updated: 2020/06/16 18:36:10 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
// # include <sys/types.h>
// # include <stdbool.h>
// # include <stdarg.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_mini
{
	t_token			*start;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	t_env			*env;
	int				run;
}				t_mini;

t_token			*get_args(char *line);
void			del_args(t_token *start);
void			parse(t_mini *mini);
void			del_tab(char **tab);
void			free_env_lst(t_env *env);
void			free_env_array(char **env);
int				lst_init(t_mini *mini, char **env);
char			*lst_to_str(t_env *lst);
/* BUILTINS */
int		ft_echo(char **args);
int		ft_cd(char **args, t_env *env);
int		ft_pwd(void);
int		ft_export(char **args, t_env *env);
void	ft_env(t_env *env);
/* BUILTINS UTILITIES */
int		is_builtin(char	*command);
int		exec_builtin(char **args, t_env *env);
#endif		