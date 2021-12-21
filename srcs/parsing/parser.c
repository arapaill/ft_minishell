/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:10:19 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/10/19 15:10:19 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	tokenizer(char *input)
{
	t_cmd			*new;
	char			*value;
	t_token			*token;
	t_token_type	type;

	value = ft_strdup(input);
	if (!value)
		cmd_error();
	type = find_type(value[0]);
	token = create_token(value, type);
	new = ft_cmdnew(token);
	if (!new)
	{
		free(value);
		cmd_error();
	}
	ft_cmdadd_back(&g_minishell.list_input, new);
}

t_bool	iterate_cmd(void *str)
{
	char	*c_str;

	c_str = (char *)str;
	if (!ft_strcmp(c_str, "echo")
		|| !ft_strcmp(c_str, "cd")
		|| !ft_strcmp(c_str, "pwd")
		|| !ft_strcmp(c_str, "export")
		|| !ft_strcmp(c_str, "unset")
		|| !ft_strcmp(c_str, "env")
		|| !ft_strcmp(c_str, "exit")
		|| !ft_strncmp(c_str, "./", 2)
		|| check_exec(c_str) == True)
		return (True);
	else
		return (False);
}

void	detect_cmd_type(void)
{
	t_bool	already_cmd;

	already_cmd = False;
	while (g_minishell.list_input)
	{
		if (already_cmd == False
			&& g_minishell.list_input->content->type != filename
			&& (iterate_cmd(g_minishell.list_input->content->value) == True
				|| check_path(g_minishell.list_input->content->value) == True))
		{
			g_minishell.list_input->content->type = cmd_instr;
			already_cmd = True;
		}
		if (get_token_type(g_minishell.list_input->content) == pipeline
			|| get_token_type(g_minishell.list_input->content) == semicolon)
			already_cmd = False;
		if (g_minishell.list_input->next)
			g_minishell.list_input = g_minishell.list_input->next;
		else
			break ;
		if (already_cmd == True
			&& g_minishell.list_input->content->type == cmd_instr)
			g_minishell.list_input->content->type = literal;
	}
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
}

void	pre_parsing(char *user_input)
{
	char	*new;
	size_t	i;
	size_t	size;

	i = -1;
	size = ft_strlen(user_input);
	while (++i < size)
	{
		new = ft_strndup(user_input + i, 1);
		if (!new)
			cmd_error();
		tokenizer(new);
		free(new);
	}
	concat_tokens_same_type();
	concat_tokens_var();
	detect_file_type();
	detect_cmd_type();
	if (get_quote_len(user_input) >= 0)
		concat_tokens_quotes();
	else
	{
		g_minishell.parsing_error = True;
		parsing_error(MS_ERROR_INVALID_QUOTE);
	}
}

void	parsing(char *user_input)
{
	pre_parsing(user_input);
	detect_file_type();
	while (g_minishell.parsing_error == False && g_minishell.list_input)
	{
		if (get_token_type(g_minishell.list_input->content)
			== simple_redir_right)
			parse_simple_redirection_right();
		else if (get_token_type(g_minishell.list_input->content)
			== double_redir_right)
			parse_double_redirection_right();
		else if (get_token_type(g_minishell.list_input->content)
			== simple_redir_left)
			parse_simple_redirection_left();
		else if (get_token_type(g_minishell.list_input->content)
			== double_redir_left)
			parse_double_redirection_left();
		else if (get_token_type(g_minishell.list_input->content)
			== pipeline)
			parse_pipe();
		if (g_minishell.list_input->next == NULL)
			break ;
		g_minishell.list_input = g_minishell.list_input->next;
	}
	g_minishell.list_input = ft_cmdfirst(g_minishell.list_input);
}
