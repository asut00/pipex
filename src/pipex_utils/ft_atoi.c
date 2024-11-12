/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:42:04 by asuteau           #+#    #+#             */
/*   Updated: 2024/07/11 12:42:05 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	sign_count;

	res = 0;
	sign = 1;
	sign_count = 0;
	while (*str && (*str == 32 || (9 <= *str && *str <= 13)))
		str++;
	while (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign = sign * -1;
		sign_count++;
		str++;
	}
	if (sign_count > 1)
		return (0);
	while (*str && '0' <= *str && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}
