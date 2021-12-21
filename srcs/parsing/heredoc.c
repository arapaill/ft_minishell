/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:47:32 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/12/14 14:47:32 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	child_heredoc(int *fd)
{
	char	*end_redir;
	char	*buffer;

	end_redir = find_next_literal(1)->content->value;
	buffer = NULL;
	signal(SIGINT, SIG_DFL);
	while (True)
	{
		buffer = readline("\033[1;32m>\033[0m ");
		if (!buffer || !ft_strcmp(buffer, end_redir))
			break ;
		buffer = ft_strjoin_free(buffer, "\n");
		buffer = dollar_to_value(buffer, 0);
		ft_putstr_fd(buffer, fd[1]);
		free(buffer);
	}
	free(buffer);
	close(fd[1]);
	close(fd[0]);
	exit(EXIT_SUCCESS);
}

static void	parent_heredoc(pid_t pid, int *fd)
{
	int		retval;

	waitpid(pid, &retval, 0);
	close(fd[1]);
	if (retval != 0)
	{
		write(STDIN_FILENO, "\n", 1);
		close(fd[0]);
		g_minishell.signal = 0;
	}
}

void	parse_double_redirection_left(void)
{
	int		fd[2];
	pid_t	pid;

	if (is_there_literal_for_file() == False)
		return ;
	g_minishell.signal = 1;
	if (pipe(fd) < 0)
		cmd_error();
	if (find_next_cmd())
		find_next_cmd()->content->pipe_in = fd[0];
	else if (find_prev_cmd())
		find_prev_cmd()->content->pipe_in = fd[0];
	else
		return ;
	pid = fork();
	if (pid == -1)
		cmd_error();
	if (pid == 0)
		child_heredoc(fd);
	else
		parent_heredoc(pid, fd);
}
