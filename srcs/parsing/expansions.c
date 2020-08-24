/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:06:28 by macrespo          #+#    #+#             */
/*   Updated: 2020/08/24 20:36:11 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		varlcpy(char *new_arg, const char *env_value, int pos)
{
	int		i;

	i = 0;
	while (env_value[i])
		new_arg[pos++] = env_value[i++];
	return (i);
}

static void		insert_var(t_expansions *ex, char *arg, t_env *env, int ret)
{
	char	*env_value;

	env_value = get_var_value(arg, ex->j, env, ret);
	ex->i += env_value ? varlcpy(ex->new_arg, env_value, ex->i) : 0;
	ft_memdel(env_value);
	arg[ex->j] == '?' ? ex->j++ : 0;
	if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?')
	{
		while (is_env_char(arg[ex->j]) == 1)
			ex->j++;
	}
	else
	{
		if (arg[ex->j - 1] != '?')
			ex->j++;
	}
}

char			*expansions(char *arg, t_env *env, int ret)
{
	t_expansions	ex;
	int				new_arg_len;

	new_arg_len = arg_alloc_len(arg, env, ret);
	if (!(ex.new_arg = malloc(sizeof(char) * new_arg_len + 1)))
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < new_arg_len && arg[ex.j])
	{
		while (arg[ex.j] == EXPANSION)
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0)
			&& arg[ex.j] != '?')
				ex.new_arg[ex.i++] = '$';
			else
				insert_var(&ex, arg, env, ret);
		}
		ex.new_arg[ex.i++] = arg[ex.j++];
	}
	ex.new_arg[ex.i] = '\0';
	return (ex.new_arg);
}
