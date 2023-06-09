/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 01:48:10 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/10 00:52:39 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_struct()
{
	int	i;
	t_shell *tmp;

	tmp = &g_data;
	while (tmp->ms)
	{
		i = -1;
		if (!tmp->ms->stack)
			printf("Stack is empty\n");
		else
			while (tmp->ms->stack[++i])
				printf("Stack[%d] is : [%s]\n", i, tmp->ms->stack[i]);
		printf("\n");
		printf("Command is : [%s]\n", tmp->ms->cmd);
		printf("\n");
		printf("Separator is : [%d]\n", tmp->ms->sep);
		printf("\n");
		if (tmp->ms->rd)
		{
			printf(GREEN"Redirection found!\n"RESET);
			printf("\n");
			while (tmp->ms->rd)
			{
				printf("Type is : [%d]\n", tmp->ms->rd->type);
				printf("\n");
				printf("FD is : [%d]\n", tmp->ms->rd->fd);
				printf("\n");
				printf("File name is : [%s]\n", tmp->ms->rd->file);
				printf("\n");
				printf("---------------------------------------------\n");
				printf("\n");
				tmp->ms->rd = tmp->ms->rd->next;
			}
		}
		else
			printf(RED"No redirection found!\n"RESET);
		printf("_______________________________________________________________________\n");
		tmp->ms =tmp->ms->next;
	}
}