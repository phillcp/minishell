/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:30 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 13:37:04 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utilities.h"

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
