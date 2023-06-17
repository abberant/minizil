/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:17:46 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/17 16:42:30 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute(t_shell *shell)
{
    t_shell temp;
	
	temp = *shell;
    while (temp.ms && temp.ms->cmd)
    {
        if (!ft_strcmp(temp.ms->cmd, "pwd"))
            ft_pwd(shell);
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
int check_built_in(t_shell *shell)
{
    t_shell temp;
	
	temp = *shell;
    while (temp.ms && temp.ms->cmd)
    {
        if (!ft_strcmp(temp.ms->cmd, "pwd"))
            return (1);
        if (!ft_strcmp(temp.ms->cmd, "echo"))
            return (1);
        if (!ft_strcmp(temp.ms->cmd, "env"))
            return (1);
        if (!ft_strcmp(temp.ms->cmd, "cd"))
            return (1);
        if(!ft_strcmp(temp.ms->cmd, "export"))
        	return (1);
        if (!ft_strcmp(temp.ms->cmd, "unset"))
        	return (1);
        if(!ft_strcmp(temp.ms->cmd, "exit"))
        	return (1);
        temp.ms = temp.ms->next;
    }
    return (0);
}