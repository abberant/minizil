/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 01:48:10 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/22 14:19:58 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	debug_struct()
{
	int	i;
	t_vdata *tmp;
	t_redir *new;

	tmp = g_data.ms;
	while (tmp)
	{
		if (!tmp->stack)
			printf("Stack is empty\n");
		else
		{
			i = 0;
			while (tmp->stack[i])
			{
				printf("Stack[%d] is : [%s]\n", i, tmp->stack[i]);
				i++;
			}
		}
		printf("\n");
		printf("Command is : [%s]\n", tmp->cmd);
		printf("\n");
		printf("Separator is : [%d]\n", tmp->sep);
		printf("\n");
		new = tmp->rd;
		if (new)
		{
			printf(GREEN"Redirection found!\n"RESET);
			printf("\n");
			while (new)
			{
				printf("Type is : [%d]\n", new->type);
				printf("\n");
				printf("FD is : [%d]\n", new->fd);
				printf("\n");
				printf("File name is : [%s]\n", new->file);
				printf("\n");
				if (new->error)
					printf("Error : [Ambiguous]\n"); 
				printf("---------------------------------------------\n");
				printf("\n");
				new = new->next;
			}
		}
		else
			printf(RED"No redirection found!\n"RESET);
		printf("_______________________________________________________________________\n");
		tmp =tmp->next;
	}
}
