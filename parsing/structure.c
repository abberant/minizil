/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:27:01 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/12 00:32:02 by aanouari         ###   ########.fr       */
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
	tab->rd = NULL;
	tab->previous = NULL; 
	tab->next = NULL;
	return (tab);
}

t_vdata	*v_last(t_vdata *lst)
{
	if (!lst  || !lst->next)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	vdata_addback(t_vdata **vdata, t_vdata *_new)
{
	t_vdata	*tmp;

	if (!vdata || !_new)
		return ;
	tmp = *vdata;
	if (*vdata)
	{
		tmp = v_last(tmp);
		if (tmp)
		{
			tmp->next = _new;
			_new->previous = tmp;
		}
	}
	else
		*vdata = _new;
	free(tmp);
}

t_redir	*redir_new(char *file, int type)
{
	t_redir	*tab;

	tab = (t_redir *) ft_calloc(1, sizeof(t_redir));
	tab->file = ft_strdup(file);
	tab->fd = -1;
	tab->type = type;
	tab->next = NULL;
	tab->previous = NULL;
	return (tab);
}

void	redir_addback(t_redir **redir, t_redir *_new)
{
	t_redir	*current;

	if (!redir || !_new)
		return ;
	current = (*redir);
	if (!current)
	{
		*redir = _new;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = _new;
}
