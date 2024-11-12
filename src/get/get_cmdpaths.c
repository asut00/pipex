/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdpaths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:45:37 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/11 13:45:39 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fill_up_cmds_array(int argc, char **argv, t_var *pvar)
{
	int	av_offset;
	int	i;

	(void)argc;
	av_offset = 2;
	if (pvar->is_heredoc)
		av_offset = 3;
	pvar->cmds = ft_malloc(pvar->num_of_cmd + 1, sizeof(char **), pvar);
	i = 0;
	while (i < pvar->num_of_cmd)
	{
		pvar->cmds[i] = ft_split_spe(argv[i + av_offset], ' ', pvar);
		i++;
	}
	pvar->cmds[i] = NULL;
}

void	try_env_path_loop(t_var *pvar, int *path_found, int i, int *j)
{
	char	*tmp_path;
	int		size;

	while (pvar->we_have_env && pvar->splitted_env
		&& pvar->splitted_env[0] && pvar->splitted_env[*j]
		&& *path_found == 0 && pvar->cmds[i][0])
	{
		size = ft_strlen(pvar->splitted_env[*j]) + ft_strlen(pvar->cmds[i][0]);
		tmp_path = ft_malloc(size + 2, 1, pvar);
		tmp_path[0] = '\0';
		ft_strcat(tmp_path, pvar->splitted_env[*j]);
		ft_strcat(tmp_path, "/");
		ft_strcat(tmp_path, pvar->cmds[i][0]);
		if (access(tmp_path, X_OK) == 0)
		{
			(*path_found)++;
			pvar->cmd_paths[i] = tmp_path;
		}
		else
			ft_lst_find_and_free(&pvar->garbage_collector, tmp_path);
		(*j)++;
	}
}

void	try_basic_access(t_var *pvar, int i, int *path_found)
{
	char	*basic_path;

	if (access(pvar->cmds[i][0], X_OK) == 0)
		handle_absolute_path(pvar, path_found, i);
	else if (!(*path_found))
	{
		basic_path = ft_strdup_and_cat("/bin/", pvar->cmds[i][0], pvar);
		if (access(basic_path, X_OK) == 0)
			handle_basic_path(pvar, path_found, i, basic_path);
	}
	else if (!(*path_found))
	{
		basic_path = ft_strdup_and_cat("/bin/usr/", pvar->cmds[i][0], pvar);
		if (access(basic_path, X_OK) == 0)
			handle_basic_path(pvar, path_found, i, basic_path);
	}
}

void	get_cmd_paths(int argc, char **argv, t_var *pvar)
{
	int		i;
	int		j;
	int		path_found;

	fill_up_cmds_array(argc, argv, pvar);
	if (pvar->env_path && pvar->env_path[0])
		pvar->splitted_env = ft_split_spe(pvar->env_path + 5, ':', pvar);
	if (pvar->env_path)
		ft_lst_find_and_free(&pvar->garbage_collector, pvar->env_path);
	pvar->cmd_paths = ft_malloc(pvar->num_of_cmd, sizeof(char *), pvar);
	i = 0;
	while (i < pvar->num_of_cmd)
	{
		j = 0;
		path_found = 0;
		try_basic_access(pvar, i, &path_found);
		try_env_path_loop(pvar, &path_found, i, &j);
		if (path_found == 0)
			handle_path_not_found(pvar, i);
		i++;
	}
}
