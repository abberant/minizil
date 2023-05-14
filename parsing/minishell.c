/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:34:45 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/13 17:16:51 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse(char **full, t_posay *data)
{
	t_vdata	*tmp;

	init_tree(full);
	init_redir();
	tmp = data->ms;
	while (tmp)
	{
		quote_expansion(tmp);
		tmp = tmp->next;
	}
}

int main(int argc, char **argv, char **env)
{
	char	*load;
	char 	**full;

	// banner();
	(void) argc, (void) argv;
	ft_bzero(&data, sizeof(t_posay));
	data.env = env;
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
		ft_parse(full, &data);
		// while (data.ms)
		// {
		// 	int i = -1;
		// 	while (data.ms->stack[++i])
		// 		printf("---> [%s]\n", data.ms->stack[i]);
		// 	printf("______________________\n");
		// 	data.ms = data.ms->next;
		// }
		// while (data.ms)
		// {
		// 	while (data.ms->rd)
		// 	{
		// 		printf("FILE NAME [%s]\n", data.ms->rd->file);
		// 		data.ms->rd = data.ms->rd->next;
		// 	}
		// 	printf("____________________\n");
		// 	data.ms = data.ms->next;
		// }
	}
}