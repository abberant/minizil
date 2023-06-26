/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:23:08 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/26 14:59:00 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*split_path(char *path, char *argv)
{
	char	**minipath;
	char	*tmp;
	int		i;

	i = 0;
	if (!access(argv, X_OK))
		return (argv);
	minipath = ft_split(path, ':');
	while (minipath[i])
	{
		tmp = minipath[i];
		minipath[i] = s_concatinate(tmp, '/');
		tmp = minipath[i];
		minipath[i] = ft_strjoin(tmp, argv);
		if (!access(minipath[i], F_OK))
			return (minipath[i]);
		i++;
	}
	return (0);
}

void	exec_command(void)
{
	char	*path;
	char	**command;
	char	*tmp;

	path = ft_strdup(get_path(g_data.env));
	if (!path)
	{
		perror("PATH not found!!");
		g_data.exit_s = 127;
		exit(g_data.exit_s);
	}
	if (!g_data.ms->cmd)
		exit(0);
	command = &g_data.ms->stack[0];
	tmp = split_path(path, command[0]);
	free(path);
	if (execve(tmp, command, g_data.env) == -1)
	{
		ft_dprintf(2, ERR_CMD_NOT_FOUND, *g_data.ms->stack);
		exit(127);
	}
}
