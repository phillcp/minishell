/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:30 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/06 10:32:18 by fiheaton         ###   ########.fr       */
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
		if (str[i] == '\0')
			str[i] = '$';
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

static char	*remove_quotes(char *str, int count)
{
	char	*ret;
	int		i;
	int		j;

	ret = ft_calloc(ft_strlen(str) - count + 1, 1);
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (str[++i])
		if (!ft_strchr("\"\'", str[i]))
			ret[++j] = str[i];
	ft_free(str);
	ret[++j] = '\0';
	return (ret);
}

char	*process_quotes(char *str, int count)
{
	bool	in_q;
	bool	in_dq;
	bool	skip;
	char	*s;

	if (!str)
		return (NULL);
	set_false(&in_q, &in_dq, &skip);
	s = str - 1;
	while (*++s)
	{
		skip = false;
		if (*s == '\'' && !in_dq)
			in_q_dq_assign(&in_q, &skip, &count);
		else if (*s == '\"' && !in_q)
			in_q_dq_assign(&in_dq, &skip, &count);
		if (*s == '$' && in_q)
			*s = 0x80;
		else if ((in_q || in_dq) && !skip)
			*s |= 0x80;
	}
	return (remove_quotes(str, count));
}
