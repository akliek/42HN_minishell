/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:22:25 by akliek            #+#    #+#             */
/*   Updated: 2021/10/02 15:30:50 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data	*init_struct(t_data *data)
{
	data->args = NULL;
	data->cmd = NULL;
	data->echo = NULL;
	data->redirections = NULL;
	return (data);
}

char	*get_cmd(char *str)
{
	int		i;
	char	*arg;
	char	*cmd;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	arg = ft_substr(str, 0, i);
	cmd = clean_quotes(arg);
	free(arg);
	return (cmd);
}

char	*get_file(char *str, char **tmp, t_type type)
{
	int		i;
	char	*arg;
	char	*file;

	i = 0;
	if (type == OUTPUT || type == OUTPUT)
		str++;
	else
		str += 2;
	while (*str && *str == ' ')
		str++;
	while (str[i] && str[i] != ' ')
		i++;
	arg = ft_substr(str, 0, i);
	file = clean_quotes(arg);
	free(arg);
	*tmp = ft_substr(str, i, ft_strlen(str) - i);
	return (file);
}

t_data	*parse_cmd(char *str)
{
	t_data			*data;
	t_redirection	*tmp;

	data = (t_data *)malloc(sizeof(t_data));
	data = init_struct(data);
	data->cmd = get_cmd(str);
	data->redirections = get_redirection(&str, get_first_quotes(str));
	tmp = data->redirections;
	while (data->redirections->type != NONE)
	{
		data->redirections->next = get_redirection(&str, get_first_quotes(str));
		data->redirections = data->redirections->next;
	}
	data->redirections = tmp;
	while (*str && *str != ' ')
		str++;
	while (*str && *str == ' ')
		str++;
	if (!ft_strcmp(data->cmd, "echo"))
		data->echo = get_echo(str);
	else if (!ft_strcmp(data->cmd, "export"))
		data->args = parse_args_export(str);
	else
		data->args = parse_args(str);
	return (data);
}
