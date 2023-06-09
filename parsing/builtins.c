/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:17:46 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/09 01:31:16 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute(t_shell *shell)
{
    int i;
    t_shell temp = *shell;
    while (temp.ms)
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