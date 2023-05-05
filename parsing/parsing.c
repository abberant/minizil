/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:38:12 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/05 01:38:09 by aanouari         ###   ########.fr       */
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

void	init_tree(char **stack, t_vdata **ms)
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
		vdata_addback(ms, vdata_new(buffer, get_separator(stack, i)));
		if (stack[i])
			i++;
	}
}
