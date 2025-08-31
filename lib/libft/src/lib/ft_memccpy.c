/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:57:49 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 14:08:57 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*memdest;
	unsigned char	*memsrc;
	size_t			i;

	memdest = (unsigned char *)dest;
	memsrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		memdest[i] = memsrc[i];
		if (memsrc[i] == (unsigned char)c)
			return (memdest + i + 1);
		i++;
	}
	return (NULL);
}
