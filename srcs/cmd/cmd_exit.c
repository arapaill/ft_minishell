/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:15:10 by user42            #+#    #+#             */
/*   Updated: 2021/12/20 14:58:04 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	cmd_exit_pid(int in, int out, int exit_value)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		cmd_error();
	if (!pid)
		exit(exit_value);
	else
	{
		waitpid(pid, NULL, 0);
		if (out != STDOUT_FILENO)
			close(out);
		if (in != STDIN_FILENO)
			close(in);
	}
}

static void	cmd_exit_2(int in, int out, int exit_value)
{
	if ((in == 0 && out == 1) || exit_value == -1)
	{
		ft_putstr_fd("exit\n", 1);
		if (exit_value == -1)
		{
			printf("minishell: exit: bad argument\n");
			exit_value = 0;
		}
		free_list();
		exit(exit_value);
	}
	cmd_exit_pid(in, out, exit_value);
}

void	cmd_exit(t_cmd *list)
{
	int		exit_value;
	int		i;
	int		in;
	int		out;

	exit_value = 0;
	in = list->content->pipe_in;
	out = list->content->pipe_out;
	i = -1;
	list = list->next;
	while (list && list->content->type == space && list->next)
		list = list->next;
	while (list && ((char *)list->content->value)[++i])
		if (ft_isalpha(((char *)list->content->value)[i]))
			exit_value = -1;
	if (list && exit_value != -1)
		exit_value = ft_atoi((char *)list->content->value);
	cmd_exit_2(in, out, exit_value);
}
