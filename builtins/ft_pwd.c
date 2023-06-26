/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:21:49 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/26 20:48:33 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*holder;

	holder = NULL;
	holder = getcwd(NULL, 0);
	if (!holder)
	{
		ft_dprintf(2, ERR_NO_SUCH_FILE, "pwd");
		g_data.exit_s = 1;
		return (g_data.exit_s);
	}
	ft_dprintf(1, "%s\n", holder);
	free(holder);
	g_data.exit_s = 0;
	return (g_data.exit_s);
}
