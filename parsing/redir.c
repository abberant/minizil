/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:20:27 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/05 02:15:40 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arrow_check(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (REDIR_IN);
	else if (!ft_strcmp(str, ">"))
		return (REDIR_OUT);
	else if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	else if (!ft_strcmp(str, ">>"))
		return (APPEND);
	return (-1);
}

int	redir_check(char **stack)
{
	int	i;

	i = 0;
	while (stack && stack[i])
	{
		if (arrow_check(stack[i]) != -1)
			return (1);
		i++;
	}
	return (0);
}

void	set_redir_ll(t_vdata *tmp, char **buffer)
{
	int	i;

	i = 0;
	while (tmp->stack[i])
	{
		if (arrow_check(tmp->stack[i]) != -1)
		{
			redir_addback(&tmp->rd, redir_new(tmp->stack[i + 1],
				arrow_check(tmp->stack[i])));
			i++;
		}
		else
			buffer = a_concatinate(buffer, tmp->stack[i]);
		i++;
	}
}

void	init_redir(t_vdata **ms)
{
	t_vdata	*tmp;
	char	**wc;

	tmp = *ms;
	while (tmp)
	{
		wc = NULL;
		if (redir_check(tmp->stack))
		{
			set_redir_ll(tmp, wc);
			ft_free2d(tmp->stack);
			tmp->stack = wc;
		}
		else
			tmp->rd = NULL;
		tmp = tmp->next;
	}	
}