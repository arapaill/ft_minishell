/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:10:50 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/10/19 15:10:50 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

/* find_next_cmd(void)
** Renvoie un pointeur vers le prochain cmd_instr. 
** Renvoie NULL s'il ne trouve rien.
** S'arrête automatiquement dès qu'il trouve un '|', 
** un ';' ou la fin de la chaine.
*/
t_cmd	*find_next_cmd(void)
{
	t_cmd	*current;
	t_cmd	*ret;

	current = g_minishell.list_input;
	if (g_minishell.list_input && g_minishell.list_input->next
		&& (g_minishell.list_input->content->type == semicolon
			&& g_minishell.list_input->content->type == pipeline))
		g_minishell.list_input = g_minishell.list_input->next;
	while (g_minishell.list_input
		&& g_minishell.list_input->content->type != cmd_instr
		&& g_minishell.list_input->content->type != pipeline
		&& g_minishell.list_input->content->type != semicolon)
		g_minishell.list_input = g_minishell.list_input->next;
	if (g_minishell.list_input
		&& g_minishell.list_input->content->type == cmd_instr)
		ret = g_minishell.list_input;
	else
		ret = NULL;
	g_minishell.list_input = current;
	return (ret);
}

/* find_next_cmd(void)
** Renvoie un pointeur vers le précédent cmd_instr. 
** Renvoie NULL s'il ne trouve rien.
** S'arrête automatiquement dès qu'il trouve un '|',
** un ';' ou la fin de la chaine.
*/
t_cmd	*find_prev_cmd(void)
{
	t_cmd	*current;
	t_cmd	*ret;

	current = g_minishell.list_input;
	g_minishell.list_input = g_minishell.list_input->prev;
	while (g_minishell.list_input
		&& g_minishell.list_input->content->type != cmd_instr
		&& g_minishell.list_input->content->type != pipeline
		&& g_minishell.list_input->content->type != semicolon)
		g_minishell.list_input = g_minishell.list_input->prev;
	if (g_minishell.list_input
		&& g_minishell.list_input->content->type == cmd_instr)
		ret = g_minishell.list_input;
	else
		ret = NULL;
	g_minishell.list_input = current;
	return (ret);
}

/* find_next_literal(size_t range)
** range : Jusqu'à combien de node (en ignorant les espaces) 
** chercher le literal. 0 = pas de limite.
** S'arrête automatiquement dès qu'il trouve
** un '|' ou la fin de la chaine.
*/
t_cmd	*find_next_literal(int range)
{
	t_cmd	*current;
	t_cmd	*ret;

	if (range == 0)
		range = ft_cmdsize(g_minishell.list_input);
	else
		range++;
	current = g_minishell.list_input;
	while (g_minishell.list_input
		&& g_minishell.list_input->content->type != literal
		&& g_minishell.list_input->content->type != cmd_instr
		&& g_minishell.list_input->content->type != filename
		&& g_minishell.list_input->content->type != pipeline && range > 0)
	{
		if (g_minishell.list_input->content->type != space)
			range--;
		g_minishell.list_input = g_minishell.list_input->next;
	}
	if ((g_minishell.list_input
			&& g_minishell.list_input->content->type == pipeline) || range <= 0)
		ret = NULL;
	else
		ret = g_minishell.list_input;
	g_minishell.list_input = current;
	return (ret);
}

t_bool	is_there_literal_for_file(void)
{
	t_cmd	*current;
	t_cmd	*file;

	current = g_minishell.list_input;
	file = find_next_literal(1);
	if (file == NULL)
	{
		parsing_error(MS_ERROR_SYNTAX);
		return (False);
	}
	g_minishell.list_input = current;
	return (True);
}

/* t_bool	ft_isstop(t_cmd *list)
** Permet de vérifier si le node actuel est un stop
*/
t_bool	ft_isstop(t_cmd *list)
{
	if (list == NULL)
		return (False);
	if (list->content->value && list->content->type != semicolon
		&& list->content->type != simple_redir_left
		&& list->content->type != simple_redir_right
		&& list->content->type != pipeline
		&& list->content->type != double_redir_left
		&& list->content->type != double_redir_right)
		return (True);
	else
		return (False);
}
