/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:09:50 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/17 06:18:19 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_infile_redir(t_redir *redir, int in)
{
	if (in != 0)
		close(in);
	if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY, 0644));
	if (redir->type == HEREDOC)
		open_here_doc();
	return (in);
}

int	ft_outfile_redir(t_redir *redir, int out)
{
	if (out != 1)
		close(out);
	if (redir->type == REDIR_OUT)
		return (open(redir->file, O_CREAT | O_RDWR | O_TRUNC, 0644));
	if (redir->type == APPEND)
			return (open(redir->file, O_CREAT | O_RDWR | O_APPEND, 0644));
	return (out);
}

void    exec_redir(int in_fd, int out_fd)
{
	t_redir *new;
	int	in_flag = 0;
	int	out_flag = 0;

	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	if (g_data.ms->rd)
	{
		new = g_data.ms->rd;
		while(new)
		{
			printf("%s\n", new->file);
			if(new->type == HEREDOC || new->type == REDIR_IN)
			{
				in_fd = ft_infile_redir(new, in_fd);
				in_flag = 1;
			}
			else if(new->type == APPEND || new->type == REDIR_OUT)
			{
				out_fd = ft_outfile_redir(new, out_fd);
				out_flag = 1;
			}
			if (in_fd < 0 || out_fd < 0)
			{
				ft_putstrr_fd(": no such file or directory ", 2);
				g_data.exit_s = 127;
				exit(g_data.exit_s);
			}
			new = new->next;
		}
		if (in_flag)
			dup2(in_fd, 0);
		if (out_flag)
			dup2(out_fd, 1);
	}
	printf("vetbv\n");
}
