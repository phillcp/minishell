/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:36:31 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/01 20:14:02 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include "execution.h"
#include "utilities.h"

void	hdoc_call_extra(t_big *v, t_cmd *cmd, char *filename, char *sub_s)
{
	cmd->in.heredoc->content = *filename;
	if (!g_global.signal)
	{
		ft_free(*sub_s);
		v->file_counter += 1;
	}
}

void	input_loop_extra(t_big *v, t_commands *cmd)
{
	check_heredoc(v, cmd->tree);
	signal(SIGINT, signal_handler);
	if (g_global.signal)
		return ;
	if (save_hdoc_for_del(v, cmd->tree))
	{
		v->hdoc_counter = 0;
		if (cmd->tree->lcount > 1)
			pipe_loop(v, cmd->tree, -1);
		else
			exec_single(v, cmd->tree);
	}
}

void	signal_hdoc(int signal)
{
	(void)signal;	
	g_global.signal = 1;
	close(0);
}
