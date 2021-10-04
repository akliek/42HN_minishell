/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:24:07 by akliek            #+#    #+#             */
/*   Updated: 2021/10/04 10:18:36 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit_status(int ex, bool change)
{
	static int	status;

	if (change == 1)
		status = ex;
	return (status);
}

static int	execute_cd(char *input)
{
	int		cd;
	char	*tmp;
	char	*path;

	tmp = change_to_env_var(get_cd_path(input));
	path = clean_quotes(tmp);
	clean_str(tmp);
	cd = chdir(path);
	clean_str(path);
	return (cd);
}

int	execute_own_child_cmd(char *input, t_data *data)
{
	int		ex;

	ex = redirections(data->redirections);
	if (ex)
		return (ex);
	if (!ft_strcmp(data->cmd, "export"))
	{
		if (!data->args || !data->args[0])
			print_exported_vars();
		else
			g_env = add_new_str(data->args, g_env);
	}
	else if (!ft_strcmp(data->cmd, "unset"))
		g_env = delete_env_var(data->args, g_env);
	else if (!ft_strcmp(data->cmd, "env"))
		print_arr_str(g_env);
	else if (!ft_strcmp(data->cmd, "cd"))
		ex = execute_cd(input);
	if (ex == -1)
		return (error_message(PATH));
	return (0);
}

void	run_cmd(char *input)
{
	int		in;
	int		out;
	int		ex;
	t_data	*data;

	data = parse_cmd(input);
	in = dup(0);
	out = dup(1);
	heredoc(data->redirections);
	ex = execute_own_child_cmd(input, data);
	clean_struct(data);
	get_exit_status(ex, 1);
	dup2(in, 0);
	close(in);
	dup2(out, 1);
	close(out);
}

void	execute_cmd(t_data *data, char *input, char **envp)
{
	int		ex;
	char	*path;

	path = get_path(data->cmd, envp);
	if (!*data->cmd)
		exit(0);
	ex = redirections(data->redirections);
	if (ex)
		exit(ex);
	if (!ft_strcmp(data->cmd, "echo"))
		execve(path, data->echo, envp);
	else if (data->cmd[0] == '/' || data->cmd[1] == '/' || data->cmd[2] == '/')
		execve(data->cmd, get_executable(input), envp);
	else
	{
		data->args = add_new_str(data->args, &data->cmd);
		execve(path, data->args, envp);
	}
	clean_str(path);
	error_message(EXECVE);
}
