/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:51:50 by cgoncalv          #+#    #+#             */
/*   Updated: 2021/11/16 16:35:26 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_mllc(char **splitted, size_t k)
{
	size_t	i;

	i = -1;
	while (++i > k)
		free(splitted[i]);
	free(splitted);
	return (0);
}

static size_t	nbr_str(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue ;
		}
		count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char	**malloc_splitted(char const *s, char c)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * (nbr_str(s, c) + 1));
	if (!(ret))
		return (NULL);
	else
		return (ret);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	k;
	size_t	start;
	char	**splitted;

	i = 0;
	k = 0;
	if (s == NULL)
		return (NULL);
	splitted = malloc_splitted(s, c);
	while (s[i] && k < (nbr_str(s, c)))
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		splitted[k] = malloc(sizeof(char) * ((i - start) + 1));
		if (!(splitted[k]))
			return (free_mllc(splitted, k));
		ft_strlcpy(splitted[k], &s[start], i - start + 1);
		k++;
	}
	splitted[k] = NULL;
	return (splitted);
}
