/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:12:47 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/11/17 14:42:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	char	*first_occ;

	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)(&haystack[0]));
	while (haystack[j])
	{
		if (needle[0] == haystack[j])
			first_occ = (char *)(&haystack[j]);
		while (needle[i] == haystack[j + i])
		{
			i++;
			if (i == ft_strlen(needle))
				return (first_occ);
		}
		i = 0;
		j++;
	}
	return (NULL);
}
