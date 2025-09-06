/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:12:50 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/06 11:24:45 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_treeadd(t_tree *tree, void *content)
{
	t_tree	*new;

	if (!content)
		return (0);
	new = ft_treenew(content);
	if (!new)
		return (0);
	tree->leaves = ft_realloc(tree->leaves, tree->lcount * sizeof(t_tree),
			(tree->lcount + 1) * sizeof(t_tree));
	if (!tree->leaves)
	{
		ft_free(new);
		return (0);
	}
	tree->leaves[tree->lcount++] = new;
	return (1);
}

int	ft_treeclear(t_tree *t, void (*del)(void *))
{
	if (!t)
		return (0);
	del(t->content);
	while (t->lcount)
		ft_treeclear(t->leaves[--t->lcount], del);
	ft_free(t->leaves);
	ft_free(t);
	return (1);
}

t_tree	*ft_treenew(void *content)
{
	t_tree	*ret;

	ret = ft_calloc(1, sizeof(t_tree));
	if (!ret)
		return (NULL);
	ret->content = content;
	return (ret);
}
