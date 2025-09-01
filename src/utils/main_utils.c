/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:21 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/01 21:02:55 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

#include "minishell.h"
#include "utilities.h"

void	signal_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static int	save_hdoc(t_big *v, t_cmd *cmd, int *j)
{
	t_list	*head;

	if (cmd->in.heredoc)
	{
		head = cmd->in.heredoc;
		while (cmd->in.heredoc)
		{
			ft_free(v->hdoc_files[++*(j)]);
			v->hdoc_files[*j] = ft_strdup((char *)cmd->in.heredoc->content);
			if (!v->hdoc_files[*j])
			{
				write(2, "Error: unable to save heredoc for deletion\n", 43);
				cmd->in.heredoc = head;
				return (0);
			}
			cmd->in.heredoc = cmd->in.heredoc->next;
		}
		cmd->in.heredoc = head;
	}
	return (1);
}

int	save_hdoc_for_del(t_big *v, t_tree *t)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	i = -1;
	j = -1;
	while (++i < t->lcount)
	{
		cmd = (t_cmd *)t->leaves[i]->content;
		if (!save_hdoc(v, cmd, &j))
			return (0);
	}
	return (1);
}

void	clean_processes(t_big *v)
{
	int	i;

	i = 2;
	while (++i < MAX_FD)
		close(i);
	i = -1;
	while (v->pid_lst[++i] > 0)
	{
		kill(v->pid_lst[i], SIGTERM);
		v->pid_lst[i] = -1;
	}
}

void	re_init(t_big *v)
{
	clean_processes(v);
	g_global.signal = 0;
	v->hdoc_counter = 0;
	v->pid_counter = 0;
	v->last_pipe = 0;
	v->empty_str = 0;
}
