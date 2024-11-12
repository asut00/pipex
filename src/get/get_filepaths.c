/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filepaths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:04:44 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/04 14:04:45 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_input_access_error(t_var *pvar)
{
	close_all_pipes_fds(pvar);
	ft_lstclear(&pvar->garbage_collector, free);
	ft_putstr_fd("Error: input file doesn't exist ", STDERR_FILENO);
	ft_putstr_fd("or doesn't have read permission\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	handle_open_error(char *fpath)
{
	ft_putstr_fd("Error: opening file : ", STDERR_FILENO);
	ft_putstr_fd(fpath, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	get_fd(t_var *pvar, char *fpath, char mode)
{
	int	fd;

	fd = -1;
	if (mode == 'r')
	{
		if (access(fpath, R_OK | F_OK) == -1)
			handle_input_access_error(pvar);
		fd = open(fpath, O_RDONLY);
		if (fd == -1)
			handle_open_error(fpath);
	}
	else if (mode == 'w')
	{
		fd = open(fpath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			handle_open_error(fpath);
	}
	return (fd);
}

int	get_heredoc_in_fd(void)
{
	int	hd_in_fd;

	hd_in_fd = open("/tmp/pipex_heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (hd_in_fd == -1)
	{
		ft_putstr_fd("Error: opening heredoc file : ", STDERR_FILENO);
		ft_putstr_fd("/tmp/pipex_heredoc", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (hd_in_fd);
}

int	get_append_out_fd(t_var *pvar, char *fpath)
{
	int	hd_out_fd;

	(void)pvar;
	hd_out_fd = open(fpath, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (hd_out_fd == -1)
		handle_open_error(fpath);
	return (hd_out_fd);
}
