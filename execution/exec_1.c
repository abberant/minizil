/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:53:58 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/26 21:56:11 by lsadiq           ###   ########.fr       */
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
	int	pid;

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

void	ft_pipeline(int fd[2], int in, int out)
{
	while (g_data.ms)
	{
		if (g_data.ms->next)
			pipe(fd);
		launch(fd, in, out);
		if (fd[1] > 2)
			close(fd[1]);
		fd[1] = 1;
		if (in != 0)
			close(in);
		in = fd[0];
		fd[0] = 0;
		g_data.ms = g_data.ms->next;
	}
}

void	exit_status(int status)
{
	if (WTERMSIG(status) == SIGINT)
		g_data.exit_s = 130;
	else if (WTERMSIG(status) == SIGQUIT)
		g_data.exit_s = 131;
	else if (WIFEXITED(status))
		g_data.exit_s %= 255;
}

void	fork_exec(int fd_in, int fd_out)
{
	t_vdata	*new;
	int		fd[2];
	int		pid;
	int		status;

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
		while (waitpid(-1, &status, 0) != -1)
			;
		exit_status(status);
	}
}
