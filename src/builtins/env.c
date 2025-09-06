/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:54:08 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/05 19:42:22 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	print_env(t_dl_list *env)
{
	t_dl_list	*head;

	head = env;
	while (env)
	{
		printf("%s", (char *)env->name);
		printf("=");
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
	env = head;
}

void	ft_env(t_big *v, t_dl_list *env, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 1)
	{
		write(2, "env: \"", 6);
		ft_putstr_fd(argv[1], 2);
		write(2, "\": Permission denied\n", 21);
		v->exit_status = 126;
		return ;
	}
	print_env(env);
	v->exit_status = 0;
}
