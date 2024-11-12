/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:11:54 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/11 12:11:56 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_first_fork(t_var *pvar, int i)
{
	if (pvar->is_heredoc)
	{
		pvar->inputfile_fd = get_heredoc_in_fd();
		get_and_write_heredoc(pvar);
		close(pvar->inputfile_fd);
		pvar->inputfile_fd = open("/tmp/pipex_heredoc", O_RDONLY);
		if (pvar->inputfile_fd == -1)
			handle_open_error("/tmp/pipex_heredoc");
	}
	else if (!pvar->is_heredoc)
		pvar->inputfile_fd = get_fd(pvar, pvar->av[1], 'r');
	if (dup2(pvar->inputfile_fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Error: input file dup2 error\n", STDERR_FILENO);
		close(pvar->inputfile_fd);
		close_all_pipes_clear_and_exit(pvar);
	}
	if (dup2(pvar->pipe_fds[i][1], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Error: pipe dup2 error \n", STDERR_FILENO);
		close(pvar->inputfile_fd);
		close_all_pipes_clear_and_exit(pvar);
	}
	close(pvar->inputfile_fd);
	close_all_pipes_fds(pvar);
}

void	handle_last_fork(t_var *pvar, int i)
{
	if (pvar->is_heredoc)
		pvar->outputfile_fd = get_append_out_fd(pvar, pvar->av[pvar->ac - 1]);
	else if (!pvar->is_heredoc)
		pvar->outputfile_fd = get_fd(pvar, pvar->av[pvar->ac - 1], 'w');
	if (dup2(pvar->pipe_fds[i - 1][0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Error: pipe dup2 error\n", STDERR_FILENO);
		close(pvar->outputfile_fd);
		close_all_pipes_clear_and_exit(pvar);
	}
	if (dup2(pvar->outputfile_fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Error: output file dup2 error\n", STDERR_FILENO);
		close(pvar->outputfile_fd);
		close_all_pipes_clear_and_exit(pvar);
	}
	close(pvar->outputfile_fd);
	close_all_pipes_fds(pvar);
}

void	handle_middle_fork(t_var *pvar, int i)
{
	if (dup2(pvar->pipe_fds[i - 1][0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Error: pipe dup2 error\n", STDERR_FILENO);
		close_all_pipes_clear_and_exit(pvar);
	}
	if (dup2(pvar->pipe_fds[i][1], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Error: pipe dup2 error\n", STDERR_FILENO);
		close_all_pipes_clear_and_exit(pvar);
	}
	close_all_pipes_fds(pvar);
}

void	handle_forks(t_var *pvar, char **envp, int i)
{
	if (i == 0)
		handle_first_fork(pvar, i);
	else if (i == pvar->num_of_cmd - 1)
		handle_last_fork(pvar, i);
	else
		handle_middle_fork(pvar, i);
	if (pvar->cmds[i][0] && ft_strcmp(pvar->cmds[i][0], "exit") == 0)
		handle_exit_cmd(pvar, i);
	else if (!pvar->cmd_paths[i])
		handle_cmd_path_error(pvar, i);
	else if (execve(pvar->cmd_paths[i], pvar->cmds[i], envp) == -1)
		handle_execve_error(pvar);
	exit(EXIT_SUCCESS);
}

void	forks_loop(t_var *pvar, char **envp)
{
	int	i;

	i = 0;
	while (i < pvar->num_of_cmd)
	{
		pvar->pids[i] = fork();
		if (pvar->pids[i] == -1)
		{
			ft_putstr_fd("Error: fork error\n", STDERR_FILENO);
			close_all_pipes_fds(pvar);
			ft_lstclear_and_exit(&pvar->garbage_collector, free);
		}
		if (pvar->pids[i] == 0)
			handle_forks(pvar, envp, i);
		i++;
	}
}
