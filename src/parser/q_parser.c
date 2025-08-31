/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:30 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 11:37:47 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "utilities.h"

int	unmask_str(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		(str[i] &= 0x7F);
		!str[i] && (str[i] = '$');
	}
	return (1);
}

int	unmask(t_tree *t)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)t->content;
	i = -1;
	if (cmd && cmd->line)
		unmask_str(cmd->line);
	if (cmd && cmd->cmd)
		while (cmd->cmd[++i])
			if (!unmask_str(cmd->cmd[i]))
				return (0);
	i = 0;
	while (i < t->lcount)
		if (!unmask(t->leaves[i++]))
			return (0);
	return (1);
}

static char	*rem_q(char *str, int count)
{
	char	*ret;
	int		p1;
	int		p2;

	ret = ft_calloc(ft_strlen(str) - count + 1, 1);
	if (!ret)
		return (NULL);
	p1 = -1;
	p2 = -1;
	while (str[++p1])
		if (!ft_strchr("\"\'", str[p1]))
			ret[++p2] = str[p1];
	ft_free(str);
	return (ret);
}

static void	mask_char(char *c, bool in_q, bool in_dq, bool skip)
{
	if ((*c & 0x7F) && (in_q || in_dq) && !skip)
		*c |= 0x80;
}

char	*process_quotes(char *str, int count)
{
	bool	in_q;
	bool	in_dq;
	bool	in_var;
	bool	skip;
	char	*s;

	set_false(&in_q, &in_dq, &in_var, &skip);
	s = str - 1;
	while (*++s)
	{
		skip = false;
		if (*s == '\'' && !in_dq)
			in_q_dq_assign(&in_q, &skip, &count);
		else if (*s == '\"' && !in_q)
			in_q_dq_assign(&in_dq, &skip, &count);
		if (*s == '$' && !in_q)
			in_var = true;
		if (ft_strchr(" \'\"|", *s))
			in_var = false;
		if (*s == '$' && in_q)
			*s = 0x80;
		mask_char(s, in_q, in_dq, skip);
	}
	return (rem_q(str, count));
}
