/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:02:16 by akliek            #+#    #+#             */
/*   Updated: 2021/10/01 14:09:14 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_sapes(char *str)
{
	int	spaces;

	spaces = 0;
	while (*str)
	{
		if (*str == ' ')
			spaces++;
		str++;
	}
	return (spaces);
}

char	*clean_first_last_spaces(char *str)
{
	int		i;
	char	*res;

	while (*str && *str == ' ')
		str++;
	i = ft_strlen(str) - 1;
	while (str[i] == ' ')
		i--;
	res = ft_substr(str, 0, i + 1);
	return (res);
}

char	*clean_spaces(char *str)
{
	int		i;
	int		spaces;
	char	*res;

	i = 0;
	spaces = count_sapes(str);
	res = (char *)malloc((ft_strlen(str) - spaces) * sizeof(char));
	while (*str)
	{
		if (*str != ' ')
		{
			res[i] = *str;
			i++;
		}
		str++;
	}
	res[i] = '\0';
	return (res);
}
