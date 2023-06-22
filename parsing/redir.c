/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:20:27 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/22 23:43:21 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	set_redir_ll(t_vdata *tmp, char ***buffer)
{
	t_redir	*rd;
	int		i;

	i = 0;
	while (tmp->stack[i])
	{
		if (arrow_check(tmp->stack[i]) != -1)
		{
			rd = redir_new(tmp->stack[i + 1], arrow_check(tmp->stack[i]));
			redir_addback(&tmp->rd, rd);
			i++;
		}
		else
			*buffer = a_concatinate(*buffer, tmp->stack[i]);
		if (!tmp->stack[i])
			return ;
		i++;
	}
}
void	file_expansion(t_vdata *ms)
{
	t_redir	*v_base;

	v_base = ms->rd;
	while (v_base)
	{
		if (v_base->type != HEREDOC)
		{
			v_base->file = expand(v_base->file, 1);
			if (ft_strchr(v_base->file, '\'') || ft_strchr(v_base->file, '"'))
				v_base->file = cancel_quotes(v_base->file);
		}
		if (!ft_strcmp(v_base->file, ""))
			v_base->error = 1;
		v_base = v_base->next;
	}
}

void	init_redir(void)
{
	t_vdata	*tmp;
	char	**wc;

	tmp = g_data.ms;
	while (tmp)
	{
		wc = NULL;
		if (redir_check(tmp->stack))
		{
			set_redir_ll(tmp, &wc);
			ft_free2d(tmp->stack);
			tmp->stack = wc;
		}
		else
			tmp->rd = NULL;
		file_expansion(tmp);
		tmp = tmp->next;
	}
}
