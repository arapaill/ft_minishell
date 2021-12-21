/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:24:26 by user42            #+#    #+#             */
/*   Updated: 2021/12/16 18:23:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_envncmp(char *needle, char *env, int len)
{
	int		i;

	i = 0;
	if (len == 0)
		return (0);
	while (i < len && needle[i] && env[i])
	{
		if (needle[i] != env[i])
			return ((unsigned char)(needle)[i] - (unsigned char)(env)[i]);
		i++;
	}
	if (i == len)
		i--;
	if (env[i + 1] != '=')
		return (-1);
	return ((unsigned char)(needle)[i] - (unsigned char)(env)[i]);
}

int	envchr(char *value, int i)
{
	int		len;
	char	*needle;

	len = 0;
	while (value[len] && value[len] != '=' && value[len] != '+')
		len++;
	if (value[len] == '+' && value[len + 1] != '=')
		return (-2);
	needle = malloc(sizeof(char *) * len);
	if (!needle)
		cmd_error();
	while (++i < len)
		needle[i] = value[i];
	needle[len] = '\0';
	i = -1;
	while (g_minishell.env[++i])
	{
		if (!ft_envncmp(needle, g_minishell.env[i], len))
		{
			free(needle);
			return (i);
		}
	}
	free(needle);
	return (-1);
}

int	ft_envplussearch(char *value)
{
	int		i;

	i = 0;
	while (value[i] != '=')
	{
		if (value[i] == '+')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_plus_cut(char *value)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char *) * ft_strlen(value));
	if (!ret)
		cmd_error();
	while (value[i])
	{
		if (value[i] == '+')
			i++;
		ret[j] = value[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	free(value);
	value = NULL;
	return (ret);
}
