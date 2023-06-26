/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:23:08 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/24 16:02:18 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_2(int fd_1, int fd_2)
{
	dup2(fd_1, fd_2);
	close(fd_1);
}

int	launch(int *fd, int in, int out)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (in != 0)
			dup_2(in, 0);
		if (fd[1] != 1)
			dup_2(fd[1], 1);
		if (fd[0] != 0)
			close(fd[0]);
		exec_redir(in, out);
		if (!check_built_in())
			exec_command();
		else
			execute();
		 exit(g_data.exit_s);
	}
	return (pid);
}

void ft_pipeline(int fd[2], int in, int out)
{
	while(g_data.ms)
	{
		if (g_data.ms->next)
			pipe(fd);
		launch(fd, in ,out);
		if(fd[1] > 2)
			close(fd[1]);
		fd[1] = 1;
		if(in != 0)
			close(in);
		in = fd[0];
		fd[0] = 0;
		g_data.ms = g_data.ms->next;
	}
}

void	exit_status()
{
	if (WTERMSIG(g_data.exit_s) == SIGINT)
		g_data.exit_s = 130;
	else if (WTERMSIG(g_data.exit_s) == SIGQUIT)
		g_data.exit_s = 131;
	else if(WIFEXITED(g_data.exit_s))
		g_data.exit_s %= 255;
}

void   fork_exec(int fd_in, int fd_out)
{
	t_vdata *new;
	int fd[2];
	int pid;

	if (!g_data.ms)
		return ;
	fd[0] = 0;
	fd[1] = 1;
	pid = -1;
	new = g_data.ms;
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	if (!g_data.ms->next && check_built_in() && !g_data.ms->rd)
		execute();
	else
	{
		ft_pipeline(fd, fd_in, fd_out);
		g_data.ms = new;
		waitpid(pid, &g_data.exit_s, 0);
		while (waitpid(-1, &g_data.exit_s, 0) != -1)
			;
		exit_status();
	}
}

char *get_path(char **envp)
{
	int i;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char *split_path(char *path, char *argv)
{
	char **minipath;
	char *tmp;
	int i;

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

void exec_command()
{
	char *path;
	char **command;
	char *tmp;

	path = ft_strdup(get_path(g_data.env));
	if (!path)
	{
		perror("PATH not found!!");
		g_data.exit_s = 127;
		exit(g_data.exit_s);
	}
	if(!g_data.ms->cmd)
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
