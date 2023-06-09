/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:38:12 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/10 00:28:31 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_separator(char **stack, int i)
{
	int	separator;

	separator = -1;
	if (!stack[i])
		separator = 0;
	else if (!ft_strcmp(stack[i], "|"))
		separator = PIPE;
	return (separator);
}

void	init_tree(char **stack)
{
	char	**buffer;
	int		i;
	t_vdata	*node;

	i = 0;
	g_data.ms = NULL;
	while (stack[i])
	{
		buffer = NULL;
		if (!(ft_strcmp(stack[i], "|")))
			buffer = a_concatinate(buffer, "");
		while (stack[i] && (ft_strcmp(stack[i], "|")))
			buffer = a_concatinate(buffer, stack[i++]);
		node = vdata_new(buffer, get_separator(stack, i));
		vdata_addback(&g_data.ms, node);
		if (stack[i])
			i++;
	}
}
