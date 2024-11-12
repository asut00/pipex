/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_write_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:04:44 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/04 14:04:45 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp_until_char(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0'
		&& s2[i] != '\0' && s1[i] != c && s2[i] != c)
		i++;
	if (s1[i] == c && s2[i] == '\0')
		return (0);
	if (s1[i] == '\0' && s2[i] == c)
		return (0);
	return (s1[i] - s2[i]);
}

void	get_and_write_heredoc(t_var *pvar)
{
	char	*line;

	line = "";
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line_manager(STDIN_FILENO, pvar->hd_lim);
		if (!line)
			return ;
		write(pvar->inputfile_fd, line, ft_strlen(line));
		free(line);
	}
}
