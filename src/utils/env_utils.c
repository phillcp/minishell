/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:15 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/09 15:56:46 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "minishell.h"
#include "utilities.h"

char	*get_env_value(t_env *env, char *key)
{
	t_env	*cur;

	cur = env;
	if (!env)
		return (NULL);
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
			break ;
		if (cur->next == NULL)
			return (NULL);
		cur = cur->next;
	}
	return (cur->content);
}

t_env	*new_env_node(char *key, char *content)
{
	t_env	*new;

	if (!key || !content)
	{
		ft_free(key);
		ft_free(content);
		return (NULL);
	}
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
	{
		free(key);
		free(content);
		return (NULL);
	}
	new->key = key;
	new->content = content;
	new->next = NULL;
	return (new);
}

int	add_env_node(t_env **head, t_env *node)
{
	t_env	*cur;

	if (!node)
		return (0);
	if (!(*head))
	{
		*head = node;
		return (1);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
	return (1);
}

static void	swap_env(t_env *tmp1, t_env *tmp2)
{
	char	*tmp_key;
	char	*tmp_cont;

	tmp_key = tmp1->key;
	tmp_cont = tmp1->content;
	tmp1->content = tmp2->content;
	tmp1->key = tmp2->key;
	tmp2->content = tmp_cont;
	tmp2->key = tmp_key;
}

t_env	*sort_env(t_env *env)
{
	t_env	*tmp1;
	t_env	*tmp2;
	int		swap;

	swap = 1;
	while (swap)
	{
		swap = 0;
		tmp1 = env;
		while (tmp1 && tmp1->next)
		{
			tmp2 = tmp1->next;
			if (ft_strcmp(tmp1->key, tmp2->key) > 0)
			{
				swap_env(tmp1, tmp2);
				swap = 1;
			}
			tmp1 = tmp2;
		}
	}
	return (env);
}
