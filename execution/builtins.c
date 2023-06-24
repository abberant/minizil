/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:17:46 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/25 00:27:54 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute(t_shell *shell)
{
	t_shell	temp;

	temp = *shell;
	while (temp.ms && temp.ms->cmd)
	{
		if (!ft_strcmp(temp.ms->cmd, "pwd") || ft_strcmp(temp.ms->cmd, "PWD"))
			return (ft_pwd());
		if (!ft_strcmp(temp.ms->cmd, "echo") || ft_strcmp(temp.ms->cmd, "ECHO"))
			return (ft_echo(shell));
		if (!ft_strcmp(temp.ms->cmd, "env") || ft_strcmp(temp.ms->cmd, "ENV"))
			return (ft_env(shell));
		if (!ft_strcmp(temp.ms->cmd, "cd"))
			return (ft_cd());
		if (!ft_strcmp(temp.ms->cmd, "export"))
			return (ft_export(shell));
		if (!ft_strcmp(temp.ms->cmd, "unset"))
			return (ft_unset(shell));
		if (!ft_strcmp(temp.ms->cmd, "exit"))
			return (ft_exit(shell));
		temp.ms = temp.ms->next;
	}
	return (0);
}

int	check_built_in(t_shell *shell)
{
	t_shell	temp;

	temp = *shell;
	while (temp.ms && temp.ms->cmd)
	{
		if (!ft_strcmp(temp.ms->cmd, "pwd") || ft_strcmp(temp.ms->cmd, "PWD"))
			return (1);
		if (!ft_strcmp(temp.ms->cmd, "echo") || ft_strcmp(temp.ms->cmd, "ECHO"))
			return (1);
		if (!ft_strcmp(temp.ms->cmd, "env") || ft_strcmp(temp.ms->cmd, "ENV"))
			return (1);
		if (!ft_strcmp(temp.ms->cmd, "cd"))
			return (1);
		if (!ft_strcmp(temp.ms->cmd, "export"))
			return (1);
		if (!ft_strcmp(temp.ms->cmd, "unset"))
			return (1);
		if (!ft_strcmp(temp.ms->cmd, "exit"))
			return (1);
		temp.ms = temp.ms->next;
	}
	return (0);
}
