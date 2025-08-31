/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_mng.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:03 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 13:21:19 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "libft.h"
#include "minishell.h"

char	*temp_path(char *filename, char *path, char *eof_str)
{
	char	*pth;

	if (!filename || !path || !eof_str)
	{
		ft_free(filename);
		return (NULL);
	}
	pth = ft_strjoin(path, filename);
	return (pth);
}

static int	create_hrdoc_file(t_big *v, char *eof_str, char *filename)
{
	char	*input;
	int		output;

	filename = temp_path(filename, v->temp_path, eof_str);
	if (!filename)
		return (-1);
	output = open(filename, 02 | 0100 | 01000, 0400 | 0200 | 040 | 04);
	if (output < 0)
		return (-1);
	input = readline("heredoc> ");
	while (input && ft_strcmp(input, eof_str) != 1)
	{
		if (ft_strlen(input) > 0)
			write(output, input, ft_strlen(input));
		write(output, "\n", 1);
		ft_free(input);
		input = readline("heredoc> ");
	}
	ft_free(input);
	ft_free(filename);
	close(output);
	return (0);
}

static void	check_heredoc_call(t_big *v, t_cmd *cmd)
{
	t_list	*head;
	char	*filename;
	char	*eof;
	char	*i;
	char	*sub_s;

	eof = NULL;
	if (cmd->in.heredoc)
		head = cmd->in.heredoc;
	while (cmd->in.heredoc)
	{
		eof = (char *)cmd->in.heredoc->content;
		i = ft_itoa(++v->hdoc_counter);
		filename = ft_strjoin(eof, i);
		ft_free(i);
		sub_s = ft_substr(eof, 2, ft_strlen(eof));
		ft_free(eof);
		if (create_hrdoc_file(v, sub_s, filename) < 0)
			write(2, "Error: unable to create heredoc file\n", 37);
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
	if (!cmd)
		return (0);
	v->hdoc_counter = step;
	check_heredoc_call(v, cmd);
	return (1);
}

void	check_heredoc(t_big *v, t_tree *t)
{
	int	i;
	int	ret;

	i = -1;
	ret = 1;
	while (++i < t->lcount)
	{
		ret = check_loop(v, t->leaves[i]);
		if (ret == 0 && t->leaves[i])
			check_heredoc(v, t->leaves[i]);
	}
}
