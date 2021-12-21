/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:20:29 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/06/11 00:58:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_bool	is_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (c != set[i] && set[i])
		i++;
	if (c == set[i])
		return (True);
	else
		return (False);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	end;
	size_t	start;
	char	*copy;

	if (s == NULL || set == NULL)
		return (0);
	start = 0;
	end = ft_strlen(s);
	while (is_set(s[start], set) == True && s[start])
		start++;
	while (is_set(s[end], set) == True && end > start)
		end--;
	copy = malloc(sizeof(char) * ((end - start) + 2));
	if (!(copy))
		return (NULL);
	ft_memcpy(copy, &s[start], ((end - start) + 1));
	copy[((end - start) + 1)] = '\0';
	return (copy);
}
