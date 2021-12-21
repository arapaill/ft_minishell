/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdfirst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:40:39 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/10/19 15:40:39 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_cmd	*ft_cmdfirst(t_cmd *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}
