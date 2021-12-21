/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badrien <badrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:24:44 by badrien           #+#    #+#             */
/*   Updated: 2021/12/09 11:44:30 by badrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	get_quote_len(char *str)
{
	int	i;
	int	quote;
	int	double_quote;

	i = 0;
	quote = 0;
	double_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && double_quote % 2 == 0)
			quote++;
		else if (str[i] == '\"' && quote % 2 == 0)
			double_quote++;
		i++;
	}
	if (quote % 2 == 1 || double_quote % 2 == 1)
		return (-1);
	return (i - quote - double_quote);
}

static char	*remove_quote_2(char *str, int len, int i)
{
	char	*new_str;
	int		quote;
	int		double_quote;

	quote = 0;
	double_quote = 0;
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
	{
		free(str);
		cmd_error();
	}
	len = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '\'' && double_quote % 2 == 0)
			quote++;
		else if (str[i] == '\"' && quote % 2 == 0)
			double_quote++;
		else
			new_str[len++] = str[i];
	}
	new_str[len] = '\0';
	free(str);
	return (new_str);
}

char	*remove_quote(char *str)
{
	int		len;

	len = get_quote_len(str);
	if (len == -1)
	{
		printf("quote not even\n");
		exit(-1);
	}
	return (remove_quote_2(str, len, -1));
}
