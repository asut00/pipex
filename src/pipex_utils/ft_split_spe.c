/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 07:47:56 by asuteau           #+#    #+#             */
/*   Updated: 2024/05/24 17:09:19 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char const *str, char charset)
{
	int	i;
	int	count_words;

	i = 0;
	count_words = 0;
	while (str && str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == charset)
			i++;
		if (str[i] != '\0' && !(str[i] == charset))
			count_words++;
		while (str[i] != '\0' && !(str[i] == charset))
			i++;
	}
	return (count_words);
}

static int	ft_sl_s(char const *str, char charset)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0' && !(str[i] == charset))
		i++;
	return (i);
}

static char	**attribute_words_spe(char **tab, char *str, char c, t_var *pvar)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = 0;
	while (str && str[i] != '\0')
	{
		while (str[i] != '\0' && (str[i] == c))
			i++;
		if (str[i] != '\0' && !((str[i] == c)))
		{
			y = 0;
			tab[x] = ft_malloc(ft_sl_s(&str[i], c) + 1, sizeof(char), pvar);
			while (str[i] != '\0' && !(str[i] == c))
				tab[x][y++] = str[i++];
			tab[x++][y] = '\0';
		}
	}
	tab[x] = NULL;
	return (tab);
}

char	**ft_split_spe(char *s, char c, t_var *pvar)
{
	int		word_count;
	char	**tab;

	word_count = count_words(s, c);
	tab = ft_malloc(word_count + 1, sizeof(char *), pvar);
	if (!tab)
		return (NULL);
	tab = attribute_words_spe(tab, s, c, pvar);
	return (tab);
}
