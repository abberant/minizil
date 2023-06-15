/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:09:50 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/15 04:50:39 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_infile_redir(t_vdata *redir, int in)
{
	t_redir	*fl;
	
	if (in != 0)
		close(0);
	if (redir->rd->type == REDIR_IN)
		return (open(fl->file, O_RDONLY, 0644));
	else if (redir->rd->type == HEREDOC)
		ft_here_doc();
}

int	ft_outfile(t_vdata *redir, int out)
{
	t_redir	*fl;

	if (out != 1)
		close(1);
	if (redir->rd->type == REDIR_OUT)
		return (open(fl->file, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (redir->rd->type == APPEND)
		return (open(fl->file, O_CREAT | O_WRONLY | O_APPEND, 0644));
}

void    exec_redir(t_shell g_data, int in_fd, int out_fd)
{
	t_redir *new;

    if(g_data.ms->rd)
	{
		new = g_data.ms->rd;
		while(new)
		{
			if(new->type == HEREDOC || new->type == REDIR_IN)
			{
				in_fd = ft_infile_redir();
				dup2(in_fd, 1);
			}
			else if(new->type == APPEND || new->type == REDIR_OUT)
			{
				out_fd = ft_outfile_redir();
				dup2(out_fd, 1);
			}
			if (in_fd < 0 || out_fd < 0)
			{
				ft_putstrr_fd(": no such file or directory ", 2);
				g_data.exit_s = 127;
				exit(g_data.exit_s);
			}
			new = new->next;
		}
	}
}
