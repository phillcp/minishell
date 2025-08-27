/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:31:12 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/27 21:04:34 by fheaton-         ###   ########.fr       */
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

void	aux1(const char *str, int i, char *q, char *text)
{
	if (str[i] == '\'' && !(*q & 2))
	{
		*text = 1;
		*q ^= 1;
	}
	else if (str[i] == '\"' && !(*q & 1))
	{
		*text = 1;
		*q ^= 2;
	}
}

void	aux2(char c, char *q, int *count)
{
	if (c == '\'' && !(*q & D))
	{
		*q ^= S | Q;
		*count += 1;
	}
	else if (c == '\"' && !(*q & S))
	{
		*q ^= D | Q;
		*count += 1;
	}
}

t_list	*aux3(int heredoc, char *in)
{
	t_list	*l;

	l = NULL;
	if (!heredoc)
		l = ft_lstnew(ft_strjoin("<", in));
	else
		l = ft_lstnew(ft_strjoin("<<", in));
	return (l);
}

t_list	*aux4(int append, char *out)
{
	t_list	*l;

	l = NULL;
	if (!append)
		l = ft_lstnew(ft_strjoin(">", out));
	else
		l = ft_lstnew(ft_strjoin(">>", out));
	return (l);
}
