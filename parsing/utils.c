/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:47:05 by aanouari          #+#    #+#             */
/*   Updated: 2023/04/27 14:47:05 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	reset_pivot(char *pivot)
{
	free(pivot);
	pivot = NULL;
}