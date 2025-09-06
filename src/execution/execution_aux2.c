/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 19:51:27 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/05 21:30:45 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "minishell.h"
#include <signal.h>

int	check_empty_cmd(char **cmd)
{
	int	devnull;

	if (!cmd || !cmd[0] || !cmd[0][0])
	{
		devnull = open("/dev/null", O_WRONLY);
		if (devnull == -1)
			write(2, "Couldn't open /dev/null\n", 24);
		dup2(devnull, 1);
		close(devnull);
	}
	return (0);
}

void	swap_env(t_dl_list *tmp1, t_dl_list *tmp2)
{
	char	*tmp_name;
	char	*tmp_cont;

	tmp_name = tmp1->name;
	tmp_cont = tmp1->content;
	tmp1->content = tmp2->content;
	tmp1->name = tmp2->name;
	tmp2->content = tmp_cont;
	tmp2->name = tmp_name;
}

t_dl_list	*sort_env(t_dl_list *env)
{
	t_dl_list	*tmp1;
	t_dl_list	*tmp2;
	int			swap;

	swap = 1;
	while (swap)
	{
		swap = 0;
		tmp1 = env;
		while (tmp1 && tmp1->next)
		{
			tmp2 = tmp1->next;
			if (ft_strcmp(tmp1->name, tmp2->name) > 0)
			{
				swap_env(tmp1, tmp2);
				swap = 1;
			}
			tmp1 = tmp2;
		}
	}
	return (env);
}

void	print_env_export(t_dl_list	*env)
{
	t_dl_list	*head;

	head = env;
	sort_env(env);
	while (env)
	{
		printf("declare -x ");
		printf("%s", (char *)env->name);
		printf("=");
		printf("\"%s\"\n", (char *)env->content);
		env = env->next;
	}
	env = head;
}

int	ft_strisspace(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}
