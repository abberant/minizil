/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:57:47 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/15 01:46:20 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	dup = ft_calloc(sizeof(char), (ft_strlen(str) + 1));
	if (!dup)
		exit(EXIT_FAILURE);
	i = 0;
	while (str && str[i])
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}
