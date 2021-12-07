/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:10:01 by akliek            #+#    #+#             */
/*   Updated: 2021/10/02 15:21:14 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_redirection *redirection)
{
	char			*input;

	while (redirection)
	{
		if (redirection->type == HEREDOC)
		{
			while (1)
			{
				input = readline("> ");
				if (!ft_strcmp(input, redirection->file))
					break ;
				free(input);
			}
			free(input);
		}
		redirection = redirection->next;
	}
}

t_redirection	*init_redirection(t_redirection *red, char current, char next)
{
	red->file = NULL;
	if (current == '<' && next == '<')
		red->type = HEREDOC;
	else if (current == '>' && next == '>')
		red->type = DOUBLE_OUTPUT;
	else if (current == '<')
		red->type = INPUT;
	else if (current == '>')
		red->type = OUTPUT;
	else
		red->type = NONE;
	return (red);
}

t_redirection	*get_redirection(char **str, char q)
{
	int				i;
	char			*tmp1;
	char			*tmp2;
	t_redirection	*red;

	i = 0;
	red = (t_redirection *)malloc(sizeof(t_redirection));
	red = init_redirection(red, 'n', 'o');
	while ((*str)[i])
	{
		if (((*str)[i] == '<' || (*str)[i] == '>') && is_real(*str, q, i, 0))
		{
			red = init_redirection(red, (*str)[i], (*str)[i + 1]);
			tmp1 = ft_substr(*str, 0, i);
			red->file = get_file(*str + i, &tmp2, red->type);
			free(*str);
			*str = ft_strjoin(tmp1, tmp2);
			free(tmp1);
			free(tmp2);
			break ;
		}
		i++;
	}
	red->next = NULL;
	return (red);
}

static int	change_descriptor(t_redirection *redirection)
{
	int	fd;

	if (redirection->type == INPUT)
	{
		fd = open(redirection->file, O_RDONLY);
		if (fd == -1)
			return (error_message(OPEN));
		dup2(fd, 0);
	}
	else if (redirection->type == OUTPUT)
	{
		fd = open(redirection->file, O_RDWR | O_CREAT | O_TRUNC, 0664);
		dup2(fd, 1);
	}
	else if (redirection->type == DOUBLE_OUTPUT)
	{
		fd = open(redirection->file, O_RDWR | O_CREAT | O_APPEND, 0664);
		dup2(fd, 1);
	}
	return (0);
}

int	redirections(t_redirection *redirections)
{
	int	ex;

	while (redirections->next)
	{
		ex = change_descriptor(redirections);
		if (ex)
			return (ex);
		redirections = redirections->next;
	}
	return (0);
}
