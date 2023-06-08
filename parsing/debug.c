/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 01:48:10 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/07 16:58:56 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_struct()
{
	// int	i;
	t_shell tmp;

	tmp = g_data;
	// printf("%s\n", g_data.ms->stack[0]);
	while (tmp.ms)
	{
		// i = -1;
		// while (tmp.ms->stack[++i]){

		// 	printf("is here\n");
		// 	printf("Stack[%d] is : [%s]\n", i, tmp.ms->stack[i]);
		// }
		printf("\n");
		printf("Command is : [%s]\n", tmp.ms->cmd);
		printf("\n");
		printf("Separator is : [%d]\n", tmp.ms->sep);
		printf("\n");
		if (tmp.ms->rd)
		{
			printf(GREEN"Redirection found!\n"RESET);
			printf("\n");
			while (tmp.ms->rd)
			{
				printf("Type is : [%d]\n", tmp.ms->rd->type);
				printf("\n");
				printf("FD is : [%d]\n", tmp.ms->rd->fd);
				printf("\n");
				printf("File name is : [%s]\n", tmp.ms->rd->file);
				printf("\n");
				printf("---------------------------------------------\n");
				printf("\n");
				tmp.ms->rd = tmp.ms->rd->next;
			}
		}
		else
			printf(RED"No redirection found!\n"RESET);
		printf("_______________________________________________________________________\n");
		tmp.ms =tmp.ms->next;
	}
}