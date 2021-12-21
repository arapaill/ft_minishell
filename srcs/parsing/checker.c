/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:03:09 by user42            #+#    #+#             */
/*   Updated: 2021/05/25 17:03:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static t_bool	verify_executable(char **paths, char *cmd)
{
	size_t	i;
	char	*path;
	char	*buf;

	i = 0;
	while (paths[i])
	{
		if (cmd[0] != '/')
		{
			buf = ft_strjoin(paths[i], "/");
			path = ft_strjoin(buf, cmd);
			free(buf);
		}
		if (access(path, X_OK) == 0)
		{
			free(path);
			free_array(paths);
			return (True);
		}
		i++;
		free(path);
	}
	free_array(paths);
	return (False);
}

t_bool	check_path(char *cmd)
{
	size_t	i;
	char	**paths;

	i = 0;
	while (g_minishell.env[i] != NULL
		&& ft_strnstr(g_minishell.env[i], "PATH=", 5) == 0)
		i++;
	if (g_minishell.env[i] == NULL)
		return (False);
	paths = ft_split(g_minishell.env[i] + 5, ':');
	if (verify_executable(paths, cmd) == True)
		return (True);
	else
		return (False);
}

t_bool	check_exec(char *path)
{
	if (access(path, X_OK) == 0)
		return (True);
	else
		return (False);
}
