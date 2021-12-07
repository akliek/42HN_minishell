/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:13:51 by akliek            #+#    #+#             */
/*   Updated: 2021/10/04 10:28:27 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_process(int *fd, int *tmp)
{
	int	ex;

	wait(&ex);
	signal(SIGINT, handle_sigint);
	get_exit_status(ex / 256, 1);
	close(fd[1]);
	*tmp = fd[0];
}

static void	child_process(char **cmds, int *fd, int *tmp, int i)
{
	int		ex;
	t_data	*data;

	ex = 0;
	signal(SIGINT, SIG_DFL);
	data = parse_cmd(*cmds);
	heredoc(data->redirections);
	if (i == 0 && *(cmds + 1) == NULL)
		*tmp = 0;
	else
		dup2(*tmp, 0);
	if (*(cmds + 1) != NULL)
		dup2(fd[1], 1);
	close(fd[0]);
	if (!ft_strcmp(data->cmd, "export") || !ft_strcmp(data->cmd, "unset")
		|| !ft_strcmp(data->cmd, "cd") || !ft_strcmp(data->cmd, "env"))
		ex = execute_own_child_cmd(*cmds, data);
	else
		execute_cmd(data, *cmds, g_env);
	exit (ex);
}

void	pipes(char *input)
{
	int		i;
	int		tmp;
	int		fd[2];
	char	**cmds;
	pid_t	pid;

	i = 0;
	cmds = parse_pipes(input);
	while (cmds[i])
	{
		if (pipe(fd) < 0)
			error_message(PIPE);
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid < 0)
			error_message(FORK);
		else if (pid == 0)
			child_process(cmds + i, fd, &tmp, i);
		else
			parent_process(fd, &tmp);
		i++;
	}
	clean_str_arr(cmds);
}
