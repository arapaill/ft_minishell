/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:05:24 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/09/30 16:07:55 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*array;
	size_t	len1;
	size_t	len2;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	array = malloc(sizeof(char ) * (len1 + len2 + 1));
	if (!array)
		return (NULL);
	ft_memcpy(array, s1, len1);
	ft_memcpy(&array[len1], s2, len2 + 1);
	free(s1);
	return (array);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	size_s1;
	size_t	size_s2;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (s1 == NULL || s2 == NULL)
		return (0);
	ret = malloc(sizeof(char) * (size_s1 + size_s2) + 1);
	if (!(ret))
		return (NULL);
	ft_memcpy(ret, s1, size_s1);
	ft_memcpy(&ret[size_s1], s2, size_s2 + 1);
	return (ret);
}
