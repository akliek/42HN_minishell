/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:26:04 by akliek            #+#    #+#             */
/*   Updated: 2021/10/01 15:35:06 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_str(char *s)
{
	free(s);
	s = NULL;
}

void	clean_node(t_redirection *red)
{
	if (red->file)
		free(red->file);
	free(red);
}

void	clean_struct(t_data *data)
{
	t_redirection	*tmp;

	if (data->cmd)
		clean_str(data->cmd);
	if (data->echo)
		clean_str_arr(data->echo);
	if (data->args)
		clean_str_arr(data->args);
	while (data->redirections)
	{
		tmp = data->redirections->next;
		clean_node(data->redirections);
		data->redirections = tmp;
	}
	free(data);
}
