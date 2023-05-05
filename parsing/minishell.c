/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:34:45 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/05 21:07:29 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*load;
	char 	**full;
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
		full = lexer(load);
		if (token_error(full))
		{
			free(load);
			ft_free2d(full);
			continue ;
		}
		init_tree(full, &ms);
		init_redir(&ms);
	}
}