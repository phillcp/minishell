/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:02 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/15 08:45:36 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "execution.h"
#include "minishell.h"
#include <signal.h>

static int	setup_pipe(int pipefd[2], int prev_fd)
{
	if (pipe(pipefd) == -1)
	{
		write(2, "Error in pipe creation\n", 23);
		if (prev_fd != -1)
			close(prev_fd);
		return (0);
	}
	return (1);
}

static void	child_fork(t_big *v, t_cmd *cmd, int prev_fd, int *pipefd)
{
	signal(SIGINT, child_signal_handler);
	signal(SIGPIPE, child_signal_handler);
	handle_child_pipe(v, prev_fd, pipefd);
	if (has_input(cmd))
		fork_input(v, cmd);
	if (has_output(cmd))
		fork_output(v, cmd);
	cmd_selector(v, cmd->argv, true);
	exit_child(v, 0);
}

static int	go_fork(t_big *v, t_cmd *cur, int *prev_fd, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		failed_fork(v, prev_fd, pipefd);
		return (0);
	}
	if (pid == 0)
		child_fork(v, cur, *prev_fd, pipefd);
	v->pid_lst[v->pid_counter++] = pid;
	signal(SIGINT, SIG_IGN);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (!v->last_pipe)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	return (1);
}

void	pipe_loop(t_big *v, t_cmd *cmds, int i)
{
	t_cmd	*cur;
	int		pipefd[2];
	int		prev_fd;

	prev_fd = -1;
	cur = cmds;
	while (++i < cmds->n_cmds && cur)
	{
		if (i == cmds->n_cmds - 1)
			v->last_pipe = 1;
		if (!v->last_pipe)
			if (!setup_pipe(pipefd, prev_fd))
				break ;
		if (!go_fork(v, cur, &prev_fd, pipefd))
			break ;
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
		signal(SIGINT, main_signal_handler);
		return ;
	}
	if (!go_fork_single(v, cmd, &pid))
		return ;
	wait_one_pid(v, pid, cmd);
}
