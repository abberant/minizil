/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:47:54 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/23 13:57:48 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_sig(int signal)
{
	if (signal == SIGINT)
	{
		g_data.exit_s = 1;
		exit(EXIT_FAILURE);
	}
}

int open_here_doc(char *file, int fd)
{
	char	*line;
	char	*q_file;

	fd = -1;
	if (fd != -1)
		close(fd);
	int end[2];
	pipe(end);
	if (fork() == 0)
	{
		q_file = cancel_quotes(file, 0);
		close(end[0]);
		fd = end[1];
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, heredoc_sig);
		while (1)
		{
			line = readline(YELLOW " >" RESET);
			if (!line || ft_strcmp(q_file, line) == 0)
			{
				if (line)
					free(line);
				break;
			}
			else if (ft_strlen(line) > 0)
			{
				if (!ft_strchr(file, '\"') && !ft_strchr(file, '\''))
					line = expand(line, 0);
				ft_dprintf(fd, line);
				ft_dprintf(fd, "\n");
			}
			free(line);
		}
		free(q_file);
		close(fd);
		exit(0);
	}
	else
		wait(0);
	close (end[1]);
	fd = end[0];
	return (fd);
}
