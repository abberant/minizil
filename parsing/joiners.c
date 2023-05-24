/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joiners.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:36:47 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/24 01:33:18 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unspecial(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '?' || c == '_');
}

char	**alloc_one(void)
{
	char	**buffer;

	buffer = malloc(sizeof(char *));
	*buffer = NULL;
	return (buffer);
}

char	*s_concatinate(char *s, char c)
{
	char	*str;
	int		i;

	if (!s)
		s = ft_strdup("");
	str = malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i++] = c;
	str[i] = '\0';
	free(s);
	return (str);
}

char	**a_concatinate(char **s, char *c)
{
	char	**arr;
	int		i;

	if (!s)
		s = alloc_one();
	arr = malloc(sizeof(char *) * (ft_arrsize(s) + 2));
	if (!arr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		arr[i] = ft_strdup(s[i]);
		i++;
	}
	arr[i++] = ft_strdup(c);
	arr[i] = NULL;
	ft_free2d(s);
	return (arr);
}
