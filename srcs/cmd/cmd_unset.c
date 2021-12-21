/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 09:46:55 by arapaill          #+#    #+#             */
/*   Updated: 2021/11/30 17:35:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_unseting(t_cmd *list)
{
	int		i;
	int		env_size;
	int		word_size;

	i = -1;
	env_size = 0;
	while (g_minishell.env[env_size])
		env_size++;
	env_size--;
	word_size = ft_strlen(list->content->value);
	while (g_minishell.env[++i])
	{
		if (!ft_strncmp(list->content->value, g_minishell.env[i], word_size))
		{
			free(g_minishell.env[i]);
			g_minishell.env[i] = g_minishell.env[env_size];
			g_minishell.env[env_size] = NULL;
			g_minishell.env = realloc_env(g_minishell.env, env_size);
			return ;
		}
	}
}

void	cmd_unset(t_cmd *list)
{
	if (!list || list->next == NULL)
		return ;
	list = list->next;
	g_minishell.last_return_value = 0;
	while (list && ft_isstop(list))
	{
		while (list->next && list->content->type == space)
			list = list->next;
		if (!ft_isstop(list))
			return ;
		if (!ft_isalpha(((char *)list->content->value)[0]))
		{
			printf("minishell: unset: %s not a valid identifier\n",
				(char *)list->content->value);
			list = list->next;
			g_minishell.last_return_value = 1;
		}
		if (!ft_isstop(list))
			return ;
		ft_unseting(list);
		list = list->next;
	}
}
