/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:51:27 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/26 20:45:16 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_look(char **stack)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	g_data.flag = 1;
	while (stack[i])
	{
		if (stack[i][0] != '-' || stack[i][1] != 'n')
			return (i);
		j = 0;
		while (stack[i][j])
		{
			if (stack[i][0] == '-' && j == 0)
				j++;
			if (stack[i][j] != 'n')
				return (i);
			j++;
		}
		g_data.flag = 0;
		i++;
	}
	return (-1);
}

int	ft_echo(void)
{
	t_vdata	*tmp;
	int		i;

	g_data.exit_s = 0;
	tmp = g_data.ms;
	i = ft_look(tmp->stack);
	if (i == -1)
	{
		printf("\n");
		return (0);
	}
	if (i == 0)
		return (0);
	while (tmp->stack[i])
	{
		printf("%s", tmp->stack[i]);
		i++;
		if (tmp->stack[i])
			printf(" ");
	}
	if (g_data.flag)
		printf("\n");
	return (0);
}
