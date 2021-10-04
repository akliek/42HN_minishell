/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:17:25 by akliek            #+#    #+#             */
/*   Updated: 2021/10/01 14:28:26 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arr_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	clean_str_arr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		clean_str(s[i]);
		i++;
	}
	free(s);
	s = NULL;
}

void	print_arr_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

char	**arr_str_dup(char **env)
{
	int		i;
	char	**res;

	res = (char **)malloc((arr_strlen(env) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (env[i])
	{
		res[i] = ft_strdup(env[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
