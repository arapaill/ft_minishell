/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:58:01 by arapaill          #+#    #+#             */
/*   Updated: 2021/12/17 17:37:20 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	print_non_quote(void *s, int out)
{
	char	*str;
	int		len;
	int		i;

	str = (char *)s;
	len = ft_strlen(str);
	i = -1;
	while (str[++i] && i < len)
		write(out, &str[i], 1);
}

static int	check_space(t_cmd *list)
{
	if (list->next)
		list = list->next;
	else
		return (0);
	while (list && list->content->type == space)
		list = list->next;
	if (list || (list->content->value && list->content->type != semicolon
			&& list->content->type != pipeline))
		return (1);
	else
		return (0);
}

static void	loop_echo(int flag, t_cmd *list, int out)
{
	while (list->content->value && list->content->type != semicolon
		&& list->content->type != pipeline)
	{
		if (list->content->type == literal
			|| list->content->type == variable)
		{
			print_non_quote(list->content->value, out);
			if (check_space(list))
				write(out, " ", 1);
		}
		if (list->next)
			list = list->next;
		else
			break ;
		while (list && list->content->type == space)
			list = list->next;
		if (!list)
			break ;
	}
	if (flag == 0)
		write(out, "\n", 1);
}

static int	is_flag(t_cmd **list)
{
	int		i;
	int		flag;

	flag = 0;
	while ((*list)->content->type == space && (*list)->next)
		*list = (*list)->next;
	if (!ft_strncmp((*list)->content->value, "-n", 2))
	{
		i = 1;
		while (((char *)(*list)->content->value)[i])
		{
			if (((char *)(*list)->content->value)[i] != 'n')
				return (flag);
			i++;
		}
		flag = 1;
		if ((*list)->next)
			*list = (*list)->next;
		while ((*list)->content->type == space && (*list)->next)
			*list = (*list)->next;
		if (!list)
			exit(EXIT_SUCCESS);
	}
	return (flag);
}

void	cmd_echo(t_cmd *list, int out, int in)
{
	int		flag;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		cmd_error();
	if (list->next)
		list = list->next;
	while (list->next && list->content->type == space)
		list = list->next;
	if (!pid)
	{
		flag = is_flag(&list);
		loop_echo(flag, list, out);
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
	g_minishell.last_return_value = 0;
}
