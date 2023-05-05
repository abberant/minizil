 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:44:34 by aanouari          #+#    #+#             */
/*   Updated: 2023/04/24 13:28:35 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_managing(char **pivot, char *load, int *i)
{
	int	S_quote;
	int D_quote;

	S_quote = 0;
	D_quote = 0;
	*pivot = s_concatinate(*pivot, load[*i]);
	if (load[(*i)++] == SINGLE_QUOTE)
		S_quote++;
	else
		D_quote++;
	while (load[*i])
	{
		if (load[*i] == SINGLE_QUOTE)
			S_quote++;
		else if (load[*i] == DOUBLE_QUOTE)
			D_quote++;
		if (S_quote % 2 == 0 && D_quote % 2 == 0
			&& (!metachar_check(load[*i + 1]) || !load[(*i) + 1]))
			break ;
		*pivot = s_concatinate(*pivot, load[(*i)++]);
	}
	if (load[*i])
		*pivot = s_concatinate(*pivot, load[(*i)++]);
}

void	separator_managing(char **pivot, char *load, int *i)
{
	*pivot = s_concatinate(*pivot, load[*i]);
	if ((load[*i] != PIPE && load[(*i) + 1] != PIPE)
			&& (load[(*i) + 1] == load[*i]))
		*pivot = s_concatinate(*pivot, load[++(*i)]);
	(*i)++;
}

void	word_managing(char **pivot, char *load, int *i)
{
	while (load[*i])
	{
		*pivot = s_concatinate(*pivot, load[(*i)++]);
		if (load[*i] == SINGLE_QUOTE || load[*i] == DOUBLE_QUOTE)
			quotes_managing(pivot, load, i);
		if (!metachar_check(load[*i]))
			break ;
	}
}

char	**lexer(char *load)
{
	int		i;
	char	*pivot;
	char	**stack;

	i = 0;
	stack = NULL;
	while (load[i])
	{
		pivot = NULL;
		if (load[i] == SPACE || load[i] == TAB)
			skip_spaces(load, &i);
		else if (load[i] == SINGLE_QUOTE || load[i] == DOUBLE_QUOTE)
			quotes_managing(&pivot, load, &i);
		else if (load[i] == PIPE || load[i] == GREAT
			|| load[i] == LESS)
			separator_managing(&pivot, load, &i);
		else
			word_managing(&pivot, load, &i);
		if (pivot)
			stack = a_concatinate(stack , pivot);
	}
	return (stack);
}

