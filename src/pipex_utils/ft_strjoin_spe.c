/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_spe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:17:40 by asuteau           #+#    #+#             */
/*   Updated: 2024/02/23 10:03:00 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strslen(int size, char **strs)
{
	int	i;
	int	j;
	int	counter;

	i = 0;
	counter = 0;
	while (i < size && strs[i] != NULL)
	{
		j = 0;
		while (strs[i][j] != '\0')
		{
			j++;
			counter++;
		}
		i++;
	}
	return (counter);
}

char	*strcat_s(int size, char **strs, char *sep, char *cat_str)
{
	int		i;

	i = 0;
	while (i < size && strs[i] != NULL)
	{
		ft_strcat(cat_str, strs[i]);
		if (i < size - 1)
			ft_strcat(cat_str, sep);
		i++;
	}
	return (cat_str);
}

char	*ft_strjoin_spe(int size, char **strs, char *sep, t_var *pvar)
{
	char	*cat_str;
	int		fullsize;

	if (size <= 0)
	{
		cat_str = ft_malloc(1, sizeof(char), pvar);
		cat_str[0] = '\0';
		return (cat_str);
	}
	fullsize = (ft_strslen(size, strs) + (ft_strlen(sep) * (size - 1)) + 1);
	cat_str = ft_malloc(fullsize, sizeof(char), pvar);
	cat_str[0] = 0;
	cat_str = strcat_s(size, strs, sep, cat_str);
	return (cat_str);
}
