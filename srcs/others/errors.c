/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:28:08 by user42            #+#    #+#             */
/*   Updated: 2021/12/07 16:14:55 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	cmd_error(void)
{
	if (errno)
	{
		perror("minishell:");
		g_minishell.last_return_value = errno;
	}
	free_list();
	if (g_minishell.env)
		free_array(g_minishell.env);
	g_minishell.env = NULL;
	exit(EXIT_FAILURE);
}

void	parsing_error(int error_code)
{
	if (error_code == MS_ERROR_PARSE)
		write(2, "minishell: parse error\n", 24);
	else if (error_code == MS_ERROR_TOO_MANY_ARG)
		write(2, "minishell: too many arguments\n", 30);
	else if (error_code == MS_ERROR_TO_PERROR)
		perror("minishell");
	else if (error_code == MS_ERROR_NO_CMD)
		write(2, "minishell: command not found.\n", 30);
	else if (error_code == MS_ERROR_INVALID_QUOTE)
		write(2, "minishell: quote are uneven.\n", 29);
	else if (error_code == MS_ERROR_SYNTAX)
		write(2, "minishell: syntax error.\n", 25);
	g_minishell.parsing_error = True;
}
