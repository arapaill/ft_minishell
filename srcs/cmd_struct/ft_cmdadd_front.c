/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:05:28 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/10/19 15:40:53 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_cmdadd_front(t_cmd **alst, t_cmd *new)
{
	if (alst == NULL || new == NULL)
		return ;
	if (*alst == NULL)
	{
		(*alst) = new;
		(*alst)->prev = NULL;
	}
	else
	{
		ft_cmdfirst(*alst)->prev = new;
		new->next = *alst;
		*alst = new;
	}
}
