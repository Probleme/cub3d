/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:15:59 by ataouaf           #+#    #+#             */
/*   Updated: 2023/10/12 22:12:56 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include <stdarg.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		sign = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

void	put_string(int fd, char *string)
{
	if (!string)
		string = "(null)";
	while (*string)
		write(fd, string++, 1);
}

void	put_digit(int fd, long long int number, int base)
{
	char	*hexadecimal;

	hexadecimal = "0123456789abcdef";
	if (number < 0)
	{
		number *= -1;
		write(fd, "-", 1);
	}
	if (number >= base)
		put_digit(fd, (number / base), base);
	write(fd, &hexadecimal[number % base], 1);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	args;

	va_start(args, str);
	while (*str)
	{
		if ((*str == '%') && ((*(str + 1) == 's') || (*(str + 1) == 'd')
				|| (*(str + 1) == 'x')))
		{
			str++;
			if (*str == 's')
				put_string(fd, va_arg(args, char *));
			else if (*str == 'd')
				put_digit(fd, (long long int)va_arg(args, int), 10);
			else if (*str == 'x')
				put_digit(fd, (long long int)va_arg(args, unsigned int), 16);
		}
		else
			write(fd, str, 1);
		str++;
	}
	va_end(args);
	return (fd);
}
