/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:47:54 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/17 22:07:34 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_here_doc()
{
	int i;
	char *line;
	t_vdata	*tmp;
	size_t buffer_len = 0;
	char buffer[BUFFER_SIZE];
	size_t line_len;

	i = 0;
	tmp = g_data.ms;
	while (tmp)
	{
		while (tmp->rd)
		{
			if (tmp->rd && tmp->rd->type == HEREDOC)
			{
				line = readline(YELLOW " >" RESET);
				if (!line || (!ft_strncmp(tmp->rd->file, line, ft_strlen(tmp->rd->file) + 1)))
				{
					if (!tmp->rd->next)
					{
						free(line);
						break;
					}
					tmp->rd = tmp->rd->next;
						free(line);
					continue;
				}
				else
				{
					line_len = ft_strlen(line);
					if (buffer_len + line_len >= BUFFER_SIZE)
					{
						ft_dprintf(2, "Error: Input exceeds buffer size.\n");
						break;
					}
					strncpy(buffer + buffer_len, line, line_len);
					buffer_len += line_len;
					buffer[buffer_len++] = '\n';
					continue;
					free(line);
				}
			}
			tmp->rd = tmp->rd->next;
		}
		tmp = tmp->next;
	}
	buffer[buffer_len] = '\0';
	ft_dprintf(1, buffer);
	return (0);
}
