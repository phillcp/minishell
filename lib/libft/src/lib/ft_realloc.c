/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:30:15 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/06 11:21:24 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t o_size, size_t n_size)
{
	char	*ret;

	if (!ptr)
		return (ft_calloc(n_size, 1));
	if (!n_size)
	{
		ft_free(ptr);
		return (NULL);
	}
	ret = malloc(n_size);
	if (!ret)
		return (ptr);
	if (o_size > n_size)
		o_size = n_size;
	ft_memcpy(ret, ptr, o_size);
	ft_free(ptr);
	return (ret);
}
