/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 07:47:56 by asuteau           #+#    #+#             */
/*   Updated: 2024/05/15 08:28:15 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif
# if BUFFER_SIZE > 125000 || BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_var
{
	int	i;
	int	j;
}	t_var;

int		ft_strcmp(char *s1, char *s2);
int		ft_strcmp_until_char(char *s1, char *s2, char c);
size_t	ft_strlen_spe(char *str, char c);
char	*buffer_read(int fd, int *pbytes_read);
char	*free_and_return_null(char	**m1, char **m2, char **m3, char **m4);
void	*ft_memcpy_spe(void *dst, const void *src, int *i, char c);
char	*deal_with_temp_that_still_holds_nl(char **temp, char *line);
char	*buff_w_nl(char *buffer, char **ptemp, int *bytes_read, char *new_line);
char	*loop_start(char *buffer, t_var *var, char **ptemp, char **pline);
char	*while_loop(int fd, int *pbytes_read, char **pline, char **ptemp);
char	*finishers(int bytes_read, char **ptemp, char *line);
char	*get_next_line(int fd, char *temp);

#endif