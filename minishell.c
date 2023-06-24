/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 00:51:14 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/24 23:51:04 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_shell(int argc, char **argv, char **env)
{
	(void) argc, (void) argv;
	// banner();
	ft_bzero(&g_data, sizeof(t_shell));
	g_data.env = clone_env(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
}

int	main(int argc, char **argv, char **env)
{
	char	**full;
	char	*load;
	int out = 1;
	int in = 0;

	initialize_shell(argc, argv, env);
	while (1)
	{
		load = readline("minishell$ ");
		if (!load)
			exit(EXIT_FAILURE);
		if (ft_strlen(load))
			add_history(load);
		full = lexer(load);
		if	(ft_parse(full, load))
			continue ;
		t_vdata *tmp = g_data.ms;
		t_redir *new;
		while(tmp)
		{
			new = tmp->rd;
			while(new)
			{
				if(new->type == HEREDOC)
					new->fd = open_here_doc(new->file, in);
				new = new->next;
			}
			tmp = tmp->next;
		}
		if (g_data.ms)
			fork_exec(in, out);
		ft_cleanse();
		ft_free2d(full);
		free (load);
	}
}