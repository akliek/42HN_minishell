/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 13:56:04 by jhagedor          #+#    #+#             */
/*   Updated: 2021/10/02 12:03:34 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_last_slash(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = -1;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '/')
			res = i;
		i++;
	}
	return (res);
}

static char	**get_args(char *str)
{
	int		i;
	char	**args;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	args = parse_args(str + i);
	return (args);
}

char	**get_executable(char *str)
{
	int		i;
	int		j;
	char	**args;
	char	**res;

	j = 0;
	i = find_last_slash(str) + 1;
	args = get_args(str);
	while (args[j])
		j++;
	res = (char **)malloc((j + 2) * sizeof(char *));
	j = i;
	while (str[j] && str[j] != ' ')
		j++;
	res[0] = ft_substr(str, i, j - i);
	j = 0;
	while (args[j])
	{
		res[j + 1] = ft_strdup(args[j]);
		j++;
	}
	res[j + 1] = NULL;
	return (res);
}
