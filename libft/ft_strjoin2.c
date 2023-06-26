/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:34:18 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/26 16:22:02 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinf(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (0);
	if (!s1)
		s1 = (char *)ft_calloc(1, sizeof(char));
	s = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!s)
		return (0);
	if (s1)
		while (s1[++i])
			s[i] = s1[i];
	while (s2[j])
		s[i++] = s2[j++];
	return (s);
}
