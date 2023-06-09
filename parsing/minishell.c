/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:34:45 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/09 01:38:01 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	initialize_shell(int argc, char **argv, char **env)
{
	(void) argc, (void) argv;
	// banner();
	ft_bzero(&g_data, sizeof(t_shell));
	g_data.env = env;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
}

void	ft_parse(char **full)
{
	t_vdata	*tmp;

	init_tree(full);
	init_redir();
	tmp = g_data.ms;
	while (tmp)
	{
		quote_expansion(tmp);
		tmp->cmd = tmp->stack[0];
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	**full;
	char	*load;
	// int outfile;

	// int i = 1;
	initialize_shell(argc, argv, env);
	while (1)
	{
		load = readline(RED "dkhol 3lia$ " RESET);
		if (!load)
			exit(EXIT_FAILURE);
		if (ft_strlen(load))
			add_history(load);
		full = lexer(load);
		// i = -1;
		// while (full[++i])
		// 	printf("Lexer[%d] is : [%s]\n", i, full[i]);
		if (token_error(full))
		{
			free(load);
			ft_free2d(full);
			continue ;
		}
		ft_parse(full);
		// debug_struct();
		execute(&g_data);
		g_data.ms = NULL;
		// exec_command();
		// here_doc(g_data.ms->stack[1]);
		// heredoc_six(g_data.ms->stack, g_data.env);
		// ft_cleanse();
	}
}
