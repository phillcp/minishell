/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:31:12 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 11:36:38 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	aux(const char *str, int i, char *q)
{
	if (str[i] == '\'' && !(*q & 2))
		*q ^= 1;
	else if (str[i] == '\"' && !(*q & 1))
		*q ^= 2;
}

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

t_commands	*assign_error(t_commands *cmd, int i)
{
	if (i != 0)
		cmd->error = i;
	return (cmd);
}
