/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 01:21:25 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/11 21:30:07 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	non_env(char *str, char **forum)
{
	if (*str == '?')
	{
		*forum = ft_itoa(g_data.exit_s);
		*forum = ft_strjoin(*forum, str + 1);
	}
	else if (!unspecial(*str) && *str)
		*forum = ft_strjoin("?", str);
	else
		*forum = ft_strdup("");
}

char	*env_variable(char *str)
{
	char	*forum;
	int		i;

	i = 0;
	while (g_data.env && g_data.env[i])
	{
		forum = ft_strstr(g_data.env[i], str);
		if (forum)
		{
			if (*(forum + ft_strlen(str)) == '=' && *str == *g_data.env[i])
			{
				forum = ft_strdup(g_data.env[i] + (ft_strlen(str) + 1));
				free(str);
				return (forum);
			}
		}
		i++;
	}
	non_env(str, &forum);
	free(str);
	return (forum);
}

void	env_value(char **forum, char *str, int *i)
{
	char	*calc;
	int		a;

	(*i)++;
	a = *i;
	while (str[*i] && unspecial(str[*i]))
		(*i)++;
	calc = ft_substr(str, a, *i - a);
	calc = env_variable(calc);
	if (!(*forum))
		*forum = ft_strdup("");
	*forum = ft_strjoin(*forum, calc);
	free(calc);
}

void	do_quotes(char *str, int i, int *index)
{
	if (str[i] == DOUBLE_QUOTE && *index != 3)
	{
		if (*index == 2)
			*index = 1;
		else
			*index = 2;
	}
	if (str[i] == SINGLE_QUOTE && *index != 2)
	{
		if (*index == 3)
			*index = 1;
		else
			*index = 3;
	}
}

char	*expand(char *str)
{
	char	*forum;
	int		index;
	int		i;

	i = 0;
	index = 1;
	forum = NULL;
	while (str && str[i])
	{
		do_quotes(str, i, &index);
		if (str[i] == '$' && str[i + 1] && index != 3)
			env_value(&forum, str, &i);
		else
		{
			forum = s_concatinate(forum, str[i]);
			i++;
		}
	}
	free(str);
	return (forum);
}
