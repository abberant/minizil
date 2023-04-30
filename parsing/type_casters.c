/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_casters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:05:50 by aanouari          #+#    #+#             */
/*   Updated: 2023/04/30 11:25:30 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_cast(char *stack)
{
	if (stack[0] == SINGLE_QUOTE
		&& stack[ft_strlen(stack) - 1] == SINGLE_QUOTE)
		return (BETWIXT_SQ);
	else if (stack[0] == DOUBLE_QUOTE
		&& stack[ft_strlen(stack) - 1] == DOUBLE_QUOTE)
		return (BETWIXT_DQ);
	else
		return (DEFAULTED);
}

