/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:11 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 15:54:06 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "utilities.h"

static int	input(char *s, t_cmd *cmd, int heredoc)
{
	int		i;
	int		skp;
	t_list	*l;
	char	*in;

	skp = 0;
	i = 0;
	l = NULL;
	get_in(s, &skp, &i, &in);
	l = init_list(heredoc, in, '<');
	free(in);
	if (!l)
		return (-1);
	if (heredoc)
		ft_lstadd_back(&cmd->in.heredoc, l);
	else
		ft_lstadd_back(&cmd->in.input, l);
	cmd->in.in = l;
	ft_memset(s - (1 + heredoc), ' ', skp + i + 1 + heredoc);
	return (skp + i + heredoc);
}

static int	output(char *str, t_cmd *cmd, int append)
{
	int		i;
	int		skip;
	t_list	*l;
	char	*out;

	skip = 0;
	i = 0;
	l = NULL;
	while (str[skip] && ft_isspace((int)str[skip]))
		skip++;
	while (str[skip + i] && !ft_isspace(str[skip + i]))
		i++;
	out = ft_substr(str, skip, i);
	l = init_list(append, out, '>');
	free(out);
	if (!l)
		return (-1);
	if (append)
		ft_lstadd_back(&cmd->in.append, l);
	else
		ft_lstadd_back(&cmd->in.output, l);
	cmd->in.out = l;
	ft_memset(str - (1 + append), ' ', skip + i + 1 + append);
	return (skip + i + append);
}

int	parse_op_cmd2(char *cur, t_cmd *cmd)
{
	int	i;

	if (!ft_strncmp(cur, "<<", 2))
		i = input(cur + 2, cmd, 1);
	else if (!ft_strncmp(cur, ">>", 2))
		i = output(cur + 2, cmd, 1);
	else if (*cur == '<')
		i = input(cur + 1, cmd, 0);
	else if (*cur == '>')
		i = output(cur + 1, cmd, 0);
	else
		i = 0;
	return (i);
}

static int	parse_op_cmd(t_cmd *cmd)
{
	bool	in_q;
	bool	in_dq;
	char	*cur;
	int		i;

	in_q = false;
	in_dq = false;
	cur = (char *) cmd->line;
	while (*cur)
	{
		if (*cur == '\'' && !in_dq)
			in_q = !in_q;
		else if (*cur == '\"' && !in_q)
			in_dq = !in_dq;
		if (in_q || in_dq)
		{
			cur++;
			continue ;
		}
		i = parse_op_cmd2(cur, cmd);
		if (i < 0)
			return (0);
		cur += i + 1;
	}
	return (1);
}

int	parse_op(t_tree *t)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)t->content;
	if (cmd)
		if (!parse_op_cmd(cmd))
			return (0);
	i = 0;
	while (i < t->lcount)
		if (!parse_op(t->leaves[i++]))
			return (0);
	return (1);
}
