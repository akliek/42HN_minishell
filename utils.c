/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:25:26 by akliek            #+#    #+#             */
/*   Updated: 2021/10/02 15:37:36 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**swap_strings(char **str, int i, int j)
{
	char	*tmp;

	tmp = ft_strdup(str[i]);
	free(str[i]);
	str[i] = ft_strdup(str[j]);
	free(str[j]);
	str[j] = ft_strdup(tmp);
	free(tmp);
	return (str);
}

char	**sort_strings(char **env)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	str = arr_str_dup(env);
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (ft_strcmp(str[i], str[j]) > 0)
				str = swap_strings(str, i, j);
			j++;
		}
		i++;
	}
	return (str);
}

bool	is_number(char *s)
{
	if (!s)
		return (0);
	if (*s == '-')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s < 48 || *s > 57)
			return (0);
		s++;
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (((unsigned char)s1[i] || (unsigned char)s2[i]))
	{
		if (s1[i] != s2[i])
		{
			if ((unsigned char)s1[i] < (unsigned char)s2[i])
				return (-1);
			return (1);
		}
		i++;
	}
	return (0);
}
