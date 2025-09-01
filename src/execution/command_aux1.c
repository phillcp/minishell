/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aux1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 19:51:27 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/01 14:48:02 by fiheaton         ###   ########.fr       */
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

void	go_wait(int *pid_lst, int *status, int i)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid_lst[i], status, 0);
	signal(SIGINT, signal_handler);
}

void	print_env_export(t_dl_list	*env)
{
	t_dl_list	*head;

	head = env;
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
