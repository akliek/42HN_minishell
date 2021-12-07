/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:59:26 by akliek            #+#    #+#             */
/*   Updated: 2021/10/02 11:47:26 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_message(t_error error)
{
	if (error == PIPE)
	{
		perror("minishell: idk, dude, smth wrong");
		exit(1);
	}
	else if (error == FORK)
	{
		perror("minishell: idk, dude, smth wrong");
		exit(1);
	}
	else if (error == EXECVE)
	{
		perror("minishell: Wtf does your command mean???");
		exit(127);
	}
	else if (error == OPEN)
		perror("minishell: dude pls");
	else if (error == EXIT_ARG)
	{
		perror("minishell: you are doing some weird stuff \\_(-_-)_/");
		get_exit_status(1, 1);
	}
	else
		perror("minishell: duuuude, you are definitely drunk");
	return (1);
}
