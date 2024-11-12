/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:21:07 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/04 13:21:09 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* ********************************** INCL ********************************** */

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

/* ********************************* STRUCT ********************************* */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_var
{
	int		ac;
	char	**av;

	int		we_have_env;

	int		inputfile_fd;
	int		outputfile_fd;
	int		**pipe_fds;

	char	***cmds;
	char	**cmd_paths;
	char	*env_path;
	char	**splitted_env;
	int		num_of_cmd;
	int		num_of_env_path;
	int		status;
	int		last_cmd_exit_status;
	int		exit_ret_value;

	int		is_heredoc;
	char	*hd_lim;

	pid_t	*pids;

	t_list	*garbage_collector;
}				t_var;

typedef struct s_list_explorer
{
	t_list	*voyager;
	t_list	*previous_node;
	t_list	*next_node;
	int		found_node;
}				t_list_explorer;

/* ********************************* MACROS ********************************* */

# define FALSE 0
# define TRUE 1
# define ARGC_OFFSET 3
# define ARGC_OFFSET_HD 4

/* ********************************* FUNCT ********************************** */

// pipex_init_and_finish.c
void	init_gen_vars(t_var *pvar, int argc, char **argv);
void	init_pids_and_fds(t_var *pvar);
void	wait_and_get_status(t_var *pvar);

// get_path_var.c
void	get_path_var(char **envp, t_var *pvar);
int		ft_strlen_until_char(char *str, char c);
char	*ft_strdup_until_char_spe(char *s1, char c, t_var *pvar);

// get_cmdpaths.c
void	fill_up_cmds_array(int argc, char **argv, t_var *pvar);
void	try_env_path_loop(t_var *pvar, int *path_found, int i, int *j);
void	get_cmd_paths(int argc, char **argv, t_var *pvar);

// get_filepaths.c
int		get_fd(t_var *pvar, char *fpath, char mode);
void	get_file_paths(int argc, char **argv, t_var *pvar);
void	get_cmd_paths(int argc, char **argv, t_var *pvar);
void	check_args(int argc, char **argv, t_var *pvar);
int		get_heredoc_in_fd(void);
int		get_append_out_fd(t_var *pvar, char *fpath);
void	handle_open_error(char *fpath);

// get_handlers.c
void	handle_absolute_path(t_var *pvar, int *path_found, int i);
void	handle_basic_path(t_var *pvar, int *path_found, int i, char *b_path);
void	handle_path_not_found(t_var *pvar, int i);

// get_and_write_heredoc.c
void	get_and_write_heredoc(t_var *pvar);

// garbage_collector.c
void	*ft_malloc(int len, int size, t_var *pvar);
void	ft_lst_find_and_free(t_list **lst, void *content_to_find);

// ft_lstclear.c
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstclear_and_exit(t_list **lst, void (*del)(void *));

// close.c
void	close_everything(t_var *pvar);
void	close_everything_soft(t_var *pvar, int i);
void	close_previous_pipes(t_var *pvar, int i);
void	close_all_pipes_fds(t_var *pvar);
void	close_all_pipes_clear_and_exit(t_var *pvar);

// forks.c
void	forks_loop(t_var *pvar, char **envp);
void	handle_forks(t_var *pvar, char **envp, int i);
void	handle_first_fork(t_var *pvar, int i);
void	handle_last_fork(t_var *pvar, int i);
void	handle_middle_fork(t_var *pvar, int i);

// forks_special_cases.c
void	handle_exit_cmd(t_var *pvar, int i);
void	handle_cmd_path_error(t_var *pvar, int i);
void	handle_execve_error(t_var *pvar);

// pipex_utils.c
int		ft_strlen(char *str);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strcat(char *dest, char *src);
int		ft_strcmp(char *s1, char *s2);
int		ft_strcmp_until_char(char *s1, char *s2, char c);

// ft_atoi.c
int		ft_atoi(const char *str);

// ft_split_spe.c
char	**ft_split_spe(char *s, char c, t_var *pvar);

// ft_strjoin_spe.c
char	*ft_strjoin_spe(int size, char **strs, char *sep, t_var *pvar);

// ft_strdup_and_cat.c
char	*ft_strdup_and_cat(char *src, char *to_add, t_var *pvar);

// get_next_line.c
char	*get_next_line(int fd);
char	*get_next_line_manager(int fd, char *lim);

#endif
