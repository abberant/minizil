/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:23:08 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/17 22:09:44 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void dup_2(int fd_1, int fd_2)
{
    dup2(fd_1, fd_2);
    close(fd_1);
}
void	dupfd2fd(int fd, int othe_fd)
{
	dup2(fd, othe_fd);
	close(fd);
}

void	dup_ends(int *ends, int fd_in)
{
	if (fd_in != STDIN_FILENO)
		dupfd2fd(fd_in, STDIN_FILENO);
	dupfd2fd(ends[1], STDOUT_FILENO);
	if (ends[0] > 2)
		close(ends[0]);
}
void    fork_exec(int fd_in, int fd_out)
{
    int pid;
    int end[2];

    fd_in = STDIN_FILENO;
    if (pipe(end) == -1)
        perror("pipe");
    pid = fork();
    if (!pid)
    {
        if (g_data.ms)
        {
		exec_redir(fd_in, fd_out);
            if (!check_built_in(&g_data))
                exec_command();
        }
		exit (0);
    }
    else
	{
        if(check_built_in(&g_data))
	    	execute(&g_data);
		wait(0);
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
        minipath[i] = ft_strjoin(tmp, "/");
        // free(tmp);
        tmp = minipath[i];
        minipath[i] = ft_strjoin(tmp, argv);
        if (!access(minipath[i], F_OK))
            return (minipath[i]);
        // free(tmp);
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
        ft_putstrr_fd("minishell : command not found: ", 2);
        ft_putstrr_fd(*g_data.ms->stack, 2);
        ft_putchar_fd('\n', 2);
        g_data.exit_s = 127;
    } 
}
