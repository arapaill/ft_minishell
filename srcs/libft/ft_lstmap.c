/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:58:45 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/06/11 01:05:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list	*new_lst;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_lst = ft_lstnew(lst->content);
	if (new_lst == NULL)
		return (NULL);
	new_lst->content = f(new_lst->content);
	new_lst->next = ft_lstmap(lst->next, f);
	return (new_lst);
}
