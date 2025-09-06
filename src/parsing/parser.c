/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:20 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/06 15:47:09 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"

static void	free_cmd_cmd(void *v)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)v;
	i = -1;
	if (cmd->cmd)
	{
		while (cmd->cmd[++i])
		{
			ft_free(cmd->cmd[i]);
			cmd->cmd[i] = NULL;
		}
		ft_free(cmd->cmd);
	}
}

static void	free_cmd(void *v)
{
	t_cmd	*cmd;

	if (!v)
		return ;
	cmd = (t_cmd *)v;
	if (cmd->line)
		ft_free(cmd->line);
	free_cmd_cmd(v);
	if (cmd->in.input)
		ft_lstclear(&cmd->in.input, ft_free);
	if (cmd->in.heredoc)
		ft_lstclear(&cmd->in.heredoc, ft_free);
	if (cmd->in.output)
		ft_lstclear(&cmd->in.output, ft_free);
	if (cmd->in.append)
		ft_lstclear(&cmd->in.append, ft_free);
	ft_free(v);
}

void	free_data(t_parse *cmd)
{
	ft_treeclear(cmd->tree, free_cmd);
	ft_free(cmd->line);
	ft_free(cmd);
}

t_parse	*parse(t_big *v, const char *str)
{
	t_parse	*cmd;

	cmd = ft_calloc(1, sizeof(t_parse));
	if (!cmd)
		return (cmd);
	if (!validate(str))
		return (assign_error(cmd, 1));
	cmd->tree = ft_treenew(NULL);
	cmd->line = process_quotes(ft_strdup(str), 0);
	if (!cmd->line || !cmd->tree)
		return (assign_error(cmd, 2));
	if (!split_cmd(cmd->tree, cmd->line, 0))
		return (assign_error(cmd, 3));
	if (!parse_op(v, cmd->tree))
		return (assign_error(cmd, 4));
	if (!expand(v, cmd->tree))
		return (assign_error(cmd, 5));
	if (!word_split(cmd->tree))
		return (assign_error(cmd, 6));
	unmask(cmd->tree);
	return (cmd);
}
