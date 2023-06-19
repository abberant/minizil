/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:19:27 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/19 02:56:55 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_c_index(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char *get_my_env(t_shell shell, char *str)
{
	int i;

	i = 0;
	while (shell.env[i])
	{
		if (!ft_strncmp(str, shell.env[i], get_c_index(shell.env[i], '=')))
			return (shell.env[i] + get_c_index(shell.env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

int ft_go_home()
{
	t_shell	tmp;
	int		i;

	i = 0;
	tmp = g_data;
	if (get_my_env(tmp, "HOME"))
	{
		if (chdir(get_my_env(tmp, "HOME")) < 0)
		{
			perror("cd");
			return 1;
		}
	}
	else
	{
		ft_dprintf(2, "Minishell : cd : HOME not set\n");
		return 0;
	}

	return 0;
}

int go_old_pwd()
{
	t_shell tmp;
	int i;

	i = 0;
	tmp = g_data;
	// printf("%s\n", get_my_env(tmp, "OLDPWD"));
	if(get_my_env(tmp, "OLDPWD"))
	{
		if (chdir(get_my_env(tmp, "OLDPWD")) < 0)
		{
			perror("cd");
			return (1);
		}
		return 0;
	}
	else
	{
		ft_dprintf(2, "Minishell : cd : OLDPWD not set\n");
		return 0;
	}
}

void reset_pwd(t_shell *shell)
{
	t_shell *tmp = shell;
	char *cwd = getcwd(NULL, 0);

	if (!cwd)
		return;
	int i = 0;
	while (tmp->env && tmp->env[i])
	{
		if (!ft_strncmp(tmp->env[i], "PWD=", 4))
		{
			tmp->env[i] = ft_strjoin("PWD=", cwd);
			// printf("PWD = %s\n", cwd);
			return;
		}
		i++;
	}
	free(cwd);
}

void reset_oldpwd(t_shell *shell)
{
	int i = 0;
	t_shell *tmp = shell;
	char *cwd = getcwd(NULL, 0);

	if (!cwd)
		return;
	while (tmp->env && tmp->env[i])
	{
		if (!ft_strncmp(tmp->env[i], "OLDPWD=", 6))
		{
			tmp->env[i] = ft_strjoin("OLDPWD=", cwd);
			// printf("PLDPWD = %s\n", cwd);
			return;
		}
		i++;
	}
	free(cwd);
}

void	ft_go_to(char **str)
{
	if (!str[1] || !ft_strncmp(str[1], "~", 1))
	{
		reset_oldpwd(&g_data);
		ft_go_home();
		reset_pwd(&g_data);
	}
	else if (!ft_strncmp(str[1], "-", 1))
	{
		go_old_pwd();
		reset_pwd(&g_data);
	}
	else if (!ft_strncmp(str[1], "..", 1))
	{
		reset_oldpwd(&g_data);
		if (chdir("..") < 0)
		{
			perror("cd");
			exit(2);
		}
		reset_pwd(&g_data);
	}
	else
	{
		reset_oldpwd(&g_data);
		if (chdir(str[1]) < 0)
		{
			perror("cd");
			g_data.exit_s = 1;
			return;
		}
		reset_pwd(&g_data);
	}
}

int ft_cd(t_shell *shell)
{
	char *cwd;
	t_shell *tmp = shell;

	cwd = getcwd(NULL, 0);
	ft_go_to(tmp->ms->stack);
	free(cwd);
	g_data.exit_s = 0;
	return (g_data.exit_s);
}