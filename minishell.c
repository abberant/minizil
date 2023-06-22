/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 00:51:14 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/22 15:49:53 by aanouari         ###   ########.fr       */
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

void	get_cmd_reset_stack()
{
	int		i;
	char	**ct;
	t_vdata	*data;

	i = 0;
	ct = NULL;
	data = g_data.ms;
	if (data)
	{
		if (ft_strchr(data->stack[0], 32))
		{
			data->cmd = ft_split(data->stack[0], 32)[0];
			ct = ft_split(data->stack[0], 32);
			while (data->stack[++i])
				ct = a_concatinate(ct, data->stack[i]);
			data->stack = ct;
		}
		else
			data->cmd = data->stack[0];
	}
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
		if (!tmp->stack)
			tmp = tmp->next;
		else
			get_cmd_reset_stack();
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	**full;
	char	*load;
	// t_redir *redi;
	int out = 1;
	int in = 0;

	// int i = 1;
	initialize_shell(argc, argv, env);
	while (1)
	{
		load = readline("[MiniShell💩]$ ");
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
		t_vdata *tmp = g_data.ms;
		debug_struct();
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
		fork_exec(in, out);
		ft_cleanse();
		ft_free2d(full);
		free (load);
	}
}