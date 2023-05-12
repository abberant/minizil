/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:34:45 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/12 05:25:55 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse(char **full, t_posay *tsr)
{
	t_vdata	*tmp;

	init_tree(full, tsr);
	init_redir(tsr);
	tmp = tsr->ms;
	while (tmp)
	{
		quote_expansion(tsr, tmp);
		tmp = tmp->next;
	}
}

int main(int argc, char **argv, char **env)
{
	char	*load;
	char 	**full;
	t_posay	tsr;

	// banner();
	(void) argc, (void) argv;
	ft_bzero(&tsr, sizeof(t_posay));
	tsr.env = env;
	int i;
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
		if (token_error(&tsr, full))
		{
			free(load);
			ft_free2d(full);
			continue ;
		}
		ft_parse(full, &tsr);
		// while (tsr.ms)
		// {
		// 	i = -1;
		// 	while (tsr.ms->stack[++i])
		// 		printf("---> [%s]\n", tsr.ms->stack[i]);
		// 	printf("______________________\n");
		// 	tsr.ms = tsr.ms->next;
		// }
		// while (tsr.ms)
		// {
		// 	while (tsr.ms->rd)
		// 	{
		// 		printf("FILE NAME [%s]\n", tsr.ms->rd->file);
		// 		tsr.ms->rd = tsr.ms->rd->next;
		// 	}
		// 	printf("____________________\n");
		// 	tsr.ms = tsr.ms->next;
		// }
	}
}