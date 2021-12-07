/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:16:23 by akliek            #+#    #+#             */
/*   Updated: 2021/09/30 11:15:57 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_option(char *str)
{
	str = clean_quotes(str);
	if (str[0] && str[1] && str[0] == '-' && str[1] == 'n'
		&& (str[2] == '\0' || str[2] == ' '))
		return (1);
	return (0);
}

static char	*get_arg(char *str)
{
	if (!*str)
		return (NULL);
	while (*str && (*str == '\"' || *str == '\''))
		str++;
	str++;
	while (*str && (*str == '\"' || *str == '\''))
		str++;
	str++;
	while (*str && (*str == '\"' || *str == '\''))
		str++;
	while (*str && *str == ' ')
		str++;
	if (*str == '\0')
		return (NULL);
	return (str);
}

static int	get_size(char *str)
{
	int	size;

	size = 2;
	if (get_option(str))
	{
		size++;
		if (get_arg(str))
			size++;
	}
	else if (*str)
		size++;
	return (size);
}

char	**get_echo(char *str)
{
	int		size;
	char	*arg;
	char	**echo;

	size = get_size(str);
	echo = (char **)malloc(size * sizeof(char *));
	echo[0] = ft_strdup("echo");
	if (get_option(str))
	{
		echo[1] = ft_strdup("-n");
		arg = get_arg(str);
		if (arg)
			echo[2] = clean_quotes(change_to_env_var(arg));
	}
	else if (*str)
		echo[1] = clean_quotes(change_to_env_var(str));
	echo[size - 1] = NULL;
	return (echo);
}
