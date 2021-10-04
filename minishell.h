/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 12:19:29 by akliek            #+#    #+#             */
/*   Updated: 2021/10/02 15:39:05 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_type
{
	INPUT,
	OUTPUT,
	HEREDOC,
	DOUBLE_OUTPUT,
	NONE
}			t_type;

typedef enum e_error
{
	PIPE,
	FORK,
	PATH,
	OPEN,
	EXIT,
	EXECVE,
	EXIT_ARG
}			t_error;

typedef struct s_redirection
{
	char					*file;
	t_type					type;
	struct s_redirection	*next;
}			t_redirection;

typedef struct s_data
{
	char			*cmd;
	char			**echo;
	char			**args;
	int				exit_status;
	t_redirection	*redirections;
}			t_data;

extern char		**g_env;

/*==========CLEAN=========*/

void			clean_str(char *s);
void			clean_struct(t_data *data);
void			clean_node(t_redirection *red);

/*==========ENV_VARS=========*/

void			print_exported_vars(void);
char			*change_to_env_var(char *arg);
char			**add_new_str(char **args, char **env);
char			**delete_env_var(char **args, char **env);

/*==========ERROR=========*/

int				error_message(t_error error);

/*==========EXECUTE_CMD=========*/

int				get_exit_status(int ex, bool change);
int				execute_own_child_cmd(char *input, t_data *data);
void			run_cmd(char *input);
void			execute_cmd(t_data *data, char *input, char **envp);

/*==========EXECUTABLES=========*/

char			**get_executable(char *str);

/*==========PARSE_ARGS=========*/

char			**parse_args(char *str);
char			**parse_args_export(char *str);

/*==========PARSE_CMD=========*/

char			*get_cmd(char *str);
char			*get_file(char *str, char **tmp, t_type type);
t_data			*parse_cmd(char *input);

/*==========PARSE_ECHO=========*/

char			**get_echo(char *str);

/*==========PARSE_PIPES=========*/

int				count_real_pipes(char *str);
char			**parse_pipes(char *input);
bool			is_real(char *str, char qoute, int i, int k);

/*==========PATH=========*/

char			*get_cd_path(char *input);
char			*get_path(char *cmd, char **envp);

/*==========PIPE=========*/

void			pipes(char *input);

/*==========QUOTES=========*/

int				count_quotes(char *str, char c);
char			*clean_quotes(char *str);
char			get_first_quotes(char *str);

/*==========REDIRECTIONS=========*/

int				redirections(t_redirection *redirections);
void			heredoc(t_redirection *redirection);
t_redirection	*get_redirection(char **str, char q);

/*==========SIGNALS=========*/

void			handle_sigint(int sig);

/*==========SPACES=========*/
int				count_sapes(char *str);
char			*clean_spaces(char *str);
char			*clean_first_last_spaces(char *str);

/*==========STR_ARR=========*/

int				arr_strlen(char **str);
void			clean_str_arr(char **s);
void			print_arr_str(char **str);
char			**arr_str_dup(char **envp);

/*==========UTILS=========*/

int				ft_strcmp(const char *s1, const char *s2);
bool			is_number(char *s);
char			**sort_strings(char **env);

#endif
