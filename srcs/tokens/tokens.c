/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:26:13 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/10/19 15:26:13 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static const t_symbols	g_tab_token[] = {
{"|", pipeline},
{"<", simple_redir_left},
{">", simple_redir_right},
{"<<", double_redir_left},
{">>", double_redir_right},
{";", semicolon},
{"\"", double_quote},
{"'", single_quote},
{"\\", backslash},
{"\f", space},
{"\n", line_return},
{"\r", space},
{"\t", space},
{"\v", space},
{" ", space},
{"$", variable},
{0},
};

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!(token))
	{
		free(value);
		cmd_error();
	}
	token->value = value;
	token->type = type;
	token->pipe_in = STDIN_FILENO;
	token->pipe_out = STDOUT_FILENO;
	return (token);
}

t_token_type	find_type(char c)
{
	size_t			i;
	char			*str;
	t_token_type	type;

	i = 0;
	type = none;
	while (g_tab_token[i].symbol)
	{
		str = g_tab_token[i].symbol;
		if (str[0] == c)
		{
			type = g_tab_token[i].type;
			return (type);
		}
		i++;
	}
	if (type == none)
		if (ft_isprint(c))
			type = literal;
	return (type);
}
