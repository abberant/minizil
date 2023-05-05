/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 01:49:28 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/05 02:28:45 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	quote_error(char *stack)
{
	char	quote;
	int		i;

	i = 0;
	while (stack[i])
	{
		if (stack[i] == DOUBLE_QUOTE || stack[i] == SINGLE_QUOTE)
		{
			quote = stack[i++];
			while (stack[i] && stack[i] != quote)
				i++;
			if (!stack[i])
			{
				ft_putstr_fd(UNCLOSED_QUOTE, 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	separator_error(char **stack, int i)
{
	if (!ft_strcmp(stack[i], "|"))
	{
		if (!stack[i + 1] || !ft_strcmp(stack[i + 1], "|"))
		{
			if (!stack[i + 1])
				dprintf(2, UNEXPECTED_TOKEN, stack[i]);
			else
				dprintf(2, UNEXPECTED_TOKEN, stack[i + 1]);
			return (1);
		}
	}
	return (0);
}

int	invalid_separator(char **stack, int i)
{
	if (!ft_strcmp(stack[0], "|") && ft_strcmp(stack[1], "|"))
	{
		dprintf(2, UNEXPECTED_TOKEN, stack[i]);
		return (1);
	}
	else if (!ft_strcmp(stack[0], "|") && !ft_strcmp(stack[1], "|"))
	{
		dprintf(2, UNEXPECTED_TOKEN_2);
		return (1);
	}
	return (0);
}

int	redirection_error(char **stack, int i)
{
	if (arrow_check(stack[i]) != -1)
	{
		if (!stack[i + 1])
		{
			dprintf(2, UNEXPECTED_TOKEN, "newline");
			return (1);
		}
		else if (arrow_check(stack[i + 1]) != -1 || !ft_strcmp(stack[i + 1], "|"))
		{
			dprintf(2, UNEXPECTED_TOKEN, stack[i + 1]);
			return (1);
		}
	}
	return (0);
}


int	token_error(char **stack)
{
	int	i;

	i = 0;
	while (stack && stack[i])
	{
		if (quote_error(stack[i]))
			return (1);
		else if (separator_error(stack, i))
			return (1);
		else if (invalid_separator(stack, i))
			return (1);
		else if (redirection_error(stack, i))
			return (1);
		i++;
	}
	return (0);
}