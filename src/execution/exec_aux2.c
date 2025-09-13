/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 19:51:27 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/13 21:14:39 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "minishell.h"
#include <signal.h>

void	child_signal_handler(int signal)
{
	g_signal = signal;
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

int	ft_strisspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}
