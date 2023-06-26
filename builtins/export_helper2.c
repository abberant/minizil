/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:33:55 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/26 14:48:43 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**print_export(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(str[i], '='))
			printf("declare -x %s\n", str[i]);
		else
		{
			j = 0;
			printf("declare -x ");
			while (str[i][j])
			{
				printf("%c", str[i][j]);
				if (str[i][j] == '=')
					break ;
				j++;
			}
			j++;
			printf("%c%s%c\n", '"', str[i] + j, '"');
		}
		i++;
	}
	return (str);
}

int	ft_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	ft_does_it_exist(char **str, char *new)
{
	int	i;
	int	j;

	i = 0;
	while (new[i])
	{
		if (new[i] == '=' || new[i] == '+')
			break ;
		i++;
	}
	j = 0;
	while (str[j])
	{
		if (!ft_strncmp(str[j], new, i))
		{
			if (str[j][i] == '=' || !str[j][i])
				return (j + 1);
		}
		j++;
	}
	return (0);
}

int	ft_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		if ((str[i] == '+' && str[i + 1] != '=') || str[i] == '-')
		{
			g_data.exit_s = 1;
			return (2);
		}
		if (str[i] == '=')
			break ;
		i++;
	}
	return (0);
}
