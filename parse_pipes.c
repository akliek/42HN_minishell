/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:17:52 by akliek            #+#    #+#             */
/*   Updated: 2021/10/02 12:31:38 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_real(char *str, char quote, int i, int k)
{
	int	n1;
	int	n2;

	n1 = count_quotes(ft_substr(str, k, i - k), quote);
	n2 = count_quotes(ft_strdup(str + i + 1), quote);
	if (n1 % 2 == 0 && n2 % 2 == 0)
		return (1);
	return (0);
}

int	count_real_pipes(char *str)
{
	int		i;
	int		k;
	int		pipes;
	char	quote;

	i = 0;
	k = 0;
	pipes = 0;
	quote = get_first_quotes(str);
	while (str[i])
	{
		if (str[i] == '|' && is_real(str, quote, i, k))
		{
			pipes++;
			quote = get_first_quotes(str + i);
			k = i + 1;
		}
		i++;
	}
	return (pipes);
}

static char	**parse_pipe_loop(char *input, char **res, int pipes, char quote)
{
	int		i[3];
	char	*tmp;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (pipes > 0)
	{
		if (input[i[0]] == '|' && is_real(input, quote, i[0], i[2]))
		{
			tmp = ft_substr(input, i[2], i[0] - i[2]);
			res[i[1]] = clean_first_last_spaces(tmp);
			clean_str(tmp);
			quote = get_first_quotes(input + i[0]);
			i[2] = i[0] + 1;
			pipes--;
			i[1]++;
		}
		i[0]++;
	}
	tmp = ft_strdup(input + i[0]);
	res[i[1]] = clean_first_last_spaces(tmp);
	clean_str(tmp);
	res[i[1] + 1] = NULL;
	return (res);
}

char	**parse_pipes(char *input)
{
	int		pipes;
	char	**res;
	char	quote;

	pipes = count_real_pipes(input);
	res = (char **)malloc((pipes + 2) * sizeof(char *));
	quote = get_first_quotes(input);
	res = parse_pipe_loop(input, res, pipes, quote);
	return (res);
}
