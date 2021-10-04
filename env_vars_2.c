/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:00:29 by akliek            #+#    #+#             */
/*   Updated: 2021/10/02 15:25:39 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_value(char *env_var, int j)
{
	int	i;

	i = 0;
	while (g_env[i] && ft_strncmp(g_env[i], env_var, j))
		i++;
	free(env_var);
	if (!g_env[i] || j == 0)
		env_var = ft_strdup("");
	else
		env_var = ft_strdup(g_env[i] + j + 1);
	return (env_var);
}

static char	*replace(char *env_var, char *arg, int i, int j)
{
	char	*tmp1;
	char	*tmp2;	

	tmp1 = ft_substr(arg, 0, i - 1);
	tmp2 = ft_strdup(arg + i + j);
	if (!ft_strcmp(env_var, "?"))
		env_var = ft_itoa(get_exit_status(0, 0));
	else
		env_var = get_value(env_var, j);
	arg = ft_strjoin(tmp1, env_var);
	free(tmp1);
	tmp1 = ft_strdup(arg);
	free(arg);
	arg = ft_strjoin(tmp1, tmp2);
	free(tmp2);
	free(env_var);
	arg = change_to_env_var(arg);
	return (arg);
}

char	*change_to_env_var(char *arg)
{
	int		i;
	int		j;

	i = 0;
	while (arg[i])
	{
		if (arg[i + 1] && arg[i] == '$' && (ft_isalnum(arg[i + 1])
				|| (arg[i + 1] == '\"' && arg[i - 1] != '\"')
				|| (arg[i + 1] == '\'' && arg[i - 1] != '\'')
				|| (arg[i + 1] == '?')))
		{
			j = 0;
			while (++i && arg[i] && ft_isalnum(arg[i]))
				j++;
			i -= j;
			if (arg[i] == '?')
				arg = replace("?", arg, i, 1);
			else
				arg = replace(ft_substr(arg, i, j), arg, i, j);
			break ;
		}
		i++;
	}
	return (arg);
}

void	add_new_args(char **env, char **args, int i)
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
}

void	print_exported_vars(void)
{
	int		i;
	int		j;
	char	**export;

	i = 0;
	export = sort_strings(g_env);
	while (export[i])
	{
		if (!ft_strcmp(export[i], "OLDPWD"))
			i++;
		printf("declare -x ");
		j = 0;
		while (export[i][j] != '=')
		{
			printf("%c", export[i][j]);
			j++;
		}
		printf("=\"%s\"\n", export[i] + j + 1);
		i++;
	}
	clean_str_arr(export);
}
