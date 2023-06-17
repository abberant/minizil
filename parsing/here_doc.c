/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:47:54 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/16 17:04:50 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_here_doc()
{
	int i;
	char *line;
	size_t buffer_len = 0;
	char buffer[BUFFER_SIZE];
	size_t line_len;

	i = 0;
	while (g_data.ms)
	{
		while (g_data.ms->rd)
		{
			if (g_data.ms->rd && g_data.ms->rd->type == HEREDOC)
			{
				line = readline(YELLOW " >" RESET);
				if (!line || (!ft_strncmp(g_data.ms->rd->file, line, ft_strlen(g_data.ms->rd->file) + 1)))
				{
					if (!g_data.ms->rd->next)
					{
						free(line);
						break;
					}
					g_data.ms->rd = g_data.ms->rd->next;
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
			g_data.ms->rd = g_data.ms->rd->next;
		}
		g_data.ms = g_data.ms->next;
	}
	buffer[buffer_len] = '\0';
	ft_dprintf(1, buffer);
	return (0);
}
