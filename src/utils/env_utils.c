/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:15 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/29 22:54:37 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include "utilities.h"

void	print_env_content(t_dl_list *lst, char *name, char free_name)
{
	char	*content;

	content = NULL;
	if (return_env_content(lst, name))
	{
		content = return_env_content(lst, name);
		if (content == NULL)
			printf("\n");
		else
			printf("%s", content);
	}
	if (free_name == 'y')
		ft_free(name);
}

char	*return_env_content(t_dl_list *lst, char *name)
{
	while (lst)
	{
		if (ft_strcmp(lst->name, name))
			break ;
		if (lst->next == NULL)
			return (NULL);
		lst = lst->next;
	}
	return (lst->content);
}

char	*get_name(char *str, char c)
{
	char	*name;
	int		x;
	int		i;

	x = -1;
	i = 0;
	if (!str || !str[0] || str[0] == '=')
		return (NULL);
	while (str[++x] && str[x] != c)
	{
		if (ft_isalpha(str[x]))
			i = 1;
		if (!ft_isalnum(str[x]))
			return (NULL);
	}
	if (!i)
		return (NULL);
	name = ft_calloc((x + 1), sizeof(char));
	ft_strlcpy(name, str, x + 1);
	return (name);
}

t_dl_list	*get_env(t_big *v, char **env)
{
	t_dl_list	*temp;
	int			x;
	char		**splited;
	int			aux;

	x = -1;
	v->env = NULL;
	splited = malloc(sizeof(char *) * 2);
	while (env[++x] != NULL)
	{
		aux = ft_strichr(env[x], '=');
		splited[0] = ft_substr(env[x], 0, aux);
		splited[1] = ft_substr(env[x], aux + 1, ft_strlen(env[x]) - aux);
		temp = ft_lstnew_dl(splited);
		ft_lstadd_back_dl(&v->env, temp);
	}
	ft_free(splited);
	return (v->env);
}

int	check_env_names(t_big *v, char *name, char *content)
{
	t_dl_list	*head;

	head = v->env;
	while (1)
	{
		if (ft_strcmp(name, v->env->name))
		{
			ft_free(v->env->content);
			v->env->content = ft_strdup(content);
			v->env = head;
			return (1);
		}
		if (v->env->next == NULL)
			break ;
		v->env = v->env->next;
	}
	v->env = head;
	return (0);
}
