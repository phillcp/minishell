/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:21 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 11:45:00 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

#include "minishell.h"
#include "utilities.h"

void	signal_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
*  Closes all possibly open file descriptors and
*  kills all processes that were not naturally closed.
*/
void	clean_processes(t_big *v)
{
	int	i;

	i = 2;
	while (++i < MAX_FD)
		close(i);
	i = -1;
	while (v->pid_lst[++i] > 0)
	{
		kill(v->pid_lst[i], SIGTERM);
		v->pid_lst[i] = -1;
	}
}

void	re_init(t_big *v)
{
	clean_processes(v);
	v->fd_in = 0;
	v->fd_out = 1;
	v->cmd_counter = 0;
	v->file_counter = 0;
	v->hdoc_counter = 0;
	v->pid_counter = 0;
	v->last_pipe = 0;
	v->stop = 0;
	v->and_flag = 0;
	v->or_flag = 0;
	v->last_pipe = 0;
	v->empty_str = 0;
}
