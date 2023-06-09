/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:23:08 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/08 12:48:09 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *get_path(char **envp)
{
    int i;

    i = 0;
    while (envp && envp[i])
    {
        if (ft_strncmp("PATH=", envp[i], 5) == 0)
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
    if (access(argv, X_OK) == 0 && argv[0] == '/')
        return (argv);
    minipath = ft_split(path, ':');
    while (minipath[i])
    {
        tmp = minipath[i];
        minipath[i] = ft_strjoin(tmp, "/");
        // free(tmp);
        tmp = minipath[i];
        minipath[i] = ft_strjoin(tmp, argv);
        if (access(minipath[i], F_OK) == 0)
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
        // exit(0);
    }
    command = ft_split(g_data.ms->stack[0], ' ');
    tmp = command[0];
    command[0] = split_path(path, tmp);
    free(path);
    if (execve(command[0], command, g_data.env) == -1)
    {
        ft_putstrr_fd("minishell : command not found: ", 2);
        ft_putstrr_fd(*g_data.ms->stack, 2);
        ft_putchar_fd('\n', 2);
        g_data.exit_s = 127;
    }
}
