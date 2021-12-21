/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_concat_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:29:55 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/10/19 15:29:55 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	clear_node(t_cmd *node)
{
	free(node->content->value);
	node->content->value = NULL;
	free(node->content);
	node->content = NULL;
	free(node);
	node = NULL;
}

static void	join_two_tokens(t_cmd *list)
{
	char	*str_1;
	char	*str_2;
	char	*new_tok_value;

	str_1 = list->content->value;
	str_2 = list->next->content->value;
	new_tok_value = ft_strjoin(str_1, str_2);
	if (!new_tok_value)
		cmd_error();
	free(list->content->value);
	list->content->value = new_tok_value;
}

/* Fusionne le token actuel avec le token suivant 
** et garde le type du token actuel. 
*/
void	relink_nodes(void)
{
	t_cmd	*tmp_list;

	tmp_list = NULL;
	if (g_minishell.list_input->content->type == none)
	{
		g_minishell.list_input = g_minishell.list_input->next;
		return ;
	}
	join_two_tokens(g_minishell.list_input);
	if (g_minishell.list_input->next->next)
		tmp_list = g_minishell.list_input->next->next;
	else
	{
		clear_node(g_minishell.list_input->next);
		g_minishell.list_input->next = NULL;
	}
	if (tmp_list)
	{
		clear_node(g_minishell.list_input->next);
		g_minishell.list_input->next = tmp_list;
		g_minishell.list_input->next->prev = g_minishell.list_input;
	}
}

/* Supprime le node envoyé en pointeur, et renvoie le node précédent celui
** qui vient d'être supprimé.
*/
t_cmd	*delete_node(t_cmd *node_to_delete)
{
	t_cmd	*prev;
	t_cmd	*next;

	prev = node_to_delete->prev;
	next = node_to_delete->next;
	if (node_to_delete->prev)
		prev->next = next;
	if (node_to_delete->next)
		next->prev = prev;
	free(node_to_delete->content->value);
	node_to_delete->content->value = NULL;
	free(node_to_delete->content);
	node_to_delete->content = NULL;
	free(node_to_delete);
	node_to_delete = NULL;
	if (prev)
		return (prev);
	else
		return (next);
}
