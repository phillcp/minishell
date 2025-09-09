/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:14 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/09 14:49:50 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"
#include "utilities.h"

int	has_input(t_cmd *cmd)
{
	t_redir	*cur;

	cur = cmd->redirs;
	while (cur)
	{
		if (cur->type == T_HEREDOC || cur->type == T_IN)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	has_output(t_cmd *cmd)
{
	t_redir	*cur;

	cur = cmd->redirs;
	while (cur)
	{
		if (cur->type == T_APPEND || cur->type == T_OUT)
			return (1);
		cur = cur->next;
	}
	return (0);
}

static void	go_wait(int *pid_lst, int *status, int i)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid_lst[i], status, 0);
	signal(SIGINT, signal_handler);
}

void	wait_forks(t_big *v, int *pid_lst, int pid_counter, t_cmd *cmds)
{
	int		status;
	int		sig;
	int		i;

	i = -1;
	while (++i < pid_counter)
	{
		go_wait(pid_lst, &status, i);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				write(2, "\n", 1);
			v->exit_status = 128 + sig;
		}
		else if (WIFEXITED(status))
		{
			v->exit_status = WEXITSTATUS(status);
			write_error(v, cmds, i);
		}
	}
}

void	wait_one_pid(t_big *v, pid_t pid, t_cmd *cmd)
{
	int	status;
	int	sig;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, signal_handler);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(2, "\n", 1);
		v->exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
	{
		v->exit_status = WEXITSTATUS(status);
		write_error(v, cmd, 0);
	}
}
