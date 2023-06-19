/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:23:08 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/19 04:29:21 by lsadiq           ###   ########.fr       */
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
void close_ends(int *ends, int fd_in)
{
	if (ends[1] > 2)
		close(ends[1]);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
}
// dup_ends(ends, fd_in);
int   fork_exec(int fd_in, int fd_out)
{
    // (void)fd_out;
    int fd[2];

    fd_in = STDIN_FILENO;
    // fd_out = STDOUT_FILENO;
    if (g_data.ms)
    {
        while(g_data.ms->next->cmd)
        {
		    pipe(fd);
		    if (fork() == 0)
		    {
		    	if (fd_in != 0)
		    		dup2(fd_in, 0);
		    	dup2(fd[1], 1);
                puts("llll");
		    	// if (fd[0] > 2)
		    	// 	close(fd[0]);
                exec_redir(fd_in, fd_out);
                if (!check_built_in(&g_data))
                    exec_command();
                exit(0);
            }
            else
                wait(0);
            g_data.ms->cmd = g_data.ms->next->cmd;
        }
		// if(fd[1] > 2)
		// 	close(fd[1]);
		// if(fd_in != 0)
		// 	close(fd_in);
    // }
    // while(g_data.ms->next->cmd)
    // {
    //     printf("%s\n", g_data.ms->next->cmd);
    //     g_data.ms->cmd = g_data.ms->next->cmd;
    }
    if(check_built_in(&g_data))
    {
        // printf("%d\n", fd_in);
        // if(fd_in != 0)
        // {
        //     puts("mok");
            // dup2(fd_out, 1);
        // }
        exec_redir(fd_in, fd_out);
        execute(&g_data);
    }
    return 0;
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
