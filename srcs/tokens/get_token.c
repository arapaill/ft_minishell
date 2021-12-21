/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:25:25 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/10/19 15:25:25 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_token_type	get_token_type(t_token *token)
{
	if (!token)
		return (none);
	return (token->type);
}

char	*get_token_value(t_token *token)
{
	char	*value;

	if (!token)
		return (NULL);
	value = (char *)token->value;
	return (value);
}
