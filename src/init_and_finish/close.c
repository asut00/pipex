/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:58:11 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/10 18:58:12 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_previous_pipes(t_var *pvar, int i)
{
	while (i >= 1)
	{
		i--;
		close(pvar->pipe_fds[i][0]);
		close(pvar->pipe_fds[i][1]);
	}
}

void	close_all_pipes_fds(t_var *pvar)
{
	int	i;

	i = 0;
	while (i < pvar->num_of_cmd)
	{
		close(pvar->pipe_fds[i][0]);
		close(pvar->pipe_fds[i][1]);
		i++;
	}
}

void	close_all_pipes_clear_and_exit(t_var *pvar)
{
	close_all_pipes_fds(pvar);
	ft_lstclear_and_exit(&pvar->garbage_collector, free);
}
