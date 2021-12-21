/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:15:04 by user42            #+#    #+#             */
/*   Updated: 2021/12/17 17:30:04 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_switch(t_cmd *list)
{
	if (!ft_strcmp(list->content->value, "exit"))
		cmd_exit(list);
	else if (!ft_strcmp(list->content->value, "echo"))
		cmd_echo(list, list->content->pipe_out,
			list->content->pipe_in);
	else if (!ft_strcmp(list->content->value, "env"))
		print_env(list);
	else if (!ft_strcmp(list->content->value, "pwd"))
		cmd_pwd(list);
	else if (!ft_strcmp(list->content->value, "cd"))
		cmd_cd(list->next);
	else if (!ft_strncmp(list->content->value, "./", 2)
		|| check_exec(list->content->value))
		cmd_execute(list, list->content->pipe_out, list->content->pipe_in);
	else if (!ft_strcmp(list->content->value, "unset"))
		cmd_unset(list->next);
	else if (!ft_strcmp(list->content->value, "export"))
		cmd_export(list->next, list->content->pipe_out, list->content->pipe_in);
	else
		cmd_execve(list);
}

static void	go_to_next_block(void)
{
	while (g_minishell.list_input
		&& g_minishell.list_input->content->type != semicolon
		&& g_minishell.list_input->content->type != pipeline)
		g_minishell.list_input = g_minishell.list_input->next;
	if (g_minishell.list_input
		&& (g_minishell.list_input->content->type == semicolon
			|| g_minishell.list_input->content->type == pipeline))
		g_minishell.list_input = g_minishell.list_input->next;
}

void	cmd_hub(void)
{
	t_cmd	*current;
	t_cmd	*first;

	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
	first = ft_cmdfirst(g_minishell.list_input);
	while (g_minishell.list_input)
	{
		replace_value_from_env(g_minishell.list_input);
		concat_tokens_same_type();
		current = g_minishell.list_input;
		detect_cmd_type();
		detect_file_type();
		g_minishell.list_input = current;
		if (find_next_cmd())
			ft_switch(find_next_cmd());
		else if (find_next_literal(0))
			ft_switch(find_next_literal(0));
		go_to_next_block();
	}
	g_minishell.list_input = first;
}
