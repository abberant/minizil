/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:51:27 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/10 16:06:25 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void ft_echo(t_shell *shell)
{
    t_shell *tmp = shell;

    int i;
    // printf("here\n");
    i = ft_look(tmp->ms->stack);
    // printf("dkhlt \n");
    // printf("%d\n", i);
    if (i == -1)
    {
        printf("\n");
        return;
    }
    if (i == 0)
        return;
    while (tmp->ms->stack[i])
    {
        printf("%s", tmp->ms->stack[i]);
        i++;
        if (tmp->ms->stack[i])
            printf(" ");
    }
    // printf("%d", g_data.flag);
    if (g_data.flag)
        printf("\n");
    // free(tmp->ms->stack);
    // printf("HelloNewLine!\n");
}