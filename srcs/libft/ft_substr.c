/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:51:15 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/06/11 00:57:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (s == NULL)
		return (0);
	if (start > ft_strlen(s))
	{
		ret = malloc(sizeof(char) * 1);
		if (!(ret))
			return (NULL);
		ret[0] = '\0';
		return (ret);
	}
	ret = malloc(sizeof(char) * (len + 1));
	if (!(ret))
		return (NULL);
	ft_memcpy(ret, &s[start], len);
	ret[len] = '\0';
	return (ret);
}
