/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_finish.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:23:36 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/11 12:23:37 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_gen_vars(t_var *pvar, int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	pvar->we_have_env = FALSE;
	pvar->is_heredoc = FALSE;
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		if (argc < 6)
		{
			ft_putstr_fd("Error: wrong number of arguments\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		pvar->is_heredoc = TRUE;
		pvar->hd_lim = argv[2];
	}
	pvar->ac = argc;
	pvar->av = argv;
	pvar->num_of_cmd = argc - ARGC_OFFSET;
	if (pvar->is_heredoc == TRUE)
		pvar->num_of_cmd = argc - ARGC_OFFSET_HD;
	pvar->last_cmd_exit_status = EXIT_SUCCESS;
	pvar->garbage_collector = NULL;
}

void	init_pids_and_fds(t_var *pvar)
{
	int	i;

	pvar->pids = ft_malloc(pvar->num_of_cmd, sizeof(pid_t), pvar);
	pvar->pipe_fds = ft_malloc(pvar->num_of_cmd, sizeof(int *), pvar);
	i = 0;
	while (i < pvar->num_of_cmd)
	{
		pvar->pipe_fds[i] = ft_malloc(2, sizeof(int), pvar);
		if (pipe(pvar->pipe_fds[i]) == -1)
		{
			close_previous_pipes(pvar, i);
			ft_putstr_fd("Error: pipe function error\n", STDERR_FILENO);
			ft_lstclear_and_exit(&pvar->garbage_collector, free);
		}
		i++;
	}
}

void	wait_and_get_status(t_var *pvar)
{
	int	i;

	i = 0;
	while (i < pvar->num_of_cmd)
	{
		if (waitpid(pvar->pids[i], &pvar->status, 0) == -1)
		{
			ft_putstr_fd("Error: waitpid error\n", STDERR_FILENO);
			ft_lstclear_and_exit(&pvar->garbage_collector, free);
		}
		if (i == pvar->num_of_cmd - 1 && WIFEXITED(pvar->status))
			pvar->last_cmd_exit_status = WEXITSTATUS(pvar->status);
		i++;
	}
}
