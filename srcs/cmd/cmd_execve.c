/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:56:30 by arapaill          #+#    #+#             */
/*   Updated: 2021/12/16 18:25:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static char	**get_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split((env[i] + 5), ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

static void	ft_exec_free(char *cmd)
{
	char	**args;
	char	**path;
	char	*tmp;
	size_t	i;

	i = -1;
	if (ft_strlen(cmd) == 0)
		parsing_error(4);
	args = ft_split(cmd, ' ');
	free(cmd);
	path = get_path(g_minishell.env);
	while (path && path[++i])
	{
		if (args[0][0] != '/')
		{
			tmp = ft_strjoin(path[i], "/");
			tmp = ft_strjoin_free(tmp, args[0]);
		}
		execve(tmp, args, g_minishell.env);
		free(tmp);
	}
	free_array(args);
	free_array(path);
	parsing_error(MS_ERROR_NO_CMD);
}

static void	ft_loop_execve_child(int in, int out, char *cmd)
{
	signal(SIGINT, SIG_DFL);
	if (in != STDIN_FILENO && dup2(in, STDIN_FILENO) < 0)
		cmd_error();
	if (out != STDOUT_FILENO && dup2(out, STDOUT_FILENO) < 0)
		cmd_error();
	ft_exec_free(cmd);
	exit(0);
}

static void	ft_loop_execve(int in, int out, char *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == -1)
		cmd_error();
	if (!pid)
		ft_loop_execve_child(in, out, cmd);
	else
	{
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) && g_minishell.last_return_value != 130)
			g_minishell.last_return_value = WEXITSTATUS(status);
		if (in != STDIN_FILENO)
			close(in);
		if (out != STDOUT_FILENO)
			close(out);
		free(cmd);
	}
}

void	cmd_execve(t_cmd *list)
{
	int		in;
	int		out;
	char	*cmd;

	g_minishell.signal = 1;
	cmd = ft_strdup(list->content->value);
	in = list->content->pipe_in;
	out = list->content->pipe_out;
	while (list->next && (list->next->content->type == literal
			|| list->next->content->type == variable
			|| list->next->content->type == single_quote
			|| list->next->content->type == double_quote
			|| list->next->content->type == space))
	{
		cmd = ft_strjoin_free(cmd, list->next->content->value);
		list = list->next;
	}
	ft_loop_execve(in, out, cmd);
	g_minishell.signal = 0;
}
