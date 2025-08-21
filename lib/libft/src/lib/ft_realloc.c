/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:30:15 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/21 14:51:39 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t osize, size_t nsize)
{
	char	*ret;

	if (!ptr)
		return (ft_calloc(nsize, 1));
	if (!nsize)
		ft_free(ptr);
	if (!nsize)
		return (NULL);
	ret = ft_calloc(nsize, 1);
	if (!ret)
		return (ptr);
	if (osize > nsize)
		osize = nsize;
	ft_memcpy(ret, ptr, osize);
	ft_free(ptr);
	return (ret);
}
