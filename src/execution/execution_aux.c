/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:14 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 11:32:55 by fheaton-         ###   ########.fr       */
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
	write (2, "minishell: ", 11);
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
