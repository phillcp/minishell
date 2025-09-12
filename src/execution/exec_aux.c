/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:14 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/12 10:41:19 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"
#include "utilities.h"
#include "execution.h"

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

static void	write_error(t_big *v, t_cmd *cmds, int i)
{
	t_cmd	*cur;
	int		j;

	if (v->exit_status == 0)
		return ;
	j = -1;
	cur = cmds;
	while (++j < i)
		cur = cur->next;
	if (v->exit_status == 127)
		error_output(v, 'x', cur->argv[0]);
}

void	wait_forks(t_big *v, int *pid_lst, int pid_counter, t_cmd *cmds)
{
	int	status;
	int	sig;
	int	i;

	i = -1;
	while (++i < pid_counter)
	{
		waitpid(pid_lst[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			v->exit_status = 128 + sig;
		}
		else if (WIFEXITED(status))
		{
			v->exit_status = WEXITSTATUS(status);
			write_error(v, cmds, i);
		}
	}
	signal(SIGINT, main_signal_handler);
}

void	wait_one_pid(t_big *v, pid_t pid, t_cmd *cmd)
{
	int	status;
	int	sig;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, main_signal_handler);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		v->exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
	{
		v->exit_status = WEXITSTATUS(status);
		write_error(v, cmd, 0);
	}
}
