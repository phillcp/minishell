/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:58:05 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 14:08:39 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*curr;
	t_list	*ret;

	if (lst)
	{
		curr = ft_lstnew(f(lst->content));
		ret = curr;
		while (lst->next && curr)
		{
			lst = lst->next;
			curr->next = ft_lstnew(f(lst->content));
			curr = curr->next;
		}
		if (!curr)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		return (ret);
	}
	return (NULL);
}
