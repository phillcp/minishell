/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:56:37 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/09 15:03:40 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	free_node(t_env *cur)
{
	ft_free(cur->key);
	ft_free(cur->content);
	cur->key = NULL;
	cur->content = NULL;
	ft_free(cur);
}

void	ft_unset(t_big *v, t_env **head, char **argv)
{
	t_env	*cur;
	t_env	*prev_node;
	int		i;

	i = 0;
	while (argv[++i])
	{
		cur = *head;
		prev_node = NULL;
		while (cur)
		{
			if (!ft_strcmp(cur->key, argv[i]))
			{
				if (prev_node)
					prev_node->next = cur->next;
				else
					*head = cur->next;
				free_node(cur);
				break ;
			}
			prev_node = cur;
			cur = cur->next;
		}
	}
	v->exit_status = 0;
}
