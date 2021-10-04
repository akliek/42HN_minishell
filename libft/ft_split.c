/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:44:41 by akliek            #+#    #+#             */
/*   Updated: 2021/09/20 16:43:32 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_splits(char const *s, char c)
{
	int		splits;
	int		check;
	int		i;

	i = 0;
	check = 0;
	splits = 1;
	if (!*s)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
			check = 1;
		if (s[i] == c && check == 1)
		{
			check = 0;
			splits++;
		}
		i++;
	}
	if (s[i - 1] == c)
		splits--;
	return (splits);
}

static char	*memory(char const *s, char c, char *res)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	res = (char *)malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (*s && *s != c)
	{
		res[j] = *s;
		j++;
		s++;
	}
	res[j] = '\0';
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		j;
	int		splits;

	j = 0;
	if (!s)
		return (NULL);
	splits = count_splits(s, c);
	res = (char **)malloc((splits + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (*s && j < splits)
	{
		if (*s != c)
		{
			res[j] = memory(s, c, res[j]);
			while (*s && *s != c)
				s++;
			j++;
		}
		while (*s && *s == c)
			s++;
	}
	res[j] = NULL;
	return (res);
}
