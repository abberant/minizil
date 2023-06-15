/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:47:54 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/14 16:21:43 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void here_doc()
{
	int pid = fork();
	if (pid == 0)
	{
		open_here_doc();
		exit(1);
	}
	else
		wait(0);
}

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
					line_len = strlen(line);
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
	ft_dprintf(1, buffer);
	return (0);
}

void ft_append()
{
	pid_t pid;
	int fd[2];
	t_vdata *tmp;
	t_redir *new;

	tmp = g_data.ms;
	new = g_data.ms->rd;
	while (tmp)
	{
		while (new)
		{
			if (new &&new->type == APPEND)
			{
				new->fd = open(new->file, O_CREAT | O_RDWR | O_APPEND, 0644);
				pipe(fd);
				pid = fork();
				if (pid)
				{
					close(fd[1]);
					wait(0);
					// dup2(fd[0], 0);
				}
				else
				{
					close(fd[0]);
					dup2(new->fd, 1);
					exec_command();
				}
				close(fd[0]);
				close(fd[1]);
				close(new->fd);
			}
			new = new->next;
		}
		tmp = tmp->next;
	}
}