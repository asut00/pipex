/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_and_cat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 07:47:56 by asuteau           #+#    #+#             */
/*   Updated: 2024/05/24 17:09:19 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*init_dest(char *src, char *to_add, t_var *pvar)
{
	int		src_len;
	int		to_add_len;
	char	*dest;

	src_len = ft_strlen(src);
	to_add_len = ft_strlen(to_add);
	dest = ft_malloc(src_len + to_add_len + 1, sizeof(char), pvar);
	return (dest);
}

char	*ft_strdup_and_cat(char *src, char *to_add, t_var *pvar)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	if (!src || !to_add)
		return (NULL);
	dest = init_dest(src, to_add, pvar);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	j = 0;
	while (to_add[j])
	{
		dest[i] = to_add[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
