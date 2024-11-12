/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 07:47:56 by asuteau           #+#    #+#             */
/*   Updated: 2024/05/15 08:28:15 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_spe(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] && str[i] == c)
		i++;
	return (i);
}

char	*free_and_return_null(char	**m1, char **m2, char **m3, char **m4)
{
	if (m1 && *m1)
	{
		free(*m1);
		*m1 = NULL;
	}
	if (m2 && *m2)
	{
		free(*m2);
		*m2 = NULL;
	}
	if (m3 && *m3)
	{
		free(*m3);
		*m3 = NULL;
	}
	if (m4 && *m4)
	{
		free(*m4);
		*m4 = NULL;
	}
	return (NULL);
}

void	*ft_memcpy_spe(void *dst, const void *src, int *i, char c)
{
	char	*ddst;
	char	*ssrc;

	*i = 0;
	if (!dst && !src)
		return (dst);
	ddst = (char *)dst;
	ssrc = (char *)src;
	while (ssrc[*i] && ssrc[*i] != c)
	{
		ddst[*i] = ssrc[*i];
		(*i)++;
	}
	ddst[*i] = '\0';
	return (dst);
}

char	*get_next_line_manager(int fd, char *lim)
{
	char		*returned_string;
	static char	*temp;

	returned_string = get_next_line(fd, temp);
	if (!returned_string)
	{
		if (temp)
			free(temp);
		return (NULL);
	}
	if (!ft_strcmp_until_char(returned_string, lim, '\n'))
	{
		if (temp)
			free(temp);
		if (returned_string)
			free(returned_string);
		return (NULL);
	}
	return (returned_string);
}

char	*get_next_line(int fd, char *temp)
{
	int			bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(1);
	if (!line)
		return (free_and_return_null(&line, &temp, NULL, NULL));
	line[0] = '\0';
	if (!temp)
	{
		temp = malloc(1);
		if (!temp)
			return (free_and_return_null(&line, &temp, NULL, NULL));
		temp[0] = '\0';
	}
	if (temp && (ft_strlen_spe(temp, '\n') != ft_strlen_spe(temp, '\0')))
		return (deal_with_temp_that_still_holds_nl(&temp, line));
	bytes_read = 1;
	line = while_loop(fd, &bytes_read, &line, &temp);
	if (!line)
		return (free_and_return_null(&line, &temp, NULL, NULL));
	return (finishers(bytes_read, &temp, line));
}
