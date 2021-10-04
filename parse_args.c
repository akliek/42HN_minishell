/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:07:44 by akliek            #+#    #+#             */
/*   Updated: 2021/10/01 18:15:01 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_next_arg(char *str, int i)
{
	char	c;

	while (str[i] == ' ')
		i++;
	i++;
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
		i++;
	if (str[i] == '\'' || str[i] == '\"')
	{
		c = str[i];
		i++;
		while (str[i] != c)
			i++;
		i++;
	}
	while (str[i] && str[i] != ' ')
		i++;
	if (str[i] == ' ' || str[i] == 0)
		return (i);
	find_next_arg(str, i);
	return (i);
}

static int	count_args(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		j = find_next_arg(str, j);
		if (str[j])
			j++;
		i++;
	}
	return (i);
}

char	**fill_the_damn_malloc(char	*str, char **ret, int i, int j)
{
	int		k;
	char	*tmp;

	k = 0;
	while (str[i])
	{
		j = find_next_arg(str, j);
		if (str[j])
			j++;
		while (str[i] == ' ')
			i++;
		tmp = ft_substr(str, i, j - i);
		if (ft_strchr(tmp, '='))
		{
			clean_str(tmp);
			tmp = change_to_env_var(ft_substr(str, i, j - i));
			ret[k] = clean_quotes(tmp);
			k++;
		}
		clean_str(tmp);
		i = j;
	}
	ret[k] = 0;
	return (ret);
}

char	**parse_args_export(char *str)
{
	char	**ret;

	ret = (char **)malloc((count_args(str) + 1) * sizeof(char *));
	ret = fill_the_damn_malloc(str, ret, 0, 0);
	return (ret);
}

char	**parse_args(char *str)
{
	int		i;
	char	*tmp;
	char	**args;

	i = 0;
	args = ft_split(str, ' ');
	while (args[i])
	{
		tmp = ft_strdup(args[i]);
		clean_str(args[i]);
		args[i] = clean_quotes(tmp);
		clean_str(tmp);
		i++;
	}
	return (args);
}
