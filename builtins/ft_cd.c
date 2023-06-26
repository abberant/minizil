/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:19:27 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/26 14:18:22 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_pwd(void)
{
	int		i;
	char	*holder;
	char	*pwd;
	char	*cwd;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	pwd = ft_strdup("PWD=");
	while (g_data.env && g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], "PWD=", 4))
		{
			holder = g_data.env[i];
			g_data.env[i] = ft_strjoin(pwd, cwd);
			free(cwd);
			free(holder);
			return ;
		}
		i++;
	}
	free(cwd);
}

void	reset_oldpwd(void)
{
	int		i;
	char	*holder;
	char	*cwd;
	char	*old_pwd;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	old_pwd = ft_strdup("OLDPWD=");
	while (g_data.env && g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], "OLDPWD=", 6))
		{
			holder = g_data.env[i];
			g_data.env[i] = ft_strjoin(old_pwd, cwd);
			free(cwd);
			free(holder);
			return ;
		}
		i++;
	}
	free(cwd);
}

void	ft_go_to_prv(void)
{
	reset_oldpwd();
	if (chdir("..") < 0)
	{
		perror("cd");
		exit(0);
	}
}

void	ft_go_to(char **str)
{
	if (!str[1] || !ft_strncmp(str[1], "~", 2))
	{
		reset_oldpwd();
		ft_go_home();
	}
	else if (!ft_strncmp(str[1], "-", 2))
		go_old_pwd();
	else if (!ft_strncmp(str[1], "..", 3))
		ft_go_to_prv();
	else
	{
		reset_oldpwd();
		if (chdir(str[1]) < 0)
		{
			perror("cd");
			g_data.exit_s = 1;
			return ;
		}
	}
	reset_pwd();
}

int	ft_cd(void)
{
	t_vdata	*tmp;

	tmp = g_data.ms;
	ft_go_to(tmp->stack);
	g_data.exit_s = 0;
	return (g_data.exit_s);
}
