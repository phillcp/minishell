/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:14 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/22 12:53:01 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

#include "minishell.h"
#include "utilities.h"

void	err_c(t_big *v, char *str)
{
	ft_putstr_fd(str, 2);
	write(2, ": ", 2);
	write (2, "command not found", 17);
	write (2, "\n", 1);
	v->exit_status = 127;
}

void	err_i(t_big *v, char *str)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd(str, 2);
	write(2, ": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
	v->exit_status = 1;
}

void	file_output_instruction(t_big *v, t_cmd *cmd)
{
	int	fd_out;

	if (!cmd->in.out)
		return ;
	fd_out = file_output(v, cmd->in.output, cmd->in.append, cmd->in.out);
	if (fd_out < 0)
		exit(v->exit_status);
	if (dup2(fd_out, 1) == -1)
		perror("dup2 failed");
	close(fd_out);
}

int	builtin_output_i(t_big *v, t_cmd *cmd)
{
	int	fd_out;

	if (!cmd->in.out)
		return (1);
	fd_out = file_output(v, cmd->in.output, cmd->in.append, cmd->in.out);
	if (fd_out < 0)
		return (0);
	if (dup2(fd_out, 1) == -1)
		perror("dup2 failed");
	close(fd_out);
	return (1);
}

/*
*   Check for all input files and if one doesn't exist, returns 0, which
*    prevents the command from running and exiting the command loop.
*/

// static int	file_input_instruction(t_cmd *cmd)
// {
// 	if (cmd->in.in)
// 		g_global.fd_in = file_input(cmd->in.input, cmd->in.heredoc, cmd->in.in);
// 	if (g_global.fd_in < 0)
// 	{
// 		dup2(g_global.tmp_in, 0);
// 		dup2(g_global.tmp_out, 1);
// 		close(g_global.tmp_in);
// 		close(g_global.tmp_out);
// 		return (0);
// 	}
// 	if (dup2(g_global.fd_in, 0) > 0)
// 		close(g_global.fd_in);
// 	return (1);
// }

// void	check_pipe(t_cmd *cmd)
// {
// 	if ((cmd->cmd_flags & 0x40) && !cmd->in.out)
// 	{
// 		pipe(g_global.fd);
// 		g_global.fd_in = g_global.fd[0];
// 		g_global.fd_out = g_global.fd[1];
// 	}
// 	if (!(cmd->cmd_flags & 0x40) && !cmd->in.out)
// 		g_global.fd_out = dup(g_global.tmp_out);
// 	dup2(g_global.fd_out, 1);
// 	close(g_global.fd_out);
// }

/*
*   Checks all outputs and inputs, pipe usage, sets up the FD and create forks.
*    All commands will be executed at the same time, a list of all child PIDs
*    will be created so all child processes can be closed in case of a
*    successful execute.
*    Will kill all ghost processes.
*/

// int	execute_cmd(t_cmd *cmd)
// {
// 	int i;

// 	i = 0;
// 	file_output_instruction(cmd);
// 	file_input_instruction(cmd);
// 	check_pipe(cmd);
// 	g_global.pid = fork();
// 	g_global.pid_lst[g_global.pid_counter++] = g_global.pid;
// 	if (g_global.pid == 0)
// 	{
// 		cmd_selector(cmd->cmd);
// 		exit(0);
// 	}
// 	return (g_global.exit_status);
// }
