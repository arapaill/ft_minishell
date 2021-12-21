/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:41:20 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/10/19 15:40:37 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_cmdadd_back(t_cmd **alst, t_cmd *new)
{
	if (new == NULL)
		return ;
	if (*alst != NULL)
	{
		new->prev = ft_cmdlast(*alst);
		ft_cmdlast(*alst)->next = new;
	}
	else
		*alst = new;
}
