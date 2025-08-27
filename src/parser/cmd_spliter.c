/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_spliter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:30 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/27 21:13:25 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "utilities.h"

int	ft_isspecial(char s)
{
	return (!!ft_strchr(" \t\n\v\f\r<>$\"\'&|()", s));
}

void	get_in(char *s, int *skp, int *i, char **in)
{
	while (s[*skp] && ft_isspace(s[(*skp) + (*i)]))
		(*skp)++;
	while (s[(*skp) + (*i)] && !ft_isspace(s[(*skp) + (*i)])
		&& !ft_isspecial(s[(*skp) + (*i)]))
		(*i)++;
	*in = ft_substr(s, *skp, *i);
	check_mask(in);
}

int	word_split(t_tree *t)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)t->content;
	if (cmd)
		cmd->cmd = ft_split(cmd->line, ' ');
	i = 0;
	while (i < t->lcount)
		if (!word_split(t->leaves[i++]))
			return (0);
	return (1);
}

static void	*newcmd(char *key, char *c)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->line = c;
	if (*key == '|')
		cmd->cmd_flags |= 0x40;
	return (cmd);
}

int	split_cmd(t_tree *t, char *c, int i)
{
	int	j;

	j = i;
	while (j >= 0 && c[i])
	{
		if (c[i] == '|')
		{
			ft_treeadd(t, newcmd(c + i, ft_substr(c, j, i - j)));
			(j = ++i);
		}
		else
			i++;
	}
	if (j >= 0 && i - j > 0)
		ft_treeadd(t, newcmd(c + i, ft_substr(c, j, i - j)));
	if (j == -1 || !c[i])
		return (i);
	return (i + 1);
}
