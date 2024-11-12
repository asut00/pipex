/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:44:38 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/10 18:44:39 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_absolute_path(t_var *pvar, int *path_found, int i)
{
	(*path_found)++;
	pvar->cmd_paths[i] = pvar->cmds[i][0];
}

void	handle_basic_path(t_var *pvar, int *path_found, int i, char *b_path)
{
	(*path_found)++;
	pvar->cmd_paths[i] = b_path;
}

void	handle_path_not_found(t_var *pvar, int i)
{
	pvar->cmd_paths[i] = NULL;
	ft_putstr_fd("Error: Could not access command: ", STDERR_FILENO);
	ft_putstr_fd(pvar->cmds[i][0], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
