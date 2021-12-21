/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:36:58 by badrien           #+#    #+#             */
/*   Updated: 2021/12/17 11:10:16 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static int	len_last_return_value(void)
{
	char	*tmp;
	int		len;

	len = 0;
	tmp = NULL;
	tmp = ft_itoa(g_minishell.last_return_value);
	if (!tmp)
		cmd_error();
	len = ft_strlen(tmp);
	free (tmp);
	return (len);
}

static int	len_block_var(char *str, size_t *i)
{
	int		len;
	char	*tmp;

	len = 0;
	if (str[*i] == '\0')
		return (0);
	if (str[*i] == '$')
		return (0);
	if ((str[*i] == '\0' || ft_isalnum(str[*i]) == 0) && str[*i + 1] != '?')
		len++;
	else
	{
		tmp = get_value_env(&str[*i]);
		if (tmp != NULL)
			len += ft_strlen(tmp);
		free (tmp);
		while (str[*i] != '\0' && ft_isalnum(str[*i]))
			*i = *i + 1;
	}
	return (len);
}

int	get_dollar_len(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i + 1] && str[i] == '$' && ft_isalpha(str[i + 1]))
		{
			i++;
			len += len_block_var(str, &i);
		}
		else if (str[i + 1] && str[i + 1] == '?')
		{
			i++;
			len += len_last_return_value();
			i++;
		}
		if (str[i] != '\0')
		{
			i++;
			len++;
		}
	}
	return (len);
}
