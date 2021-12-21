/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:06:49 by cgoncalv          #+#    #+#             */
/*   Updated: 2019/10/11 16:16:29 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*cpy_dst;
	const char	*cpy_src;
	size_t		cpy_size;
	size_t		dst_size;

	cpy_dst = dst;
	cpy_src = src;
	cpy_size = size;
	while (cpy_size-- != 0 && *cpy_dst)
		cpy_dst++;
	dst_size = cpy_dst - dst;
	cpy_size = size - dst_size;
	if (cpy_size == 0)
		return (dst_size + ft_strlen(cpy_src));
	while (*cpy_src)
	{
		if (cpy_size != 1)
		{
			*cpy_dst++ = *cpy_src;
			cpy_size--;
		}
		cpy_src++;
	}
	*cpy_dst = '\0';
	return (dst_size + (cpy_src - src));
}
