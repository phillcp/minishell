/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 19:38:22 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 14:12:05 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nlen(unsigned int n)
{
	size_t	len;

	len = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*cat(char *str, long number, int i)
{
	while (i >= 0)
	{
		str[i] = (number % 10) + '0';
		number /= 10;
		if (i == 0)
			break ;
		i--;
	}
	return (str);
}

char	*ft_uitoa(unsigned int n)
{
	char	*number;
	size_t	len;
	int		i;

	len = ft_nlen(n);
	number = malloc(len + 1);
	if (!number)
		return (NULL);
	i = (int)len - 1;
	if (n)
		number = cat(number, n, i);
	number[len] = '\0';
	if (!n)
		number[0] = 0 + 48;
	return (number);
}
