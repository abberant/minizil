/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:19:27 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/06 16:09:42 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_go_home()
{
	if(chdir(getenv("HOME")) < 0)
    {
        perror("cd");
        return 1;
    }
    return 0;
}

int go_old_pwd()
{
	if(chdir(getenv("OLDPWD")) < 0)
	{
		perror("cd");
        return (1);
    }
    return 0;
}

void    reset_pwd(t_shell *shell)
{
    t_shell *tmp = shell;
     char *cwd = getcwd(NULL, 0);
     
    if(!cwd)
            return ;
    int i = 0;
    while(tmp->env[i])
    {
        if(!ft_strncmp(tmp->env[i], "PWD=", 4))
        {
            tmp->env[i] = ft_strjoin("PWD=", cwd);
            printf("PWD = %s\n", cwd);
            return ;
        }
        i++;
    }
    free(cwd);
}

void	reset_oldpwd(t_shell *shell)
{
	int i = 0;
	t_shell *tmp = shell;
	char *cwd = getcwd(NULL, 0);

    if(!cwd)
        return ;
	while(tmp->env[i])
	{
        if (!ft_strncmp(tmp->env[i], "OLDPWD=", 6))
        {
			tmp->env[i] = ft_strjoin("OLDPWD=", cwd);
            printf("OLDPWD = %s\n", cwd);
			return ;
		}
		i++;
	}
    free(cwd);
}

void    ft_go_to(char **str)
{
    if(!str[1] || !ft_strncmp(str[1], "~", 1))
    {
        reset_oldpwd(&g_data);
        ft_go_home();
        reset_pwd(&g_data);
    }
    else if(!ft_strncmp(str[1], "-", 1))
    {
        reset_oldpwd(&g_data);
        go_old_pwd();
        reset_pwd(&g_data);
    }
	else if(!ft_strncmp(str[1], "..", 1))
	{
        reset_oldpwd(&g_data);
        if(chdir("..") < 0)
        {
            perror("cd");
            exit(2);
        }
	    reset_pwd(&g_data);
	}
    else
    {
        reset_oldpwd(&g_data);
        if(chdir(str[1]) < 0)
        {
            perror("cd");
            g_data.exit_s = 1;
            return ;
        }
        reset_pwd(&g_data);
    }
}

void    ft_cd(t_shell *shell)
{
    char *cwd;
	t_shell *tmp = shell;

    cwd = getcwd(NULL, 0);
    ft_go_to(tmp->ms->stack);
    free(cwd);
}