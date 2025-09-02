/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:31:12 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/02 16:30:51 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	in_q_dq_assign(bool *in_q_dq, bool *skip, int *count)
{
	*in_q_dq = !(*in_q_dq);
	*skip = true;
	(*count)++;
}

t_list	*init_list(int key, char *in_out, char c)
{
	t_list	*l;

	l = NULL;
	if (c == '<')
	{
		if (!key)
			l = ft_lstnew(ft_strjoin("<", in_out));
		else
			l = ft_lstnew(ft_strjoin("<<", in_out));
	}
	else if (c == '>')
	{
		if (!key)
			l = ft_lstnew(ft_strjoin(">", in_out));
		else
			l = ft_lstnew(ft_strjoin(">>", in_out));
	}
	return (l);
}

t_parse	*assign_error(t_parse *cmd, int i)
{
	if (i != 0)
		cmd->error = i;
	return (cmd);
}

void	set_false(bool *in_q, bool *in_dq, bool *in_var, bool *skip)
{
	*(in_q) = false;
	*(in_dq) = false;
	*(in_var) = false;
	*(skip) = false;
}
