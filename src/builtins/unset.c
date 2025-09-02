/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:56:37 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/01 00:30:05 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	node_destroyer(t_dl_list *list)
{
	ft_free(list->name);
	ft_free(list->content);
	list->name = NULL;
	list->content = NULL;
	ft_free(list);
	list = NULL;
}

static int	lst_str_check(t_dl_list *lst, char *str)
{
	t_dl_list	*head;
	char		*name;

	head = lst;
	while (1)
	{
		name = lst->name;
		if (ft_strcmp(name, str))
		{
			lst = head;
			return (1);
		}
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	lst = head;
	return (0);
}

void	ft_unset(t_big *v, t_dl_list *env, char **argv, int i)
{
	t_dl_list	*head;
	t_dl_list	*temp;
	t_dl_list	*temp2;

	head = env;
	temp = NULL;
	if (!(lst_str_check(env, argv[i + 1])))
		return ;
	while (!(ft_strcmp(env->name, argv[i + 1])))
	{
		temp = env;
		env = env->next;
	}
	if (env->next != NULL)
		temp2 = env->next;
	else
		temp2 = NULL;
	temp->next = temp2;
	node_destroyer(env);
	env = head;
	v->exit_status = 0;
}
