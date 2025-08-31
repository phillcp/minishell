/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:41 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 13:47:42 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#include "libft.h"

#include "minishell.h"
#include "parser.h"

static char	*replace(char *s1, const char *s2, int pos, int len)
{
	char	*t1;
	char	*t2;
	char	*mask;
	int		i;

	t1 = ft_substr(s1, 0, pos);
	mask = ft_strdup(s2);
	i = -1;
	if (len & INT_MIN)
		while (mask[++i])
			mask[i] |= 0x80;
	t2 = ft_strjoin(t1, mask);
	ft_free(mask);
	ft_free(t1);
	t1 = ft_strjoin(t2, s1 + pos + (len & INT_MAX));
	ft_free(t2);
	return (t1);
}

static int	expand2(char **s, int *i, t_cmd *cmd, int start)
{
	char	*str;

	str = *s;
	*i = start - 1;
	if ((str[*i + 1] & 0x7F) == '?')
		return (0);
	while (ft_isalnum((str[++(*i)] & 0x7F)) || (str[*i] & 0x7F) == '_')
		;
	*i -= start;
	if (!*(i))
		return (0);
	return (1);
}

static int	expand1(t_big *v, char **str, int start, t_cmd *cmd)
{
	char	*s;
	char	*big;
	char	*tmp;
	int		i;

	s = *str;
	if (!expand2(&s, &i, cmd, start))
		return (0);
	tmp = ft_substr(s, start, i);
	unmask_str(tmp);
	big = ft_listget_dl(tmp, v->env);
	ft_free(tmp);
	if (!big)
		return (0);
	*str = replace(s, big, start - 1, (i + 1));
	i = ft_abs(i - ft_strlen(big));
	ft_free(s);
	return (i - 1);
}

static char	*expand_cmd(t_big *v, char *s, t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if (s[i] == '\'')
			j ^= 1;
		if (j == 1)
			continue ;
		if ((s[i] & 0x7F) == '$')
		{
			if ((s[i + 1] & 0x7F) == '?')
				i += (expand_question(v, &s, i, 0));
			else
				i += (expand1(v, &s, i + 1, cmd));
		}
	}
	return (s);
}

int	expand(t_big *v, t_tree *t)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)t->content;
	if (cmd)
	{
		cmd->line = expand_cmd(v, cmd->line, cmd, -1);
		if (!cmd->line)
			return (0);
	}
	i = 0;
	while (i < t->lcount)
		if (!expand(v, t->leaves[i++]))
			return (0);
	v->exit_status = 0;
	return (1);
}
