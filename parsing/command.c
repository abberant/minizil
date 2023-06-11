/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:54:56 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/11 22:32:02 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_path(char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = -1;
	path = NULL;
	(void)cmd;
	while (g_data.env && g_data.env[++i])
	{
		tmp = ft_strstr(g_data.env[i], "PATH");
		if (tmp)
		{
			path = ft_split(tmp + 5, ':');
			break ;
		}
	}
	if (!path)
		return (NULL);
	// tmp = ft_strjoin(path, "/");
	// printf("tmp = %s\n", tmp);
	// path = ft_strjoin(tmp, cmd);
	// printf("path = %s\n", path);
	// free(tmp);
	// free(path);
	return (path);
}