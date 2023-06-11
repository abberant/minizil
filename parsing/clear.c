/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:22:18 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/11 21:34:00 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clear_lists(void)
{
	t_vdata	*tmp;
	t_redir	*tmp2;

	while (g_data.ms)
	{
		tmp = g_data.ms;
		while (tmp->rd)
		{
			tmp2 = tmp->rd;
			tmp->rd = tmp->rd->next;
			free(tmp2);
			tmp2 = NULL;
		}
		g_data.ms = g_data.ms->next;
		free(tmp);
		tmp = NULL;
	}
}

void	ft_cleanse(void)
{
	t_vdata	*tmp;
	t_redir	*tmp2;

	tmp = g_data.ms;
	while (tmp)
	{
		tmp2 = tmp->rd;
		while (tmp2)
		{
			free(tmp2->file);
			tmp2 = tmp2->next;
		}
		free(tmp->cmd);
		if (tmp->stack)
			ft_free2d(tmp->stack);
		tmp = tmp->next;
	}
	clear_lists();
}
