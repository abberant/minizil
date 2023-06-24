/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:09:50 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/21 11:08:25 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_infile_redir(t_redir *redir, int in)
{
	if (in != 0)
		close(in);
	if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY, 0644));
	if (redir->type == HEREDOC)
		in = redir->fd;
	return (in);
}

int	ft_outfile_redir(t_redir *redir, int out)
{
	if (out != 1)
		close(out);
	if (redir->type == REDIR_OUT)
		return (open(redir->file, O_CREAT | O_TRUNC | O_RDWR, 0644));
	if (redir->type == APPEND)
		return (open(redir->file, O_CREAT | O_APPEND | O_RDWR, 0644));
	return (out);
}

int    exec_redir(int in_fd, int out_fd)
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
			if(new->type == HEREDOC || new->type == REDIR_IN)
			{
				if (in_fd != 0)
					close (in_fd);
				in_fd = ft_infile_redir(new, in_fd);
				in_flag = 1;
			}
			else if(new->type == APPEND || new->type == REDIR_OUT)
			{
				if (out_fd != 1)
					close(out_fd);
				out_fd = ft_outfile_redir(new, out_fd);
				out_flag = 1;
			}
			if (g_data.ms->rd->error)
			{
				ft_dprintf(2, "%s : ambiguous redirect\n", g_data.ms->rd->file);
				exit(1);
			}
			if (in_fd < 0 || out_fd < 0)
			{
				ft_dprintf(2, "%s : no such file or directory\n", g_data.ms->rd->file);
				exit(1);
			}
			new = new->next;
		}
		if (in_flag)
		{
			dup2(in_fd, 0);
			close(in_fd);
		}
		if (out_flag)
		{
			dup2(out_fd, 1);
			close(out_fd);
		}
	}
	g_data.exit_s = 0;
	return (g_data.exit_s);
}
