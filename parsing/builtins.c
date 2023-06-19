/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:17:46 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/19 00:11:33 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute(t_shell *shell)
{
    t_shell temp;
	
	temp = *shell;
    while (temp.ms && temp.ms->cmd)
    {
        if (!ft_strcmp(temp.ms->cmd, "pwd"))
            return (ft_pwd(shell));
        if (!ft_strcmp(temp.ms->cmd, "echo"))
            return(ft_echo(shell));
        if (!ft_strcmp(temp.ms->cmd, "env"))
            return (ft_env(shell));
        if (!ft_strcmp(temp.ms->cmd, "cd"))
            return (ft_cd(shell));
        if(!ft_strcmp(temp.ms->cmd, "export"))
        	return (ft_export(shell));
        if (!ft_strcmp(temp.ms->cmd, "unset"))
        	return (ft_unset(shell));
        if(!ft_strcmp(temp.ms->cmd, "exit"))
        	return (ft_exit(shell));
        temp.ms = temp.ms->next;
    }
    return (0);
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