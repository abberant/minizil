/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:35:16 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/07 14:20:33 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void	ft_exit(t_shell *shell)
{
    t_shell *tmp = shell;
    int i = 1;
    int nb;

    if (tmp->ms->stack[1] == NULL)
        exit(0);
    if (!ft_is_num(tmp->ms->stack[i]))
    {
        nb = ft_atoi(tmp->ms->stack[i]);
		if (tmp->ms->stack[1] && tmp->ms->stack[2])
		{
            printf("exit\n");
            ft_putstrr_fd("minishell : exit : too many arguments\n", 2);
            g_data.exit_s = 1;
            return;
        }
		else if (nb > 256)
		{
			printf("exit\n");
			g_data.exit_s = nb % 256;
			exit(g_data.exit_s);
		}
		else if(nb < 0)
		{
			printf("exit\n");
        	g_data.exit_s = 256 + nb;
        	exit(g_data.exit_s);
		}
		else if(nb == 255)
		{
			printf("exit\n");
			g_data.exit_s = 255;
        	exit(g_data.exit_s);
		}
        printf("exit\n");
        g_data.exit_s = 0;
        exit(g_data.exit_s);
    }
    else
    {
        printf("exit\n");
        ft_putstrr_fd("minishell : exit : numeric argument required\n", 2);
        g_data.exit_s = 255;
        exit(g_data.exit_s);
    }
}
