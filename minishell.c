/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 00:51:14 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/26 21:58:15 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_shell(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	// banner();
	ft_bzero(&g_data, sizeof(t_shell));
	g_data.env = clone_env(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
}

void	ft_exec(int in, int out)
{
	int		efd;
	t_vdata	*tmp;
	t_redir	*new;

	efd = 0;
	tmp = g_data.ms;
	while (tmp && !efd)
	{
		new = tmp->rd;
		while (new && !efd)
		{
			if (new->type == HEREDOC)
			{
				new->fd = open_here_doc(new->file, -1, 0, NULL);
				if (new->fd == -1)
					efd = 1;
			}
			new = new->next;
		}
		tmp = tmp->next;
	}
	if (efd)
		g_data.exit_s = 1;
	else
		fork_exec(in, out);
}

int	main(int argc, char **argv, char **env)
{
	char	**full;
	char	*load;
	int		out;
	int		in;

	out = 1;
	in = 0;
	initialize_shell(argc, argv, env);
	while (1)
	{
		load = readline("minishell$ ");
		if (!load)
			exit(EXIT_FAILURE);
		if (ft_strlen(load))
			add_history(load);
		full = lexer(load);
		if (ft_parse(full, load))
			continue ;
		ft_exec(in, out);
		ft_cleanse();
		ft_free2d(full);
		free (load);
	}
}
