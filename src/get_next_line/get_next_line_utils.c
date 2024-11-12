/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 07:47:56 by asuteau           #+#    #+#             */
/*   Updated: 2024/05/15 08:28:15 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*deal_with_temp_that_still_holds_nl(char **temp, char *line)
{
	int		bytes_to_write;
	char	*new_line;
	char	*new_temp;
	int		i;
	int		j;

	bytes_to_write = ft_strlen_spe(*temp, '\n');
	new_line = malloc(bytes_to_write + 1);
	if (!new_line)
		return (free_and_return_null(temp, &line, NULL, NULL));
	ft_memcpy_spe(new_line, *temp, &i, '\n');
	new_line[i] = '\n';
	new_line[i + 1] = '\0';
	i++;
	bytes_to_write = ft_strlen_spe(&(*temp)[i], '\0');
	new_temp = malloc (bytes_to_write + 1);
	if (!new_temp)
		return (free_and_return_null(temp, &line, &new_line, NULL));
	ft_memcpy_spe(new_temp, &(*temp)[i], &j, '\0');
	free_and_return_null(temp, NULL, NULL, NULL);
	*temp = new_temp;
	free_and_return_null(&line, NULL, NULL, NULL);
	return (new_line);
}

char	*buff_w_nl(char *buffer, char **ptemp, int *bytes_read, char *new_line)
{
	int	x;

	free_and_return_null(ptemp, NULL, NULL, NULL);
	*ptemp = malloc((*bytes_read - ft_strlen_spe(buffer, '\n') + 1));
	if (!*ptemp)
		return (NULL);
	ft_memcpy_spe(*ptemp, &buffer[ft_strlen_spe(buffer, '\n')], &x, '\0');
	new_line[0] = '\n';
	new_line[1] = '\0';
	if (*ptemp && !(ft_strlen_spe(*ptemp, '\0')))
		free_and_return_null(ptemp, NULL, NULL, NULL);
	return (new_line);
}

char	*loop_start(char *buffer, t_var *var, char **ptemp, char **pline)
{
	int		templen;
	char	*new_line;
	int		bytes_to_write;

	templen = 0;
	new_line = NULL;
	if (*ptemp)
		templen = ft_strlen_spe(*ptemp, '\0');
	bytes_to_write = ft_strlen_spe(*pline, '\0') + ft_strlen_spe(buffer, '\n');
	new_line = malloc(bytes_to_write + templen + 1);
	if (!new_line)
		return (free_and_return_null(pline, ptemp, NULL, NULL));
	if (*ptemp && ft_strlen_spe(*ptemp, '\0'))
	{
		ft_memcpy_spe(new_line, *ptemp, &var->i, '\0');
		free_and_return_null(ptemp, NULL, NULL, NULL);
	}
	else if (*pline)
		ft_memcpy_spe(new_line, *pline, &var->i, '\0');
	ft_memcpy_spe(&new_line[var->i], buffer, &var->j, '\n');
	free_and_return_null(pline, NULL, NULL, NULL);
	return (new_line);
}

char	*while_loop(int fd, int *pbytes_read, char **pline, char **ptemp)
{
	t_var	var;
	char	*nl;
	char	buffer[BUFFER_SIZE + 1];

	while (*pbytes_read > 0)
	{
		*pbytes_read = read(fd, &buffer, BUFFER_SIZE);
		if (*pbytes_read > 0)
		{
			buffer[*pbytes_read] = '\0';
			nl = loop_start((char *)buffer, &var, ptemp, pline);
			if (!nl)
				return (free_and_return_null(pline, ptemp, NULL, NULL));
			if (buffer[var.j] == '\n')
			{
				if (!buff_w_nl(buffer, ptemp, pbytes_read, &nl[var.i + var.j]))
					return (free_and_return_null(&nl, ptemp, NULL, NULL));
				return (nl);
			}
			*pline = nl;
		}
		else if (*pbytes_read < 0)
			return (free_and_return_null(pline, ptemp, NULL, NULL));
	}
	return (*pline);
}

char	*finishers(int bytes_read, char **ptemp, char *line)
{
	char	*new_line;
	int		i;

	if (bytes_read <= 0 && *ptemp && *ptemp[0])
	{
		if (*ptemp
			&& (ft_strlen_spe(*ptemp, '\n') != ft_strlen_spe(*ptemp, '\0')))
			return (deal_with_temp_that_still_holds_nl(ptemp, line));
		else
		{
			new_line = malloc(ft_strlen_spe(*ptemp, '\0') + 1);
			if (!new_line)
				return (free_and_return_null(&line, ptemp, NULL, NULL));
			ft_memcpy_spe(new_line, *ptemp, &i, '\0');
			free_and_return_null(&line, ptemp, NULL, NULL);
			return (new_line);
		}
	}
	if (ft_strlen_spe(line, '\0'))
	{
		if (*ptemp && !(ft_strlen_spe(*ptemp, '\0')))
			free_and_return_null(ptemp, NULL, NULL, NULL);
		return (line);
	}
	return (free_and_return_null(&line, ptemp, NULL, NULL));
}
