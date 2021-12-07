/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:22:29 by akliek            #+#    #+#             */
/*   Updated: 2021/10/02 15:26:42 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cd_path(char *input)
{
	int		i;
	char	*path;

	i = 0;
	while (input[i] && input[i] != ' ')
		i++;
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i])
		path = ft_substr(input, i, ft_strlen(input) - i);
	else
	{
		i = 0;
		while (ft_strncmp(g_env[i], "USER=", 5))
			i++;
		path = ft_strjoin("/Users/", g_env[i] + 5);
	}
	return (path);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	int		exist;
	char	**path;
	char	*res;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd);
		exist = access(path[i], F_OK);
		if (exist == 0)
		{
			res = ft_strdup(path[i]);
			clean_str_arr(path);
			return (res);
		}
		i++;
	}
	return (NULL);
}
