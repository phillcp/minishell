/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_mng.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:03 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/02 12:25:48 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>
#include "libft.h"
#include "minishell.h"
#include "utilities.h"

char	*temp_path(char *filename, char *path)
{
	char	*pth;

	if (!filename || !path)
		return (NULL);
	pth = ft_strjoin(path, filename);
	return (pth);
}

static int	create_hrdoc_file(t_big *v, char *eof_str, char *filename)
{
	char	*input;
	int		output;

	if (!eof_str)
		return (-1);
	filename = temp_path(filename, v->temp_path);
	if (!filename)
		return (-1);
	output = open(filename, 02 | 0100 | 01000, 0400 | 0200 | 040 | 04);
	if (output < 0)
		return (-1);
	input = readline("heredoc> ");
	if (go_read_lines(v, input, output, eof_str))
	{
		ft_free(filename);
		ft_free(eof_str);
		return (-1);
	}
	ft_free(filename);
	close(output);
	return (0);
}

static void	check_heredoc_call(t_big *v, t_cmd *cmd)
{
	t_list	*head;
	char	*filename;
	char	*eof;
	char	*sub_s;

	eof = NULL;
	if (cmd->in.heredoc)
		head = cmd->in.heredoc;
	while (cmd->in.heredoc)
	{
		eof = (char *)cmd->in.heredoc->content;
		filename = hdoc_filename(v, eof);
		sub_s = ft_substr(eof, 2, ft_strlen(eof));
		ft_free(eof);
		create_hrdoc_file(v, sub_s, filename);
		if (g_global.signal)
			cmd->in.heredoc->content = filename;
		if (g_global.signal)
			return ;
		ft_free(sub_s);
		cmd->in.heredoc->content = filename;
		cmd->in.heredoc = cmd->in.heredoc->next;
	}
	if (eof)
		cmd->in.heredoc = head;
}

static int	check_loop(t_big *v, t_tree *t)
{
	t_cmd		*cmd;
	static int	step;

	cmd = (t_cmd *)t->content;
	step += 10;
	if (!cmd->in.heredoc)
		return (0);
	v->hdoc_counter = step;
	check_heredoc_call(v, cmd);
	if (g_global.signal)
		return (0);
	return (1);
}

void	check_heredoc(t_big *v, t_tree *t)
{
	int	i;
	int	ret;
	int	stdin_save;

	stdin_save = dup(0);
	signal(SIGINT, signal_hdoc);
	i = -1;
	ret = 1;
	while (++i < t->lcount)
	{
		ret = check_loop(v, t->leaves[i]);
		if (ret == 0 && g_global.signal)
		{
			dup2(stdin_save, 0);
			close(stdin_save);
			return ;
		}
	}
	close(stdin_save);
}
