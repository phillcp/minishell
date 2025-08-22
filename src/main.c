/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:01:01 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/22 16:57:14 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"
#include "execution.h"
#include "commands.h"
#include "readline.h"
#include "history.h"
#include <signal.h>
#include <errno.h>

/*
*   Struct init function is used to initiate the stuct variable and cut down
*    some lines in the main function body.
*/
static void	struct_init(t_big *v, char **env)
{
	v->head = malloc(sizeof(t_dl_list));
	v->env = get_env(v, env);
	v->exit = 0;
	v->exit_status = 0;
	v->exit_ccode = 0;
	v->and_flag = 0;
	v->or_flag = 0;
	v->es_f = 0;
	v->stop = 0;
	v->fd_in = 0;
	v->fd_out = 1;
	v->hdoc_counter = 0;
	v->temp_path = ft_strdup("/tmp/");
	create_hdoc_and_pid_arrays(v);
	v->file_counter = 0;
	v->cmd_counter = 0;
	v->pid_counter = 0;
}

void	wait_one_pid(t_big *v, pid_t pid, char *str)
{
	int	status;
	int	sig;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, signal_handler);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGPIPE)
			write(2, "Broken pipe\n", 12);
		else if (sig == SIGSEGV)
		{
			error_output(v, 'd', str);
			v->exit_status = 127;
		}
		else if (sig == SIGINT)
			write(2, "\n", 1);
		v->exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
		v->exit_status = WEXITSTATUS(status);
}

void	exec_single(t_big *v, t_tree *t)
{
	t_cmd	*cmd;
	pid_t	pid;

	cmd = (t_cmd *)t->leaves[0]->content;
	if (!cmd_identifier(cmd->cmd))
	{
		builtin(v, cmd);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		file_input_instruction(v, cmd);
		file_output_instruction(v, cmd);
		cmd_selector(v, cmd->cmd);
		exit(v->exit_status);
	}
	wait_one_pid(v, pid, cmd->cmd[0]);
}

static void	input_loop(t_big *v, char *input)
{
	t_commands	*cmd;

	v->input = input;
	v->last_pipe = 0;
	add_history(input);
	cmd = parse(v, input);
	if (!cmd->error)
	{
		v->cmd = cmd;
		check_heredoc(v, cmd->tree);
		v->hdoc_counter = 0;
		if (cmd->tree->lcount > 1)
			pipe_loop(v, cmd->tree, -1);
		else
			exec_single(v, cmd->tree);
		delete_temp(v, v->temp_path);
	}
	else
		printf("Syntax error code: %d\n", cmd->error);
	free_command(cmd);
	ft_free(input);
	re_init(v);
	input = NULL;
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_big	*v;

	(void) argc;
	(void) argv;
	v = (t_big *)ft_calloc(sizeof(t_big), 1);
	struct_init(v, env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	while ("swag")
	{
		input = readline(CLR_PURPLE"Minishell:> "CLR_RST);
		v->boola = 0;
		if (input && ft_strlen(input) != 0)
			input_loop(v, input);
		else if (input)
			ft_free(input);
		if (v->exit || !input)
			exit_loop(v);
	}
	return (0);
}

	// int i = 0;
	// while (argv[i])
	// {
	// 	printf("argv[%d]: %s\n", i, argv[i]);
	// 	i++;
	// }
