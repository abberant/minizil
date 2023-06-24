/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:47:05 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/24 17:43:13 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_spaces(char *str, int *i)
{
	while (str[*i] == SPACE || str[*i] == TAB)
		(*i)++;
}

int	metachar_check(char c)
{
	if (c != GREAT && c != LESS
		&& c != PIPE && c != SPACE && c != TAB)
		return (1);
	return (0);
}

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
