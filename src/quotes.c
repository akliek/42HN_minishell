/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:12:47 by akliek            #+#    #+#             */
/*   Updated: 2021/10/02 13:06:20 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(char *str, char c)
{
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == c)
			quotes++;
		i++;
	}
	free(str);
	return (quotes);
}

char	get_first_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (str[i]);
		i++;
	}
	return (0);
}

static int	get_quotes(char *str)
{
	int		i;
	int		ret;
	char	c;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] != c)
				i++;
			ret += 2;
		}
		i++;
	}
	return (ret);
}

static char	*clean_quotes_loop(char *str, char *ret, int i, int j)
{
	char	c;

	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
			{
				ret[j] = str[i];
				i++;
				j++;
			}
		}
		else
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = 0;
	return (ret);
}

char	*clean_quotes(char *str)
{
	char	*ret;

	ret = malloc(ft_strlen(str) - get_quotes(str) + 1);
	ret = clean_quotes_loop(str, ret, 0, 0);
	return (ret);
}
