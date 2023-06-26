/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:57:06 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/26 14:21:25 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(void)
{
	int		i;
	t_shell	*tmp;

	tmp = &g_data;
	i = -1;
	while (tmp->env[++i])
	{
		if (!ft_strchr(tmp->env[i], '='))
			continue ;
		ft_dprintf(1, "%s\n", tmp->env[i]);
	}
	g_data.exit_s = 0;
	return (g_data.exit_s);
}
