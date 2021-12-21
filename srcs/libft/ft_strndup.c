/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:38:23 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/06/11 01:00:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*copy;
	size_t	i;

	i = -1;
	copy = malloc(sizeof(char) * (n + 1));
	if (!(copy))
		return (NULL);
	while (++i < n)
		copy[i] = s1[i];
	copy[i] = '\0';
	return (copy);
}
