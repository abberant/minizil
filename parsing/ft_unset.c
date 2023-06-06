/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:30:11 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/06 16:38:21 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_lentab(char *tab)
{
    int i = 0;
    while (tab[i])
        i++;
    return (i);
}

char **ft_remove(char **env, int k)
{
    int i = 0;
    int j = 0;
    char **tmp = NULL;

    if (!(tmp = malloc(sizeof(char *) * ft_len_env(env))))
        return NULL;
    while (env[i])
    {
        // printf("k = sgf \n");
        if (i != k)
        {
            tmp[j++] = ft_strdup(env[i]);
        }
        i++;
    }
    tmp[j] = NULL;
    return (tmp);
}

void ft_unset(t_shell *shell)
{
    int i = 0;
    int k = 0;
    t_shell *tmp;

    tmp = shell;
    if (tmp->ms->stack[1] == NULL)
        return;
    i = 1;
    while (tmp->ms->stack[i])
    {
        k = 0;
        printf("stack = %s\n", tmp->ms->stack[i]);
        if (ft_alpha(tmp->ms->stack[i][0]))
        {
            while (tmp->env[k])
            {
                if (!ft_strncmp(tmp->ms->stack[i], tmp->env[k], ft_lentab(tmp->ms->stack[i])))
                    tmp->env = ft_remove(tmp->env, k);
                k++;
            }
        }
        else
        {
            ft_putstrr_fd("minishell: unset: `", 2);
            ft_putstrr_fd(tmp->ms->stack[i], 2);
            ft_putstrr_fd("': not a valid identifier\n", 2);
            g_data.exit_s = 1;
        }
        i++;
    }
}