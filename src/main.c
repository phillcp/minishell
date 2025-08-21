/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:01:01 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/21 11:13:03 by fheaton-         ###   ########.fr       */
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

t_global	g_global;

/*
*   Struct init function is used to initiate the stuct variable and cut down
*    some lines in the main function body.
*/
static void	struct_init(char **env)
{
	g_global.head = malloc(sizeof(t_dl_list));
	g_global.env = get_env(env);
	g_global.exit = 0;
	g_global.exit_status = 0;
	g_global.exit_ccode = 0;
	g_global.and_flag = 0;
	g_global.or_flag = 0;
	g_global.es_f = 0;
	g_global.stop = 0;
	g_global.fd_in = 0;
	g_global.fd_out = 1;
	g_global.hdoc_counter = 0;
	g_global.temp_path = ft_strdup("/tmp/");
	create_hdoc_and_pid_arrays();
	g_global.file_counter = 0;
	g_global.cmd_counter = 0;
	g_global.pid_counter = 0;
}

/*
*   Check cmd calls function will run the command in case it exists on the tree
*    struct sent by the tree loop function.
*/
static int	check_cmd_calls(t_tree *t)
{
	t_cmd		cmd;
	static int	step;

	if (!t->content)
		return (0);
	cmd = *(t_cmd *)(t->content);
	step += 10;
	g_global.argv = cmd.cmd;
	g_global.hdoc_counter = step;
	if (command_exec(&cmd) == -1)
		return (-1);
	return (1);
}

/*
*   Tree loop function will check the tree leafs for commands. Also, it is
*    responsible for setting up the FD initial logic and retrieving exit
*    status variable from child process's.
*/
void	tree_loop(t_tree *t, int i)
{
	int		status;
	int		ret;
	t_cmd	*cmd;
	t_tree	*t_temp;

	dup_init_and_close('i');
	while (++i < t->lcount)
	{
		t_temp = t->leaves[i];
		cmd = (t_cmd *)t_temp->content;
		ret = check_cmd_calls(t->leaves[i]);
		if (ret == -1)
			break ;
		if (ret == 0 && t->leaves[i])
			tree_loop(t->leaves[i], -1);
		if (cmd && ((cmd->cmd_flags & 0x04) || (cmd->cmd_flags & 0x08)
				|| cmd->cmd_flags & 0x20))
			break ;
	}
	status = dup_init_and_close('c');
	if (g_global.exit_status == 1)
		status = 1;
	(g_global.pid > 0) && (waitpid(g_global.pid, &status, 0));
	(WIFEXITED(status) && !g_global.boola) &&
		(g_global.exit_status = WEXITSTATUS(status)) && (g_global.boola = 1);
}

void file_input_instruction(t_cmd *cmd)
{
	int fd;
	int null_fd;

	fd = 0;
	if (!cmd->in.in)
		return ;
	fd = file_input(cmd->in.input, cmd->in.heredoc, cmd->in.in);
	if (fd < 0 || !cmd->in.in)
	{
		null_fd = open("/dev/null", O_RDONLY);
		if (null_fd >= 0)
		{
			dup2(null_fd, 0);
			close(null_fd);
			return ;
		}
	}
	dup2(fd, 0);
	close(fd);
}

static int	setup_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		write(2, " Bad pipe\n", 10);
		return (-1);
	}
	return (0);
}

void	child_pipe(t_cmd *cmd, int prev_fd, int *pipefd, int is_last)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	if (!is_last)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
	file_output_instruction(cmd);
	file_input_instruction(cmd);
	cmd_selector(cmd->cmd);
	exit(0);
}

void	parent_pipe(int *prev_fd, int *pipefd, int is_last)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (!is_last)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

static void	wait_forks(int *pid_lst, int pid_counter)
{
	int	status;
	int	i = -1;

	while (++i < pid_counter)
		waitpid(pid_lst[i], &status, 0);
}

void	pipe_loop(t_tree *t, int i)
{
	t_tree	*t_temp;
	t_cmd	*cmd;
	int		pipefd[2];
	pid_t	pid;
	int		prev_fd;
	
	prev_fd = -1;
	while (++i < t->lcount)
	{
		t_temp = t->leaves[i];
		cmd = (t_cmd *)t_temp->content;
		g_global.hdoc_counter += 10;
		if (i < t->lcount && setup_pipe(pipefd) == -1)
			return ;
		pid = fork();
		g_global.pid_lst[g_global.pid_counter++] = pid;
		if (pid == 0)
			child_pipe(cmd, prev_fd, pipefd, i == t->lcount - 1);
		parent_pipe(&prev_fd, pipefd, i == t->lcount - 1);
	}
	wait_forks(g_global.pid_lst, g_global.pid_counter);
}

void	exec_single(t_tree *t)
{
	t_cmd	*cmd;
	int		status;
	pid_t	pid;

	cmd = (t_cmd *)t->leaves[0]->content;
	if (ft_strcmp(cmd->cmd[0], "exit"))
	{
		ft_exit(cmd->cmd);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		file_output_instruction(cmd);
		file_input_instruction(cmd);
		cmd_selector(cmd->cmd);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (g_global.exit_status == 1)
		status = 1;
}

static void	input_loop(char *input)
{
	t_commands	*cmd;

	g_global.input = input;
	g_global.first_cmd = 1;
	add_history(input);
	cmd = parse(input);
	if (!cmd->error)
	{
		g_global.cmd = cmd;
		check_heredoc(cmd->tree);
		g_global.hdoc_counter = 0;
		if (cmd->tree->lcount > 1)
			pipe_loop(cmd->tree, -1);
		else
			exec_single(cmd->tree);
		delete_temp(g_global.temp_path);
	}
	else
		printf("Syntax error code: %d\n", cmd->error);
	free_command(cmd);
	ft_free(input);
	re_init();
	input = NULL;
}

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void) argc;
	(void) argv;
	struct_init(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	while ("swag")
	{
		input = readline(CLR_PURPLE"Gui:> "CLR_RST);
		g_global.boola = 0;
		if (input && ft_strlen(input) != 0)
			input_loop(input);
		else if (input)
			ft_free(input);
		if (g_global.exit || !input)
			exit_loop();
	}
	return (0);
}
