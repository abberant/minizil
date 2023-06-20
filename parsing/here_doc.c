/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:47:54 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/20 10:44:49 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void open_here_doc()
{
	int i;
	char *line;
	t_vdata	*tmp;
	size_t buffer_len = 0;
	char buffer[BUFFER_SIZE];
	size_t line_len;
	char *last;
	int flag;
	int count;
	char *file;

	flag = 0;
	count = 0;
	i = 1;
	tmp = g_data.ms;
	int fd = open(file , O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (tmp)
	{
		// t_redir *k = tmp->rd; 
		// while (k)
		// {
		// 	count++;
		// 	k = k->next ;
		// }
		while (tmp->rd)
		{
			if (tmp->rd && tmp->rd->type == HEREDOC)
			{
				while(1)
				{
					line = readline(YELLOW " >" RESET);
					if (!line || (!ft_strncmp(tmp->rd->file, line, ft_strlen(tmp->rd->file) + 1)))
					{ 
						if (line)
							free(line);
						break ;
					}
					else{
						
						write(fd, line, ft_strlen(line) + 1);
						free (line);
					}
				}
				close (fd);
				last = ft_strdup(file);
				printf("%s-------------\n", last);
				// free(file);
			}
			tmp->rd = tmp->rd->next;
		}
		tmp = tmp->next;
	}
	ft_dprintf(1, last);
}
