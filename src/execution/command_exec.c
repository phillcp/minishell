/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:02 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/29 10:06:29 by fheaton-         ###   ########.fr       */
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
		write(2, " Bad pipe\n", 10);
		return (-1);
	}
	return (0);
}

void	child_pipe(t_big *v, t_cmd *cmd, int prev_fd, int *pipefd)
{
	signal(SIGINT, SIG_DFL);
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
	file_input_instruction(v, cmd);
	file_output_instruction(v, cmd);
	cmd_selector(v, cmd->cmd);
	exit_child(v);
}

void	parent_pipe(t_big *v, int *prev_fd, int *pipefd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (!v->last_pipe)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

static void	wait_forks(t_big *v, int *pid_lst, int pid_counter)
{
	int	status;
	int	sig;
	int	i;

	i = -1;
	while (++i < pid_counter)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid_lst[i], &status, 0);
		signal(SIGINT, signal_handler);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGPIPE)
				write(2, "Broken pipe\n", 12);
			else if (sig == SIGINT)
				write(2, "\n", 1);
			v->exit_status = 128 + sig;
		}
		else if (WIFEXITED(status))
			v->exit_status = WEXITSTATUS(status);
	}
}

void	pipe_loop(t_big *v, t_tree *t, int i)
{
	t_tree	*t_temp;
	t_cmd	*cmd;
	int		pipefd[2];
	pid_t	pid;
	int		prev_fd;

	prev_fd = -1;
	while (++i < t->lcount)
	{
		t_temp = t->leaves[i];
		cmd = (t_cmd *)t_temp->content;
		v->hdoc_counter += 10;
		if (i == t->lcount - 1)
			v->last_pipe = 1;
		if (!v->last_pipe)
			if (setup_pipe(pipefd) == -1)
				return ;
		pid = fork();
		v->pid_lst[v->pid_counter++] = pid;
		if (pid == 0)
			child_pipe(v, cmd, prev_fd, pipefd);
		parent_pipe(v, &prev_fd, pipefd);
	}
	wait_forks(v, v->pid_lst, v->pid_counter);
}
