/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_spliter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:30 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 13:47:32 by fheaton-         ###   ########.fr       */
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
	return (cmd);
}

int	split_cmd(t_tree *t, char *s, int i)
{
	int	j;

	j = 0;
	while (s[i])
	{
		if (s[i] == '|')
		{
			if (!ft_treeadd(t, newcmd(s + i, ft_substr(s, j, i - j))))
				return (-1);
			j = ++i;
		}
		else
			i++;
	}
	if (!ft_treeadd(t, newcmd(s + i, ft_substr(s, j, i - j))))
		return (-1);
	return (i);
}
