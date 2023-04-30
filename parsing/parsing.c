/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:38:12 by aanouari          #+#    #+#             */
/*   Updated: 2023/04/30 14:12:23 by aanouari         ###   ########.fr       */
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
	t_vdata	*cast;
	char	**buffer;
	int		i;
	int d;

	cast = NULL;
	i = 0;
	while (stack && stack[i])
	{
		d = -1;
		buffer = NULL;
		while (stack[i] && (ft_strcmp(stack[i], "|")))
			buffer = a_concatinate(buffer, stack[i++]);
		while (buffer[++d])
			printf("--> [%s]\n", buffer[d]);
		printf("____________________________\n");
		vdata_addback(&cast, vdata_new(buffer, get_separator(stack, i)));
		if (stack[i])
			i++;
	}
}

// void	init_redir()
// {
	
// }

// void	casting(t_token **shaft)
// {
// 	t_token	*cast;

// 	cast = *shaft;
// 	while (cast)
// 	{
// 		cast->status = d_quote_cast(cast->content);
// 		cast->type = set_type(cast->status, cast->content);
// 		cast = cast->next;
// 	}
// }
