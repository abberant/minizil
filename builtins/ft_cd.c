/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:19:27 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/24 14:46:11 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char	*holder;

	tmp = g_data;
	holder = get_my_env(tmp, "HOME");
	if (holder)
	{
		if (chdir(holder) < 0)
		{
			free(holder);
			perror("cd");
			return 1;
		}
	}
	else
		ft_dprintf(2, "Minishell : cd : HOME not set\n");
	return 0;
}

int go_old_pwd()
{
	t_shell tmp;
	char	*holder;

	tmp = g_data;
	holder = get_my_env(tmp, "OLDPWD");
	if(holder)
	{
		if (chdir(holder) < 0)
		{
			perror("cd");
			return (1);
		}
		return 0;
	}
	ft_dprintf(2, "Minishell : cd : OLDPWD not set\n");
	return 0;
}

void reset_pwd()
{
	int		i;
	char	*holder;
	char	*pwd;
	char	*cwd;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return;
	pwd = ft_strdup("PWD=");
	while (g_data.env && g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], "PWD=", 4))
		{
			holder = g_data.env[i];
			g_data.env[i] = ft_strjoin(pwd, cwd);
			free(cwd);
			free(holder);
			return;
		}
		i++;
	}
	free(cwd);
}

void reset_oldpwd()
{
	int		i;
	char	*holder;
	char	*cwd;
	char	*old_pwd;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return;
	old_pwd = ft_strdup("OLDPWD=");
	while (g_data.env && g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], "OLDPWD=", 6))
		{
			holder = g_data.env[i];
			g_data.env[i] = ft_strjoin(old_pwd, cwd);
			free(cwd);
			free(holder);
			return;
		}
		i++;
	}
	free(cwd);
}
void	ft_go_to_prv()
{
	reset_oldpwd();
	if (chdir("..") < 0)
	{
		perror("cd");
		exit(2);
	}
}
void	ft_go_to(char **str)
{
	if (!str[1] || !ft_strncmp(str[1], "~", 1))
	{
		reset_oldpwd();
		ft_go_home();
	}
	else if (!ft_strncmp(str[1], "-", 1))
		go_old_pwd();
	else if (!ft_strncmp(str[1], "..", 1))
		ft_go_to_prv();
	else
	{
		reset_oldpwd();
		if (chdir(str[1]) < 0)
		{
			perror("cd");
			g_data.exit_s = 1;
			return;
		}
	}
	reset_pwd();
}

int ft_cd()
{
	t_vdata *tmp;

	tmp = g_data.ms;
	ft_go_to(tmp->stack);
	g_data.exit_s = 0;
	return (g_data.exit_s);
}