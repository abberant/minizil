/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:17:46 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/25 00:27:54 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int    ft_strcmp_case_safe(char *str, char *str2)
{
    int i;

    i = 0;
    while ((str[i] || str2[i]))
    {
        if (ft_tolower(str[i]) != ft_tolower(str2[i]))
			return (str[i] - str2[i]);
        i++;
    }
    return (0);
}

int	execute()
{
	t_vdata	*temp;

	temp = g_data.ms;
	while (temp && temp->cmd)
	{
		if (!ft_strcmp_case_safe(temp->cmd, "pwd"))
			return (ft_pwd());
		if (!ft_strcmp_case_safe(temp->cmd, "echo"))
			return (ft_echo());
		if (!ft_strcmp_case_safe(temp->cmd, "env"))
			return (ft_env());
		if (!ft_strcmp(temp->cmd, "cd"))
			return (ft_cd());
		if (!ft_strcmp(temp->cmd, "export"))
			return (ft_export());
		if (!ft_strcmp(temp->cmd, "unset"))
			return (ft_unset(0, -1, NULL));
		if (!ft_strcmp(temp->cmd, "exit"))
			return (ft_exit());
		temp = temp->next;
	}
	return (0);
}

int	check_built_in()
{
	t_vdata	*temp;

	temp = g_data.ms;
	while (temp && temp->cmd)
	{
		if (!ft_strcmp_case_safe(temp->cmd, "pwd"))
			return (1);
		if (!ft_strcmp_case_safe(temp->cmd, "echo"))
			return (1);
		if (!ft_strcmp_case_safe(temp->cmd, "env"))
			return (1);
		if (!ft_strcmp(temp->cmd, "cd"))
			return (1);
		if (!ft_strcmp(temp->cmd, "export"))
			return (1);
		if (!ft_strcmp(temp->cmd, "unset"))
			return (1);
		if (!ft_strcmp(temp->cmd, "exit"))
			return (1);
		temp = temp->next;
	}
	return (0);
}
