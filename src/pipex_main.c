/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:46:27 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/04 12:46:30 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_var	var;

	var.env_path = NULL;
	init_gen_vars(&var, argc, argv);
	if (envp && envp[0])
		get_path_var(envp, &var);
	get_cmd_paths(argc, argv, &var);
	init_pids_and_fds(&var);
	forks_loop(&var, envp);
	close_all_pipes_fds(&var);
	wait_and_get_status(&var);
	ft_lstclear(&var.garbage_collector, free);
	return (var.last_cmd_exit_status);
}
