/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selectors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:51 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/21 17:30:16 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "commands.h"
#include "utilities.h"

static int	screening_two(t_big *v, char ***argv_p, int i)
{
	char	**argv;

	argv = *argv_p;
	if (ft_strcmp(argv[i], "pwd"))
		ft_pwd();
	else if (ft_strcmp(argv[i], "export"))
		ft_export(v, argv);
	else if (ft_strcmp(argv[i], "unset"))
		ft_unset(v->env, argv, i);
	else
		i = 1;
	return (i);
}

int	screening_one(t_big *v, char **argv)
{
	int	i;

	i = 0;
	if (argv)
	{
		if (ft_strcmp(argv[i], "exit"))
			ft_exit(v, argv);
		else if (ft_strcmp(argv[i], "echo"))
			ft_echo(argv);
		else if (ft_strcmp(argv[i], "cd"))
			ft_cd(v, argv);
		else if (ft_strcmp(argv[i], " "))
			write(1, "\n", 1);
		else if (ft_strcmp(argv[i], "env"))
			ft_env(v->env);
		else
			i = screening_two(v, &argv, i);
	}
	return (i);
}

void	cmd_selector(t_big *v, char **argv)
{
	if (argv[0])
	{
		if (ft_strcmp(argv[0], "echo"))
			ft_echo(argv);
		else if (ft_strcmp(argv[0], "env"))
			ft_env(v->env);
		else if (ft_strcmp(argv[0], "pwd") || ft_strcmp(argv[0], "PWD"))
			ft_pwd();
		else if (ft_strcmp(argv[0], "cd"))
			ft_cd(v, argv);
		else if (ft_strcmp(argv[0], "exit") || ft_strcmp(argv[0], "unset") ||
	ft_strcmp(argv[0], "export"))
			return ;
		else
			ft_execve(v, argv, 0);
	}
}

int	builtin(t_big *v, t_cmd	*cmd)
{
	int	s_stdin;
	int	s_stdout;
	int	i;

	save_std_fds(&s_stdin, &s_stdout);
	file_output_instruction(v, cmd);
	file_input_instruction(v, cmd);
	i = screening_one(v, cmd->cmd);
	restore_std_fds(s_stdin, s_stdout);
	if (!i)
		return (0);
	return (1);
}

int	cmd_identifier(char **argv)
{
	int	i;

	i = 0;
	if (argv)
	{
		if (ft_strcmp(argv[i], "exit"))
			i = 0;
		else if (ft_strcmp(argv[i], "cd"))
			i = 0;
		else if (ft_strcmp(argv[i], " "))
			i = 0;
		else if (ft_strcmp(argv[i], "echo"))
			i = 0;
		else if (ft_strcmp(argv[i], "env"))
			i = 0;
		else if (ft_strcmp(argv[i], "export") && argv[i + 1] != NULL)
			i = 0;
		else if (ft_strcmp(argv[i], "unset") && argv[i + 1] != NULL)
			i = 0;
		else if (ft_strcmp(argv[i], "pwd"))
			i = 0;
		else
			i = 1;
	}
	return (i);
}
