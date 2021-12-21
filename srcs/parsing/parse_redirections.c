/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:46:20 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/10/26 15:46:20 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	parse_simple_redirection_right(void)
{
	int	fd;

	fd = -1;
	if (fd > 0)
		close(fd);
	if (is_there_literal_for_file() == False)
		return ;
	fd = open(find_next_literal(1)->content->value,
			O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
	{
		parsing_error(MS_ERROR_TO_PERROR);
		return ;
	}
	if (find_next_cmd())
		find_next_cmd()->content->pipe_out = fd;
	else if (find_prev_cmd())
		find_prev_cmd()->content->pipe_out = fd;
	else
		return ;
}

void	parse_double_redirection_right(void)
{
	int	fd;

	fd = -1;
	if (fd > 0)
		close(fd);
	if (is_there_literal_for_file() == False)
		return ;
	fd = open(find_next_literal(1)->content->value,
			O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd < 0)
	{
		parsing_error(MS_ERROR_TO_PERROR);
		return ;
	}
	if (find_next_cmd())
		find_next_cmd()->content->pipe_out = fd;
	else if (find_prev_cmd())
		find_prev_cmd()->content->pipe_out = fd;
	else
		return ;
}

void	parse_simple_redirection_left(void)
{
	int	fd;

	fd = -1;
	if (fd > 0)
		close(fd);
	if (is_there_literal_for_file() == False)
		return ;
	fd = open(find_next_literal(1)->content->value, O_RDONLY);
	if (fd < 0)
	{
		parsing_error(MS_ERROR_TO_PERROR);
		return ;
	}
	if (find_next_cmd())
		find_next_cmd()->content->pipe_in = fd;
	else if (find_prev_cmd())
		find_prev_cmd()->content->pipe_in = fd;
	else
		return ;
}

void	parse_pipe(void)
{
	int		fd[2];
	t_cmd	*current;

	current = g_minishell.list_input;
	if (g_minishell.list_input->prev)
		g_minishell.list_input = g_minishell.list_input->prev;
	else
	{
		parsing_error(MS_ERROR_SYNTAX);
		return ;
	}
	assign_pipe(fd, current);
	g_minishell.list_input = current;
}
