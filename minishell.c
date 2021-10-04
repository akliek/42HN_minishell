/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 12:19:32 by akliek            #+#    #+#             */
/*   Updated: 2021/10/04 10:41:53 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env;

static char	*get_input(void)
{
	char	*input;

	input = NULL;
	input = readline("minishell > ");
	if (input)
		add_history(input);
	return (input);
}

static bool	is_own_cmd(char *input)
{
	int		ret;
	char	*cmd;

	ret = 0;
	cmd = get_cmd(input);
	if (!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "env"))
		ret = 1;
	clean_str(cmd);
	return (ret);
}

static int	close_programm(char *input, char **args, int ex)
{
	if (!input)
	{
		write(1, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 14);
		write(1, "minishell > ", 12);
	}
	printf("exit\n");
	if (input)
	{
		if (args && *args && arr_strlen(args) > 1 && is_number(*args))
		{
			clean_str_arr(args);
			return (error_message(EXIT_ARG));
		}
		else if (args && *args && !is_number(*args))
		{
			perror("minishell: wtf, dude?");
			ex = 255;
		}
		else if (args && *args)
			ex = ft_atoi(*args);
		clean_str_arr(args);
		free(input);
	}
	exit (ex);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc != 1 || !argv || !argv[0])
	{
		perror("Usage: just ./minishell, ok?");
		return (0);
	}
	g_env = arr_str_dup(envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = get_input();
		if (!input)
			close_programm(input, NULL, 0);
		else if ((!ft_strncmp(input, "exit", 4)
				&& (!*(input + 4) || *(input + 4) == ' ')))
			close_programm(input, parse_args(input + 4), 0);
		else if (!count_real_pipes(input) && is_own_cmd(input))
			run_cmd(input);
		else
			pipes(input);
		clean_str(input);
	}
	return (0);
}
