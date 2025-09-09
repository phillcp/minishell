/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:30 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/09 13:14:32 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utilities.h"
#include "parser.h"
#include <readline/readline.h>

void	exit_loop(t_big *v)
{
	int	exit_ccode;

	exit_ccode = v->exit_ccode;
	if (!v->exit_ccode)
		exit_ccode = v->exit_status;
	free_env(v->env);
	ft_free(v->pid_lst);
	ft_free(v->temp_path);
	rl_clear_history();
	free(v);
	exit(exit_ccode);
}

void	exit_loop2(t_big *v, int i)
{
	if (i)
		perror("init allocation error\n");
	close(2);
	close(1);
	close(0);
	exit_loop(v);
}

void	exit_child(t_big *v, int i)
{
	if (i == 1)
	{
		v->exit_status = 100;
		perror("allocation error in child\n");
	}
	close(2);
	close(1);
	close(0);
	free_parsed(v->parsed);
	exit_loop(v);
}

int	create_pid_array(t_big *v, int n_cmds)
{
	int	i;

	v->pid_lst = ft_calloc(sizeof(int), (n_cmds + 1));
	if (!v->pid_lst)
		return (0);
	i = -1;
	while (++i < n_cmds)
		v->pid_lst[i] = -1;
	return (1);
}
