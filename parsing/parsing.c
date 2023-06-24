/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:38:12 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/24 18:06:12 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_tree(char **stack)
{
	char	**buffer;
	int		i;

	i = 0;
	while (stack && stack[i])
	{
		buffer = NULL;
		if (!(ft_strcmp(stack[i], "|")))
			buffer = a_concatinate(buffer, "");
		while (stack[i] && (ft_strcmp(stack[i], "|")))
			buffer = a_concatinate(buffer, stack[i++]);
		vdata_addback(&g_data.ms, vdata_new(buffer, get_separator(stack, i)));
		if (stack[i])
			i++;
	}
}

void	get_cmd_reset_stack()
{
	int		i;
	char	**ct;
	t_vdata	*data;

	i = 0;
	ct = NULL;
	data = g_data.ms;
	while (data)
	{
		if (!data->stack)
		{
			data = data->next;
			continue ;
		}
		else if (ft_strchr(data->stack[0], 32))
		{
			data->cmd = ft_split(data->stack[0], 32)[0];
			ct = ft_split(data->stack[0], 32);
			while (data->stack[++i])
				ct = a_concatinate(ct, data->stack[i]);
			data->stack = ct;
		}
		else
			data->cmd = data->stack[0];
		data = data->next;
	}
}

int	ft_parse(char **full, char *load)
{
	t_vdata	*tmp;

	if (token_error(full))
	{
		free(load);
		ft_free2d(full);
		return (1);
	}
	init_tree(full);
	init_redir();
	tmp = g_data.ms;
	while (tmp)
	{
		quote_expansion(tmp);
		tmp = tmp->next;
	}
	get_cmd_reset_stack();
	return (0);
}
