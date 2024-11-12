/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_special_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:16:59 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/11 12:17:02 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_exit_cmd(t_var *pvar, int i)
{
	if (pvar->cmds[i][1])
	{
		pvar->exit_ret_value = ft_atoi(pvar->cmds[i][1]);
		ft_lstclear(&pvar->garbage_collector, free);
		exit(pvar->exit_ret_value);
	}
	else
	{
		ft_lstclear(&pvar->garbage_collector, free);
		exit(pvar->last_cmd_exit_status);
	}
}

void	handle_cmd_path_error(t_var *pvar, int i)
{
	ft_putstr_fd("Error: command not found : ", STDERR_FILENO);
	ft_putstr_fd(pvar->cmds[i][0], STDERR_FILENO);
	ft_lstclear(&pvar->garbage_collector, free);
	exit(127);
}

void	handle_execve_error(t_var *pvar)
{
	ft_lstclear(&pvar->garbage_collector, free);
	exit(1);
}
