/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:26:09 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/26 14:31:08 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_set(char *str)
{
	t_env	*env;
	int		j;
	int		i;

	i = 0;
	j = 0;
	env = malloc(sizeof(t_env));
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == '+')
				j = i - 1;
			else
				j = i;
			break ;
		}
		i++;
	}
	if (j == 0)
		j = i;
	env->name = cancel_quotes(ft_substr(str, 0, j), 1);
	env->value = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	env->next = NULL;
	return (env);
}

void	ft_free_env(t_env *env)
{
	free(env->name);
	free(env->value);
	free(env);
}

char	**ft_add_str_to_tab(char **tab, char *str)
{
	int		i;
	char	**tmp;
	t_env	*env;
	char	*holder;

	i = 0;
	tmp = ft_calloc((ft_arrsize(tab) + 2), sizeof(char *));
	while (tab[i])
	{
		tmp[i] = tab[i];
		i++;
	}
	if (ft_strchr(str, '='))
	{
		env = ft_set(str);
		holder = ft_strjoinf(env->name, "=");
		tmp[i] = ft_strjoinf(holder, env->value);
		free(holder);
		ft_free_env(env);
	}
	else
		tmp[i] = ft_strdup(str);
	free(tab);
	return (tmp);
}

char	**clone_env(char **str)
{
	int		i;
	char	**new;

	i = 0;
	while (str[i])
		i++;
	new = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (str[i])
	{
		new[i] = ft_strdup(str[i]);
		i++;
	}
	return (new);
}

void	sort_env(char **str)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (ft_strcmp(str[i], str[j]) > 0)
			{
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
