/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 19:41:53 by cclaude           #+#    #+#             */
/*   Updated: 2020/07/06 14:10:44 by anonymous        ###   ########.fr       */
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

# define BUFF_SIZE 4096
# define EXPANSION -36

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
	t_env			*env;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	int				ret;
	int				exit;
}				t_mini;

/* MINISHELL */
void	redir(t_mini *mini, t_token *token, int type);
void	input(t_mini *mini, t_token *token);
int		minipipe(t_mini *mini);
char	*expansions(const char *arg, t_env *env);

/* EXEC */
void	exec_cmd(t_mini *mini, t_token *token);
int		exec_bin(char **args, t_env *env);
int		is_builtin(char	*command);
int		exec_builtin(char **args, t_mini *mini);

/* BUILTINS */
int		ft_echo(char **args);
int		ft_cd(char **args, t_env *env);
int		ft_pwd(void);
int		ft_export(char **args, t_env *env);
void	ft_env(t_env *env);
int		env_add(const char *value, t_env *env);
char	*get_env_name(char *dest, const char *src);
int		is_in_env(t_env *env, char *args);
int		ft_export(char **args, t_env *env);
int		ft_unset(char **args, t_mini *mini);


/* PARSING */
void	parse(t_mini *mini);
t_token	*get_tokens(char *line);
void	squish_args(t_mini *mini);
int		is_last_valid_arg(t_token *token);
int		open_quotes(char *line, int index);
int		is_sep(char *line, int i);
int		ignore_sep(char *line, int i);

/* ENV */
char	*env_to_str(t_env *lst);
int		env_init(t_mini *mini, char **env_array);
char	*get_env_value(char *arg, t_env *env);
char	*env_value(char *env);
int		env_value_len(const char *env);
int		is_env_char(int c);
void    print_sorted_env(t_env *env);
size_t	size_env(t_env *lst);

/* FD TOOLS */
void	reset_std(t_mini *mini);
void	close_fds(t_mini *mini);
void	reset_fds(t_mini *mini);

/* FREE TOOLS */
void	free_token(t_token *start);
void	free_env(t_env *env);
void	free_tab(char **tab);

/* TOKEN TOOLS */
t_token	*next_sep(t_token *token, int skip);
t_token	*prev_sep(t_token *token, int skip);
t_token	*next_run(t_token *token, int skip);

/* TYPE TOOLS */
int		is_type(t_token *token, int type);
int		has_type(t_token *token, int type);
int		has_pipe(t_token *token);
t_token	*next_type(t_token *token, int type, int skip);

#endif
