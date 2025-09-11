/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:02 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/11 12:13:21 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "execution.h"
#include "minishell.h"
#include <signal.h>

static int	setup_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		write(2, "Error in pipe creation\n", 23);
		return (0);
	}
	return (1);
}

void	child_fork(t_big *v, t_cmd *cmd, int prev_fd, int *pipefd)
{
	signal(SIGINT, child_signal_handler);
	signal(SIGPIPE, child_signal_handler);
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	if (!v->last_pipe)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
	if (has_input(cmd))
		fork_input(v, cmd);
	if (has_output(cmd))
		fork_output(v, cmd);
	cmd_selector(v, cmd->argv, true);
	exit_child(v, 0);
}

void	parent_fork(t_big *v, int *prev_fd, int *pipefd)
{
	signal(SIGINT, SIG_IGN);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (!v->last_pipe)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

void	pipe_loop(t_big *v, t_cmd *cmds, int i)
{
	t_cmd	*cur;
	int		pipefd[2];
	pid_t	pid;
	int		prev_fd;

	prev_fd = -1;
	cur = cmds;
	while (++i < cmds->n_cmds && cur)
	{
		if (i == cmds->n_cmds - 1)
			v->last_pipe = 1;
		if (!v->last_pipe)
			if (!setup_pipe(pipefd))
				break ;
		pid = fork();
		if (pid == 0)
			child_fork(v, cur, prev_fd, pipefd);
		v->pid_lst[v->pid_counter++] = pid;
		parent_fork(v, &prev_fd, pipefd);
		cur = cur->next;
	}
	wait_forks(v, v->pid_lst, v->pid_counter, cmds);
}

void	exec_single(t_big *v, t_cmd *cmd)
{
	pid_t	pid;

	if (is_builtin(cmd))
	{
		builtin(v, cmd);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, child_signal_handler);
		if (has_input(cmd))
			fork_input(v, cmd);
		if (has_output(cmd))
			fork_output(v, cmd);
		cmd_selector(v, cmd->argv, false);
		exit_child(v, 0);
	}
	wait_one_pid(v, pid, cmd);
}
