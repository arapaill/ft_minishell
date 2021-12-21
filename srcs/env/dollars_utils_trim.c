/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils_trim.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:34:42 by badrien           #+#    #+#             */
/*   Updated: 2021/12/09 19:07:36 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static int	len_without_space(char *original_str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (original_str[i + len] != '\0')
	{
		if (original_str[i + len] == ' ')
		{
			len++;
			while (original_str[i + len] == ' ')
				i++;
		}
		len++;
	}
	return (len);
}

static char	*trim_space(char *str, char *original_str, t_cmd *list)
{
	char	*new;

	free (original_str);
	if (list->prev && list->prev->content->type != literal)
	{
		new = ft_strtrim(str, " ");
		free (str);
		if (new == NULL)
			cmd_error();
		return (new);
	}
	else
		return (str);
}

char	*remove_space(char *original_str, int len, t_cmd *list)
{
	char	*new;
	int		i;

	new = malloc (sizeof(char *) * (len_without_space(original_str) + 1));
	if (new == NULL)
	{
		free(original_str);
		cmd_error();
	}
	i = 0;
	len = 0;
	while (original_str[i] != '\0')
	{
		if (original_str[i] == ' ')
		{
			new[len++] = original_str[i++];
			while (original_str[i] == ' ')
				i++;
		}
		new[len++] = original_str[i++];
	}
	new[len] = '\0';
	return (trim_space(new, original_str, list));
}
