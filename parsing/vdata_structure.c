/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vdata_structure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:27:01 by aanouari          #+#    #+#             */
/*   Updated: 2023/04/30 11:29:00 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vdata	*vdata_new(char **stack, int separator)
{
	t_vdata	*tab;

	tab = (t_vdata *) ft_calloc(1, sizeof(t_vdata));
	tab->stack = stack;
	tab->cmd = NULL;
	tab->sep = separator;
	tab->error = 0;
	tab->head = NULL;
	tab->previous = NULL; 
	tab->next = NULL;
	return (tab);
}

int	clear_vdatas(t_vdata **vdata)
{
	t_vdata	*current;
	t_vdata	*next;

	if (!vdata)
		return (1);
	current = (*vdata);
	next = (*vdata);
	while (current)
	{
		next = next->next;
		free(current);
		current = next;
	}
	*vdata = NULL;
	return (1);
}

void	vdata_addback(t_vdata **vdata, t_vdata *_new)
{
	t_vdata	*current;

	if (!vdata || !_new)
		return ;
	current = (*vdata);
	if (!current)
	{
		*vdata = _new;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = _new;
}

void	vdata_addfront(t_vdata **vdata, t_vdata *_new)
{
	if (!_new)
		return ;
	if (!vdata)
	{
		*vdata = _new;
		return ;
	}
	_new->next = (*vdata);
	(*vdata) = _new;
}