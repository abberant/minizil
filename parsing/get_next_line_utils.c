/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:37:53 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/09 01:21:24 by lsadiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, int c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == (char )c)
			return ((char *) &str[i]);
		i++;
	}
	if (str[i] == (char)c)
		return ((char *) &str[i]);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*tab;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	tab = (unsigned char *) malloc(size * count);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < count * size)
		tab[i++] = 0;
	return ((void *) tab);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s;

	i = -1;
	j = 0;
	if (!s1)
		s1 = (char *) ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	s = (char *) ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!s)
		return (NULL);
	if (s1)
		while (s1[++i])
			s[i] = s1[i];
	while (s2[j])
		s[i++] = s2[j++];
	// free(s1);
	return (s);
}
