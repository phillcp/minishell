/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:56 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 19:54:37 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"

void	pipe_loop(t_big *v, t_tree *t, int i);
int		check_empty_cmd(char **cmd);
void	go_wait(int *pid_lst, int *status, int i);

#endif
