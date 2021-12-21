/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:34:02 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/06/11 00:49:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ret;
	size_t	i;

	i = -1;
	ret = malloc(count * size);
	if (ret == 0)
		return (NULL);
	while (++i < count * size)
		ret[i] = '\0';
	return (ret);
}
