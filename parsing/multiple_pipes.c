/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:45:42 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/17 18:17:48 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void dup_2(int fd_1, int fd_2)
// {
//     dup2(fd_1, fd_2);
//     close(fd_1);
// }
// void	dupfd2fd(int fd, int othe_fd)
// {
// 	dup2(fd, othe_fd);
// 	close(fd);
// }

// void	dup_ends(int *ends, int fd_in)
// {
// 	if (fd_in != STDIN_FILENO)
// 		dup_2(fd_in, STDIN_FILENO);
// 	dup_2(ends[1], STDOUT_FILENO);
// 	if (ends[0] > 2)
// 		close(ends[0]);
// }
// void    ft_pipes(int fd_in, int fd_out)
// {
//     t_vdata	*global;
// 	int	fd[2];

// 	global = g_data.ms;
// 	while(global->cmd)
// 	{
// 		puts(global->cmd);
// 		pipe(fd);
// 		// give_birth(fd, fd_in, fd_out);
// 		global = global->next;
// 	}
// 	if(check_built_in(&g_data))
// 		execute(&g_data);
// }
// void	give_birth(int *fd, int fd_out, int fd_in)
// {
// 	int	pid;

// 	fd_in = STDIN_FILENO;
// 	pid = fork();
// 	if(!pid)
// 	{
// 		if(g_data.ms)
// 		{
			
// 			exec_redir(fd_in, fd_out);
// 			if(!check_built_in(&g_data))
// 				exec_command();
// 		}
// 	}
// }
// if (in != 0)
	// close(fd[0]);
// else
	// in = fd[0];
// ---------case 1 :(no infile no outfile)--------------
// read from the input and put in the output
// ---------case2 : (no infile)-------------------------
// read from an input and put the output in the outfilr
// ---------case3 : (no outfile)------------------------
// execute the last cmd and put it in the output 
// ---------case 4 : (withe outfile and infile)---------
// read from the outfile and put it in the outfile
