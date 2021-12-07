/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:11:28 by akliek            #+#    #+#             */
/*   Updated: 2021/10/04 10:16:26 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_new_args(char **env, char **args, int i)
{
	int	j;

	j = 0;
	while (args[j])
	{
		env[i] = ft_strdup(args[j]);
		j++;
		i++;
	}
	env[i] = NULL;
	return (env);
}

static int	args_in_env(char **args, char *env)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j] == env[j] && env[j])
			j++;
		if (env[j] == '=')
			return (1);
		i++;
	}
	return (0);
}

static bool	arg_is_new(char *str, char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while ((args[i][j] == str[j]) && str[j] != '=')
			j++;
		if ((args[i][j] == str[j]) && (args[i][j] == '='))
			return (0);
		i++;
	}
	return (1);
}

char	**add_new_str(char **args, char **env)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	if (!args)
		return (env);
	tmp = arr_str_dup(env);
	clean_str_arr(env);
	env = (char **)malloc((arr_strlen(args)
				+ arr_strlen(tmp) + 1) * sizeof(char *));
	while (tmp[j])
	{
		if (arg_is_new(tmp[j], args))
		{
			env[i] = ft_strdup(tmp[j]);
			i++;
		}
		j++;
	}
	clean_str_arr(tmp);
	env = add_new_args(env, args, i);
	return (env);
}

char	**delete_env_var(char **args, char **env)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = arr_str_dup(env);
	clean_str_arr(env);
	env = (char **)malloc((arr_strlen(tmp)
				- arr_strlen(args) + 1) * sizeof(char *));
	while (tmp[i])
	{
		if (!args_in_env(args, tmp[i]))
		{
			env[j] = ft_strdup(tmp[i]);
			j++;
		}
		i++;
	}
	env[j] = NULL;
	clean_str_arr(tmp);
	return (env);
}
