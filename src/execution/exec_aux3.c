/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:20:02 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/09 15:06:15 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "minishell.h"
#include <signal.h>
#include <errno.h>

static void	err_x(char *str)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd(str, 2);
	write(2, ": ", 2);
	write(2, "command not found", 17);
	write(2, "\n", 1);
}

static void	err_i(t_big *v, char *str)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd(str, 2);
	write(2, ": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
	v->exit_status = 1;
}

void	error_output(t_big *v, char type, char *str)
{
	if (type == 'h')
	{
		write (2, "minishell: cd: HOME not set", 11);
		v->exit_status = 1;
	}	
	else if (type == 'x')
		err_x(str);
	else if (type == 'd')
	{
		write (2, "minishell: ", 11);
		ft_putstr_fd(str, 2);
		write (2, ": No such file or directory\n", 28);
		v->exit_status = 1;
	}
	else if (type == 'i')
		err_i(v, str);
}

void	write_error(t_big *v, t_cmd *cmds, int i)
{
	t_cmd	*cur;
	int		j;

	if (v->exit_status == 0)
		return ;
	j = -1;
	cur = cmds;
	while (++j < i)
		cur = cur->next;
	if (v->exit_status == 127)
		error_output(v, 'x', cur->argv[0]);
}
