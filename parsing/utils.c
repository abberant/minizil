/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:47:05 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/24 23:31:07 by aanouari         ###   ########.fr       */
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

char	*delete_spaces(char *forum)
{
	int		i;
	char	*n_forum;
	char	**spc;

	i = 0;
	spc = ft_split(forum, ' ');
	n_forum = ft_strdup("");
	while(spc && spc[i])
	{
		if (i > 0)
			n_forum = s_concatinate(n_forum, ' ');
		n_forum = ft_strjoin(n_forum, spc[i]);
		i++;
	}
	free(forum);
	return (n_forum);
}