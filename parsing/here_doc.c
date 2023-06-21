/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:47:54 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/21 06:25:41 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void open_here_doc()
// {
// 	int i;
// 	char *line;
// 	t_vdata	*tmp;
// 	char *last;
// 	char *file;

// 	i = 1;
// 	tmp = g_data.ms;
// 	int fd = open(file , O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	while (tmp)
// 	{
// 		// t_redir *k = tmp->rd; 
// 		// while (k)
// 		// {
// 		// 	count++;
// 		// 	k = k->next ;
// 		// }
// 		while (tmp->rd)
// 		{
// 			if (tmp->rd && tmp->rd->type == HEREDOC)
// 			{
// 				while(1)
// 				{
// 					line = readline(YELLOW " >" RESET);
// 					if (!line || (!ft_strncmp(tmp->rd->file, line, ft_strlen(tmp->rd->file) + 1)))
// 					{ 
// 						if (line)
// 							free(line);
// 						break ;
// 					}
// 					else{
						
// 						write(fd, line, ft_strlen(line) + 1);
// 						free (line);
// 					}
// 				}
// 				// close (fd);
// 				last = ft_strdup(file);
// 				printf("%s-------------\n", last);
// 				// free(file);
// 			}
// 			tmp->rd = tmp->rd->next;
// 		}
// 		tmp = tmp->next;
// 	}
// }
int open_here_doc(char *file, int fd)
{
	char	*line;
	t_vdata	*tmp;

	tmp = g_data.ms;
	fd = -1;

	printf("PASSED\n");
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
			line = readline(YELLOW " >" RESET);
			if (!line || strcmp(file, line) == 0)
			{
				if (line)
					free(line);
				break;
			}
			else
			{
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
	// dup2(fd, 0);
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
