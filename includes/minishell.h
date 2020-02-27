/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:33:33 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/27 13:00:56 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <limits.h>
# include "libft.h"



char		**command_parse(char *command);
int			is_builtin(char **args, char **env);
int			is_bin(char **args, char **env);
int			is_exit(char **args);
int			mini_echo(char **args);
int			mini_cd(char **args, char **env);
int			mini_pwd(char **args, char **env);
int			mini_export(char **args, char **env);
int			mini_unset(char **args, char **env);
int			mini_env(char **args, char **env);

char		*get_env(char **env, const char *var);
char		*path_join(const char *s1, const char *s2);
void		del_args(char **args);
#endif
