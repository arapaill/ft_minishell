/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:20:05 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/10/19 15:20:05 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	concat_tokens_same_type(void)
{
	t_cmd	*begin;

	begin = g_minishell.list_input;
	while (g_minishell.list_input->next != NULL)
	{
		if (get_token_type(g_minishell.list_input->content)
			== get_token_type(g_minishell.list_input->next->content)
			&& (get_token_type(g_minishell.list_input->content)
				!= double_quote
				&& get_token_type(g_minishell.list_input->content)
				!= single_quote))
		{
			relink_nodes();
			if (ft_strcmp(g_minishell.list_input->content->value, ">>")
				== 0)
				g_minishell.list_input->content->type = double_redir_right;
			else if (ft_strcmp(g_minishell.list_input->content->value, "<<")
				== 0)
				g_minishell.list_input->content->type = double_redir_left;
		}
		else
			g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = begin;
}

t_bool	concat_no_spaces(void)
{
	t_cmd	*begin;

	begin = g_minishell.list_input;
	while (g_minishell.list_input->next != NULL)
	{
		while (g_minishell.list_input->next->next != NULL
			&& g_minishell.list_input->next->content->type != space
			&& g_minishell.list_input->content->type != space
			&& g_minishell.list_input->content->type != single_quote
			&& g_minishell.list_input->content->type != double_quote)
			relink_nodes();
		g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = begin;
	return (False);
}

void	concat_tokens_quotes(void)
{
	t_token_type	quote_type;

	while (g_minishell.list_input->next)
	{
		if (get_token_type(g_minishell.list_input->content) == single_quote
			|| get_token_type(g_minishell.list_input->content) == double_quote)
		{
			quote_type = get_token_type(g_minishell.list_input->content);
			while ((g_minishell.list_input->next != NULL
					&& get_token_type(g_minishell.list_input->next->content)
					!= quote_type))
				relink_nodes();
			if (g_minishell.list_input->next
				&& get_token_type(g_minishell.list_input->next->content)
				== quote_type)
			{
				relink_nodes();
				if (g_minishell.list_input->next)
					g_minishell.list_input = g_minishell.list_input->next;
			}
		}
		else
			g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
}

void	concat_tokens_var(void)
{
	char	first;

	while (True)
	{
		while (g_minishell.list_input && g_minishell.list_input->next
			&& get_token_type(g_minishell.list_input->content) != variable)
			g_minishell.list_input = g_minishell.list_input->next;
		if (get_token_type(g_minishell.list_input->content) == variable
			&& g_minishell.list_input->next)
		{
			first = ((char *)g_minishell.list_input->next->content->value)[0];
			if (ft_isalnum(first) == 1 || first == '?')
				relink_nodes();
			else if (g_minishell.list_input->next)
				g_minishell.list_input = g_minishell.list_input->next;
		}
		if (g_minishell.list_input->next == NULL)
			break ;
		else
			g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
}
