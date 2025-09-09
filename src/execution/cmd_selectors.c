/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_selectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:51 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/09 13:56:16 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "commands.h"
#include "utilities.h"

static void	builtin_exec(t_big *v, char **argv)
{
	if (argv[0])
	{
		if (!ft_strcmp(argv[0], "exit"))
			ft_exit(v, argv);
		else if (!ft_strcmp(argv[0], "echo"))
			ft_echo(v, argv);
		else if (!ft_strcmp(argv[0], "cd"))
			ft_cd(v, argv);
		else if (!ft_strcmp(argv[0], "env"))
			ft_env(v, v->env, argv);
		else if (!ft_strcmp(argv[0], "pwd"))
			ft_pwd(v);
		else if (!ft_strcmp(argv[0], "export"))
			ft_export(v, argv, false);
		else if (!ft_strcmp(argv[0], "unset") && argv[1] != NULL)
			ft_unset(v, &v->env, argv);
	}
}

int	builtin(t_big *v, t_cmd	*cmd)
{
	int	s_in;
	int	s_out;

	save_std_fds(&s_in, &s_out);
	if (!builtin_input(v, cmd) || !builtin_output(v, cmd))
		return (0);
	if (cmd->argv)
		builtin_exec(v, cmd->argv);
	restore_std_fds(s_in, s_out);
	return (1);
}

int	is_builtin(t_cmd *cmd)
{
	int	i;

	if (cmd->argv && cmd->argv[0])
	{
		if (!ft_strcmp(cmd->argv[0], "exit"))
			i = 1;
		else if (!ft_strcmp(cmd->argv[0], "cd"))
			i = 1;
		else if (!ft_strcmp(cmd->argv[0], "echo"))
			i = 1;
		else if (!ft_strcmp(cmd->argv[0], "env"))
			i = 1;
		else if (!ft_strcmp(cmd->argv[0], "export"))
			i = 1;
		else if (!ft_strcmp(cmd->argv[0], "unset") && cmd->argv[1] != NULL)
			i = 1;
		else if (!ft_strcmp(cmd->argv[0], "pwd"))
			i = 1;
		else
			i = 0;
	}
	else
		return (1);
	return (i);
}

void	cmd_selector(t_big *v, char **argv, bool in_pipe)
{
	if (argv)
	{
		if (!ft_strcmp(argv[0], "echo"))
			ft_echo(v, argv);
		else if (!ft_strcmp(argv[0], "env"))
			ft_env(v, v->env, argv);
		else if (!ft_strcmp(argv[0], "pwd") || !ft_strcmp(argv[0], "PWD"))
			ft_pwd(v);
		else if (!ft_strcmp(argv[0], "export") && in_pipe == true)
			ft_export(v, argv, in_pipe);
		else if (!ft_strcmp(argv[0], "exit") || !ft_strcmp(argv[0], "unset")
			|| !ft_strcmp(argv[0], "export") || !ft_strcmp(argv[0], "cd"))
		{
			v->exit_status = 0;
			return ;
		}
		else
			ft_execve(v, argv);
	}
}
