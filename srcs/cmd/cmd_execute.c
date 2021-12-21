/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:47:41 by user42            #+#    #+#             */
/*   Updated: 2021/12/13 16:05:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static char	*get_path_pwd(char **env)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			path = ft_strdup((env[i] + 4));
			break ;
		}
	}
	return (path);
}

static char	*find_slash(void *s)
{
	size_t	i;
	char	*char_s;
	char	*ret;

	char_s = (char *)s;
	i = ft_strlen(char_s);
	i--;
	while (char_s[i] && char_s[i] != '/')
		i--;
	ret = ft_strdup(&char_s[++i]);
	return (ret);
}

static char	**add_arguments(t_cmd *list)
{
	char	**ret;
	size_t	nb_args;
	size_t	i;
	t_cmd	*begin;

	begin = list;
	i = 1;
	nb_args = 0;
	while (ft_isstop(list) != 0)
	{	
		if (list->content->type == literal)
			nb_args++;
		list = list->next;
	}
	list = begin;
	ret = malloc(sizeof(char *) * (nb_args + 2));
	ret[0] = find_slash(list->content->value);
	ret[nb_args + 1] = NULL;
	while (i < nb_args + 1)
	{
		list = list->next;
		if (list->content->type == literal)
			ret[i++] = list->content->value;
	}
	return (ret);
}

static void	execute_child(t_cmd *list)
{
	char	*path;
	char	**args;
	char	*tmp;
	char	**tmp_2;

	if (check_exec(list->content->value) == True)
	{
		tmp_2 = ft_split(list->content->value, ' ');
		tmp = ft_strdup(tmp_2[0]);
		free_array(tmp_2);
		args = add_arguments(list);
	}
	else
	{
		args = ft_split(list->content->value, '/');
		path = get_path_pwd(g_minishell.env);
		tmp = ft_strjoin(path, "/");
		free(path);
		tmp = ft_strjoin_free(tmp, args[1]);
	}
	execve(tmp, args, g_minishell.env);
	free(tmp);
	free_array(args);
	perror("minishell");
	exit(EXIT_SUCCESS);
}

void	cmd_execute(t_cmd *list, int in, int out)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == -1)
		cmd_error();
	if (!pid)
	{
		if (in != STDIN_FILENO && dup2(in, STDIN_FILENO) < 0)
			cmd_error();
		if (out != STDOUT_FILENO && dup2(out, STDOUT_FILENO) < 0)
			cmd_error();
		execute_child(list);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status))
			g_minishell.last_return_value = WEXITSTATUS(status);
		if (list->content->pipe_in != STDIN_FILENO)
			close(list->content->pipe_in);
		if (list->content->pipe_out != STDOUT_FILENO)
			close(list->content->pipe_out);
	}
}
