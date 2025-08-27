/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:30 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/27 16:47:27 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utilities.h"

// static void	end_flag_condition(void)
// {
// 	if (g_global.and_flag > 0 && (g_global.es_f || g_global.exit_status))
// 	{
// 		if (g_global.exit_status)
// 			g_global.stop = 3;
// 	}
// 	else if (g_global.or_flag > 0 && (!g_global.es_f || !g_global.exit_status))
// 	{
// 		if (g_global.exit_status)
// 			g_global.stop = 4;
// 		else
// 			g_global.stop = -2;
// 	}
// }

/*
*   Modifies the STOP, AND, OR and ES flags if the command flag && or || was
*    flagged.
*/

// static void	and_or_flag(t_cmd *cmd)
// {
// 	if ((cmd->cmd_flags & 0x04))
// 	{
// 		if (g_global.exit_status != 0)
// 		{
// 			g_global.es_f = g_global.exit_status;
// 			g_global.and_flag++;
// 			g_global.stop = 1;
// 		}
// 		else
// 			g_global.and_flag++;
// 	}
// 	else
// 		g_global.and_flag = 1;
// 	if (cmd->cmd_flags & 0x08)
// 	{
// 		if (!g_global.exit_status)
// 		{
// 			g_global.es_f = g_global.exit_status;
// 			g_global.or_flag++;
// 			g_global.stop = 2;
// 		}
// 		else
// 			g_global.or_flag++;
// 	}
// }

void	exit_loop2(t_big *v)
{
	close(2);
	close(1);
	close(0);
	exit_loop(v);
}

void	save_std_fds(int *in, int *out)
{
	*in = dup(0);
	*out = dup(1);
}

void	restore_std_fds(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

// int	dup_init_and_close(char type)
// {
// 	if (type == 'i')
// 	{
// 		g_global.tmp_in = dup(0);
// 		g_global.tmp_out = dup(1);
// 		g_global.fd_in = dup(g_global.tmp_in);
// 	}
// 	else if (type == 'c')
// 	{
// 		dup2(g_global.tmp_in, 0);
// 		dup2(g_global.tmp_out, 1);
// 		close(g_global.tmp_in);
// 		close(g_global.tmp_out);
// 	}
// 	return (0);
// }
