/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 01:10:41 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/26 22:58:51 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_kill(char *reason)
{
	ft_dprintf(2, reason);
	exit(0);
}

void	norm(char s)
{
	if (s)
	{
		ft_dprintf(2, "Error");
		exit (1);
	}
}

int	ft_atoi(char *str)
{
	int				i;
	unsigned long	num;
	int				sign;

	i = -1;
	num = 0;
	sign = 1;
	while ((str[++i] >= 9 && str[i] <= 13) || str[i] == 32)
		;
	if ((str[i] == '+' || str[i] == '-') && str[i + 1])
		if (str[i++] == '-')
			sign *= -1;
	if (!str[i])
		ft_kill("Error");
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i++] - 48;
		if (num > 9223372036854775807 && sign == 1)
			return (-1);
		else if (num > 9223372036854775807 && sign == -1)
			return (0);
	}
	norm(str[i]);
	return (num * sign);
}
