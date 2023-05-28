/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:45:35 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/26 22:51:39 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int	ft_putnbr_fd(int n, int fd)
{
	int		num;
	char	c;

	num = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	if (n < 0)
	{
		num += write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		num += ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	num += write(fd, &c, 1);
	return (num);
}

int	ft_putstr_fd(char *s, int fd)
{
	int		i;
	int		num;

	i = -1;
	num = 0;
	while (s[++i])
		num += write(fd, &s[i], 1);
	return (num);
}

int	ft_layout_fd(int fd, const char *s, va_list arg)
{
	int		i;
	int		num;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == 'd')
				num += ft_putnbr_fd(va_arg(arg, int), fd);
			else if (s[i] == 's')
				num += ft_putstr_fd(va_arg(arg, char *), fd);
			else if (s[i] == '%')
				num += write(fd, "%", 1);
		}
		else
			num += write(fd, &s[i], 1);
		i++;
	}
	return (num);
}

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list	arg;
	int		index;

	va_start(arg, s);
	index = ft_layout_fd(fd, s, arg);
	va_end(arg);
	return (index);
}