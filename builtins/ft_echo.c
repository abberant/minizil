/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:51:27 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/21 11:10:52 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_look(char **stack)
{
    int i = 1;
    int j = 0;
    g_data.flag = 1;
    while (stack[i])
    {
        if (stack[i][0] != '-' || stack[i][1] != 'n')
            return i;
        j = 0;
        while (stack[i][j])
        {
            if (stack[i][0] == '-' && j == 0)
                j++;
            if (stack[i][j] != 'n')
            {
                // printf("%d\n", i);
                return i;
            }
            j++;
        }
        g_data.flag = 0;
        i++;
    }
    return (-1);
}

int ft_echo(t_shell *shell)
{
    t_shell *tmp = shell;

    int i;
    i = ft_look(tmp->ms->stack);
    if (i == -1)
    {
        printf("\n");
        g_data.exit_s = 0;
        return (g_data.exit_s);
    }
    if (i == 0)
        return(0);
    while (tmp->ms->stack[i])
    {
        printf("%s", tmp->ms->stack[i]);
        i++;
        if (tmp->ms->stack[i])
            printf(" ");
    }
    if (g_data.flag)
        printf("\n");
    return (0);
}