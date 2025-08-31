/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:35:04 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 14:06:02 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	neg;
	int	pos;
	int	result;

	neg = 1;
	pos = 0;
	result = 0;
	while (*s && (ft_isspace(*s)))
		s++;
	if (*s && *s == '-')
	{
		neg *= -1;
		s++;
	}
	if (*s && *s == '+')
	{
		pos = 1;
		s++;
	}
	if (neg == -1 && pos == 1)
		return (result);
	while (ft_isdigit(*s))
		result = result * 10 + (*s++ - '0');
	return (result * neg);
}
