/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:04:07 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/26 14:44:40 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_exp_append(char *old, char *new, char *holder, char *holder2)
{
	char	*holder3;
	t_env	*env;
	t_env	*env2;

	env = ft_set(old);
	env2 = ft_set(new);
	holder = ft_strjoinf(env->value, env2->value);
	holder2 = ft_strjoinf(env->name, "=");
	holder3 = ft_strjoinf(holder2, holder);
	free(holder);
	free(holder2);
	free(old);
	ft_free_env(env);
	ft_free_env(env2);
	return (holder3);
}

char	*ft_replace_env(char *str, char *new)
{
	t_env	*env;
	t_env	*env2;
	char	*holder;
	char	*holder2;

	env = ft_set(str);
	env2 = ft_set(new);
	holder = ft_strjoinf(env->name, "=");
	holder2 = ft_strjoinf(holder, env2->value);
	free(holder);
	free(str);
	ft_free_env(env);
	ft_free_env(env2);
	return (holder2);
}

void	ft_exp(t_shell *tmp, int j, int i)
{
	if (!j)
		tmp->env = ft_add_str_to_tab(tmp->env, tmp->ms->stack[i]);
	else if (ft_check(tmp->ms->stack[i]))
		tmp->env[j - 1] = ft_exp_append(tmp->env[j - 1],
				tmp->ms->stack[i], NULL, NULL);
	else
		tmp->env[j - 1] = ft_replace_env(tmp->env[j - 1],
				tmp->ms->stack[i]);
}

int	ft_export(void)
{
	t_shell	*tmp;
	int		i;
	int		j;

	i = 1;
	tmp = &g_data;
	sort_env(tmp->env);
	if (!tmp->ms->stack[i])
		tmp->exp = print_export(tmp->env);
	while (tmp->ms->stack[i])
	{
		if (ft_alpha(tmp->ms->stack[i][0]) && ft_check(tmp->ms->stack[i]) != 2)
		{
			j = ft_does_it_exist(tmp->env, tmp->ms->stack[i]);
			ft_exp(tmp, j, i);
		}
		else
			printf(EXPORT_INVALID, tmp->ms->stack[i]);
		g_data.exit_s = 1;
		i++;
	}
	return (g_data.exit_s);
}
