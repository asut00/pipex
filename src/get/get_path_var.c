/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:44:38 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/10 18:44:39 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen_until_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i] && str[i] != c)
		i++;
	return (i - 1);
}

char	*ft_strdup_until_char_spe(char *s1, char c, t_var *pvar)
{
	int		i;
	int		src_len;
	char	*dest;

	i = 1;
	src_len = ft_strlen_until_char(s1, c);
	dest = ft_malloc(src_len + 1, sizeof(char), pvar);
	while (s1[i] != '\0' && s1[i] != c)
	{
		dest[i - 1] = s1[i];
		i++;
	}
	dest[i - 1] = '\0';
	return (dest);
}

void	get_path_var(char **envp, t_var *pvar)
{
	char	*tmp_fullenv;
	int		envp_size;

	pvar->we_have_env = TRUE;
	envp_size = 0;
	while (envp[envp_size])
		envp_size++;
	tmp_fullenv = ft_strjoin_spe(envp_size, envp, "\n", pvar);
	tmp_fullenv = ft_strstr(tmp_fullenv, "\nPATH=");
	if (!tmp_fullenv)
	{
		pvar->we_have_env = FALSE;
		return ;
	}
	pvar->env_path = ft_strdup_until_char_spe(tmp_fullenv, '\n', pvar);
}
