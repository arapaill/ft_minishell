/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:50:18 by arapaill          #+#    #+#             */
/*   Updated: 2021/12/16 15:52:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_exporting_2(char *value, int s)
{
	if (value && envchr(value, -1) == -1)
	{
		if (ft_envplussearch(value) != 0)
			value = ft_plus_cut(value);
		s = size_env(g_minishell.env);
		g_minishell.env = realloc_env(g_minishell.env, s + 1);
		g_minishell.env[s] = ft_strdup(value);
		if (!g_minishell.env[s])
			cmd_error();
		g_minishell.env[s + 1] = NULL;
	}
	else if (value && envchr(value, -1) > -1)
	{
		s = envchr(value, -1);
		free(g_minishell.env[s]);
		g_minishell.env[s] = ft_strdup(value);
		if (!g_minishell.env[s])
			cmd_error();
	}
}

void	ft_exporting(t_cmd *list, char *value)
{
	int	s;

	while (list && ft_isstop(list))
	{
		if (value && ft_strchr(value, 61))
		{
			s = 0;
			if (ft_envplussearch(value) != 0 && envchr(value, -1) > -1)
			{
				s = envchr(value, -1);
				g_minishell.env[s] = ft_strjoin_free(g_minishell.env[s],
						&value[ft_envplussearch(value) + 2]);
				if (!g_minishell.env[s])
					cmd_error();
			}
			else
				ft_exporting_2(value, s);
		}
		list = list->next;
	}
	free(value);
	value = NULL;
}

static void	loop_export(t_cmd *list)
{
	char	*value;

	g_minishell.last_return_value = 0;
	while (list && ft_isstop(list))
	{
		while (list && list->content->type == space)
			list = list->next;
		if (!ft_isstop(list))
			return ;
		if (!ft_isalpha(((char *)list->content->value)[0]))
		{
			printf("minishell: export: %s not a valid identifier\n",
				(char *)list->content->value);
			list = list->next;
			g_minishell.last_return_value = 1;
		}
		if (!ft_isstop(list))
			return ;
		value = ft_strdup(list->content->value);
		if (!value)
			cmd_error();
		ft_exporting(list, value);
		list = list->next;
	}
}

void	ft_exporting_no_arg(int out)
{
	int		i;

	i = -1;
	while (g_minishell.env[++i])
	{
		ft_putstr_fd("declare -x ", out);
		ft_putstr_fd(g_minishell.env[i], out);
		write(out, "\n", 1);
	}
}

void	cmd_export(t_cmd *list, int out, int in)
{
	int		pid;

	while (list && list->next && list->content->type == space)
		list = list->next;
	if (!ft_isstop(list))
	{
		pid = fork();
		if (pid == -1)
			cmd_error();
		if (!pid)
		{
			ft_exporting_no_arg(out);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, NULL, 0);
			if (out != STDOUT_FILENO)
				close(out);
			if (in != STDIN_FILENO)
				close(in);
		}
		return ;
	}
	loop_export(list);
}
