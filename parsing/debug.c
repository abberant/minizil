/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 01:48:10 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/15 02:32:59 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_struct()
{
	int	i;

	while (g_data.ms)
	{
		i = 0;
		while (g_data.ms->stack[i])
		{
			printf("Stack[%d] is : [%s]\n", i, g_data.ms->stack[i]);
			i++;
		}
		printf("\n");
		printf("Command is : [%s]\n", g_data.ms->cmd);
		printf("\n");
		printf("Separator is : [%d]\n", g_data.ms->sep);
		printf("\n");
		if (g_data.ms->rd)
		{
			printf("Redirection found!\n");
			printf("\n");
			while (g_data.ms->rd)
			{
				printf("Type is : [%d]\n", g_data.ms->rd->type);
				printf("\n");
				printf("FD is : [%d]\n", g_data.ms->rd->fd);
				printf("\n");
				printf("File name is : [%s]\n", g_data.ms->rd->file);
				printf("\n");
				printf("---------------------------------------------\n");
				printf("\n");
				g_data.ms->rd = g_data.ms->rd->next;
			}
		}
		else
			printf("No redirection found!\n");
		printf("_______________________________________________________________________\n");
		g_data.ms =g_data.ms->next;
	}
}