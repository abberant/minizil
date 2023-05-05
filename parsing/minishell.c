/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:34:45 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/05 02:31:58 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "minishell.h"

int main(void)
{
	char	*load;
	char 	**posi;
	t_vdata	*ms;

	banner();
	ms = NULL;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		load = readline(RED "dkhol 3lia$ " RESET);
		if (!load)
			exit(EXIT_FAILURE);
		if (ft_strlen(load) != 0)
			add_history(load);
		posi = lexer(load);
		if (token_error(posi))
		{
			free(load);
			ft_free2d(posi);
			continue ;
		}
		init_tree(posi, &ms);
		init_redir(&ms);
	}
}