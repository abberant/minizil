/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:47:54 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/08 14:06:16 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	heredoc_six(char **argv, char **envp)
// {
// 	int	fd[2];
// 	int	heredoc;
// 	int outfile;

	
// 	outfile = open(argv[6], O_CREAT | O_RDWR | O_APPEND, 0644);
// 	heredoc = open(".temp", O_RDONLY);
// 	pipe(fd);
// 	if (heredoc != -1)
// 	{
// 		dup2(heredoc, 0);
// 		close(heredoc);
// 	}
// 	dup2(fd[1], 1);
// 	close(fd[1]);
// 	if (fork() == 0)
// 		exec_command();
// 	dup2(fd[0], 0);
// 	close(fd[0]);
// 	dup2(outfile, 1);
// 	close(outfile);
// 	if (fork() == 0)
// 		exec_command();
// 	while (wait(NULL) != -1)
// 		;
// 	close(fd[0]);
// 	close(fd[1]);
// 	unlink(".temp");
// }

int	here_doc(char *delimiter)
{
	int	i;
	char	*line;
	int	fd;
	
	i = 0;
	fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		unlink(".tmp");
		perror("HERE_DOC");
	}
	while(1)
	{
		if (!ft_strncmp(g_data.ms->stack[0], "<<", 1))
		{
			ft_putstrr_fd("here_doc>", 2);
			line = get_next_line(0);
			if (!line || ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0)
			{
				free(line);
				break;
			}
			else
				write(fd, line, ft_strlen(line));
			free(line);
		}
	}
	close(fd);
	return (0);
}
