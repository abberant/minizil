/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:47:54 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/22 23:45:15 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int open_here_doc(char *file, int fd)
{
	char	*line;
	fd = -1;

	if (fd != -1)
		close(fd);
	int end[2];
	pipe(end);
	if (fork() == 0)
	{
		close(end[0]);
		fd = end[1];
		while (1)
		{
			signal(SIGINT, sig_handler);
			signal(SIGQUIT, SIG_IGN);
			line = readline(YELLOW " >" RESET);
			if (!line || ft_strcmp(file, line) == 0)
			{
				if (line)
					// free(line);
				break;
			}
			// else if (ft_strlen(line) > 0)
			else
			{
				line = expand(line, 0);
				ft_dprintf(fd, line);
				ft_dprintf(fd, "\n");
				free(line);
			}
		}
		close(fd);
		exit(0);
	}
	else
		wait(0);
	close (end[1]);
	fd = end[0];
	// close(fd);
	if (fd != -1)
	{
		// close(fd);
		printf("File '%s' created.\n", file);
		free(file);
	}
	return fd;
}
