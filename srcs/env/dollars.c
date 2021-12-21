/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:19:59 by badrien           #+#    #+#             */
/*   Updated: 2021/12/17 11:15:37 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static char	*next_dollar_value(int i, char *str)
{
	char	*new;
	char	*tmp;

	new = NULL;
	i++;
	if (str[i] == '?')
	{
		tmp = ft_itoa(g_minishell.last_return_value);
		if (!tmp)
			cmd_error();
		new = ft_strjoin_free(new, tmp);
		if (!new)
		{
			free(tmp);
			cmd_error();
		}
		free(tmp);
	}
	else
		new = get_value_env(&str[i]);
	return (new);
}

void	add_value(size_t *i, size_t *len, char *new_str, char *original_str)
{
	int		j;
	char	*env_value;

	j = 0;
	env_value = next_dollar_value(*i, original_str);
	while (env_value != NULL && env_value[j] != '\0')
	{
		new_str[*len] = env_value[j++];
		(*len)++;
	}
	(*i)++;
	if (original_str[*i] == '?')
		(*i)++;
	else
		while (original_str[*i] != '\0' && ft_isalnum(original_str[*i]))
			(*i)++;
	free(env_value);
}

int	make_new_block(char *new_str, char *original_str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (original_str[i] != '\0')
	{
		if (original_str[i] != '$')
			new_str[len++] = original_str[i++];
		else
		{
			if ((original_str[i + 1] == '\0' || ft_isalnum(original_str[i + 1])
					== 0) && original_str[i + 1] != '?')
			{
				new_str[len++] = original_str[i++];
			}
			else
				add_value(&i, &len, new_str, original_str);
		}
	}
	return (0);
}

char	*dollar_to_value(char *original_str, int len)
{
	char	*new_str;

	len = get_dollar_len(original_str);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	new_str[len] = '\0';
	if (len != 0)
	{
		make_new_block(new_str, original_str);
	}
	free(original_str);
	return (new_str);
}

int	replace_value_from_env(t_cmd *list)
{
	while (list != NULL)
	{
		if (list->content->type == pipeline || list->content->type == semicolon)
			return (0);
		if (list->content->type == double_quote
			|| list->content->type == single_quote)
			list->content->value = remove_quote(list->content->value);
		if (list->content->type == double_quote)
			list->content->value = dollar_to_value(list->content->value, 0);
		if (list->content->type == variable)
		{
			list->content->value = dollar_to_value(list->content->value, 0);
			list->content->value = remove_space(list->content->value, 0, list);
		}
		if (list->content->type == double_quote || list->content->type
			== single_quote || list->content->type == variable)
			list->content->type = literal;
		if (((char *)list->content->value)[0] == '\0')
			list->content->type = none;
		if (list->prev && list->prev->content->type == literal
			&& list->content->type == none)
			list = delete_node(list);
		list = list->next;
	}
	return (0);
}
