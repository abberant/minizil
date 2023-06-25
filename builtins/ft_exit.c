/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:35:16 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/21 11:10:52 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int ft_is_num(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}


int	ft_invalid_exit(char *str)
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
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i++] - 48;
		if (num > 9223372036854775807 && sign == 1)
			return (1);
		else if (num > 9223372036854775807 && sign == -1)
			return (1);
	}
	return (0);
}

int	ft_exit()
{
    t_vdata *tmp = g_data.ms;
    int i = 1;
    char c;

    c = 0;
    if (tmp->stack[1] == NULL)
        exit(127);
    if (!ft_is_num(tmp->stack[i]))
    {
        if (ft_invalid_exit(tmp->stack[i]))
        {
            printf("minishell : exit %s: numeric argument required\n", tmp->stack[i]);
            exit(255);
        }
        c = ft_atoi(tmp->stack[i]);
		if (tmp->stack[1] && tmp->stack[2])
		{
            printf("exit\n");
            ft_putstrr_fd("minishell : exit : too many arguments\n", 2);
            g_data.exit_s = 1;
            return 0;
        }
        printf("exit\n");
        exit(c);
    }
    else
    {
        printf("exit\n");
        ft_putstrr_fd("minishell : exit : numeric argument required\n", 2);
        exit(255);
    }
}
