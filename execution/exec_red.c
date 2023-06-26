/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:09:50 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/26 18:25:54 by aanouari         ###   ########.fr       */
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

void	throw_error(t_redir *new, int in_fd, int out_fd)
{
	if (new->error)
	{
		ft_dprintf(2, AMBIGUOUS_REDIR, new->error_file);
		exit(1);
	}
	if (in_fd < 0 || out_fd < 0)
	{
		ft_dprintf(2, ERR_NO_SUCH_FILE, new->file);
		exit(1);
	}
}

void	ft_red(int *in_fd, int *out_fd, int *in_flag, int *out_flag)
{
	t_redir	*new;

	new = g_data.ms->rd;
	while (new)
	{
		if (new->type == HEREDOC || new->type == REDIR_IN)
		{
			if (*in_fd != 0)
				close(*in_fd);
			*in_fd = ft_infile_redir(new, *in_fd);
			*in_flag = 1;
		}
		else if (new->type == APPEND || new->type == REDIR_OUT)
		{
			if (*out_fd != 1)
				close(*out_fd);
			*out_fd = ft_outfile_redir(new, *out_fd);
			*out_flag = 1;
		}
		throw_error(new, *in_fd, *out_fd);
		new = new->next;
	}
}

int	exec_redir(int in_fd, int out_fd)
{
	int	in_flag;
	int	out_flag;

	in_flag = 0;
	out_flag = 0;
	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	if (g_data.ms->rd)
	{
		ft_red(&in_fd, &out_fd, &in_flag, &out_flag);
		if (in_flag)
			dup_2(in_fd, 0);
		if (out_flag)
			dup_2(out_fd, 1);
	}
	g_data.exit_s = 0;
	return (g_data.exit_s);
}
