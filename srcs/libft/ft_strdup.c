/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:40:30 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/06/11 01:02:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	i;
	size_t	size_s1;

	i = -1;
	size_s1 = ft_strlen(s1);
	copy = malloc((sizeof(char) * size_s1) + 1);
	if (!(copy))
		return (NULL);
	while (++i < size_s1)
		copy[i] = s1[i];
	copy[i] = '\0';
	return (copy);
}
