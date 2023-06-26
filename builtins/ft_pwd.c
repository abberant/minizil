/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:21:49 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/26 21:22:47 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*holder;
	t_env	*env;
	int		i;

	i = 0;
	holder = NULL;
	holder = getcwd(NULL, 0);
	while (!holder && g_data.env[i])
	{
		env = ft_set(g_data.env[i]);
		if (ft_strcmp(env->name, "PWD") == 0)
			holder = ft_strdup(env->value);
		ft_free_env(env);
		i++;
	}
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
