/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:17:46 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/10 16:38:26 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute(t_shell *shell)
{
    int i;
    t_shell temp = *shell;
    puts("here");
    printf("%s\n", temp.ms->cmd);
    while (temp.ms && temp.ms->cmd)
    {
        i = 0;
        if (!ft_strcmp(temp.ms->cmd, "pwd"))
            ft_pwd();
        if (!ft_strcmp(temp.ms->cmd, "echo"))
            ft_echo(shell);
        if (!ft_strcmp(temp.ms->cmd, "env"))
            ft_env(shell);
        if (!ft_strcmp(temp.ms->cmd, "cd"))
            ft_cd(shell);
        if(!ft_strcmp(temp.ms->cmd, "export"))
        	ft_export(shell);
        if (!ft_strcmp(temp.ms->cmd, "unset"))
        	ft_unset(shell);
        if(!ft_strcmp(temp.ms->cmd, "exit"))
        	ft_exit(shell);
        temp.ms = temp.ms->next;
    }
}