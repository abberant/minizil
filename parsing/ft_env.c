/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:57:06 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/06 16:31:31 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env(t_shell *g_data)
{
    t_shell *tmp = g_data;
    int i = -1;

    while (tmp->env[++i])
    {
        if (!ft_strchr(tmp->env[i], '='))
            continue;
        printf("%s\n", tmp->env[i]);
    }
}