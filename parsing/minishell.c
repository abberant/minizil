/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:34:45 by aanouari          #+#    #+#             */
/*   Updated: 2023/04/30 14:10:49 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "minishell.h"

int main(void)
{
	char	*load;
	// t_token	*tokens;
	char **posi;

	// tokens = NULL;
	banner();
	while (1)
	{
		load = readline(RED "dkhol 3lia$ " RESET);
		if (!load)
			exit(EXIT_FAILURE);
		if (ft_strlen(load) != 0)
			add_history(load);
		posi = lexer(load);
		init_tree(posi);
		// casting(&tokens);
		// while (tokens)
		// {
		// 	printf("STATUS--> %d\nTYPE--> %d\n", tokens->status, tokens->type);
		// 	printf("CONTENT--> %s\n", tokens->content);
		// 	printf("________________________________________________\n");
		// 	tokens = tokens->next;
		// }
	}
}