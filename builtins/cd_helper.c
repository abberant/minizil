/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:12:42 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/26 14:15:20 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_c_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_my_env(t_shell shell, char *str)
{
	int	i;

	i = 0;
	while (shell.env[i])
	{
		if (!ft_strncmp(str, shell.env[i], get_c_index(shell.env[i], '=')))
			return (shell.env[i] + get_c_index(shell.env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

int	ft_go_home(void)
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
			return (1);
		}
	}
	else
		ft_dprintf(2, "Minishell : cd : HOME not set\n");
	return (0);
}

int	go_old_pwd(void)
{
	t_shell	tmp;
	char	*holder;

	tmp = g_data;
	holder = get_my_env(tmp, "OLDPWD");
	if (holder)
	{
		if (chdir(holder) < 0)
		{
			perror("cd");
			return (1);
		}
		return (0);
	}
	ft_dprintf(2, "Minishell : cd : OLDPWD not set\n");
	return (0);
}
