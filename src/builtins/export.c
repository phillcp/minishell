/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:54:56 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/01 00:13:40 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"
#include "libft.h"

static int	find_char(char *s1, char c)
{
	int	x;

	x = 0;
	if (!s1)
		return (x);
	while (s1[x] && s1[x] != c)
		x++;
	return (x);
}

void	free_set(t_big *v, char **content)
{
	free(content[0]);
	free(content[1]);
	v->exit_status = 0;
}

void	add_list(t_big *v, char **content)
{
	t_dl_list	*temp;

	temp = ft_lstnew_dl(content);
	ft_lstadd_back_dl(&v->env, temp);
}

int	check_print_env_export(t_big *v, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		print_env_export(v->env);
		return (1);
	}
	return (0);
}

int	ft_export(t_big *v, char **argv)
{
	t_dl_list	*head;
	char		*content[2];
	char		*arg;

	if (check_print_env_export(v, argv))
		return (1);
	head = v->env;
	arg = argv[1];
	content[0] = get_name(arg, '=');
	if (!content[0])
	{
		export_wrong(arg);
		v->exit_status = 1;
		return (-1);
	}
	if (!find_char(arg, '='))
		return (0);
	content[1] = ft_substr(arg, find_char(arg, '=') + 1, ft_strlen(arg));
	if (check_env_names(v, content[0], content[1]))
		free_set(v, content);
	else
		add_list(v, content);
	v->env = head;
	return (1);
}
