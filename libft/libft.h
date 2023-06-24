/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:38:00 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/24 16:35:20 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# define BUFFER_SIZE 1024

void	ft_putchar(char c);
void	ft_putnbr(int n);
void	ft_puthexnbr(unsigned long n, int upper);
void	ft_putstr(char *str);
int		ft_isalpha(int i);
int		ft_isdigit(int i);
int		ft_isalnum(int i);
int		ft_isascii(int a);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstrr_fd(char *s, int fd);
size_t	ft_strlen(char *str);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, void *src, size_t n);
void	*ft_memmove(void *dst, void *src, size_t len);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strchr(char *s, int c);
char	*ft_strrchr(char *s, int c);
void	ft_free2d(char **tab);
int		ft_arrsize(char **tab);
size_t	ft_strncmp(char *s1, char *s2, size_t n);
void	*ft_memchr(void *s, int c, size_t n);
char	*ft_strjoinf(char *s1, char *s2);
int		ft_memcmp(void *s1, void *s2, size_t n);
int		ft_strnstr(char *haystack, char *needle, size_t len);
char	*ft_strstr(char *haystack, char *needle);
int		ft_atoi(char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	**ft_split(char *s, char c);
char	*ft_itoa(int n);
int		ft_hex(char *str);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_strcmp(char *s1, char *s2);
char	*ft_readadd_to_store(int fd, char *store);
char	*ft_cull_line(char *store);
char	*ft_cull_extra(char *store);
char	*get_next_line(int fd);
int		ft_dprintf(int fd, const char *s, ...);

#endif
