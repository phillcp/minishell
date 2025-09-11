/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:56 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/11 02:09:04 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"

void	wait_forks(t_big *v, int *pid_lst, int pid_counter, t_cmd *cmds);
void	wait_one_pid(t_big *v, pid_t pid, t_cmd *cmd);
void	cmd_selector(t_big *v, char **argv, bool in_pipe);
void	child_signal_handler(int signal);
void	pipe_loop(t_big *v, t_cmd *cmds, int i);
int		builtin(t_big *v, t_cmd *cmd);
int		has_output(t_cmd *cmd);
int		has_input(t_cmd *cmd);
int		is_builtin(t_cmd *cmd);
void	exec_single(t_big *v, t_cmd *cmds);

#endif
