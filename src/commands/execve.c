/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:54:28 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/21 18:07:33 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"

#include "libft.h"

/*
*   Finds executable in PATH if exists ele executes command with relative path
*/
static char	*path_creation(t_big *v, char *path, char *cmd)
{
	char		*temp;
	char		*new_path;
	t_dl_list	*head;

	head = v->env;
	if (!ft_strncmp(cmd, "./", 2) || ft_strcmp(cmd, "a.out"))
		new_path = ft_strjoin(return_env_content(v->env, "PWD"), ++cmd);
	else if (!ft_strncmp(cmd, "/", 1))
		new_path = ft_strdup(cmd);
	else
	{
		temp = ft_strjoin(path, "/");
		new_path = ft_strjoin(temp, cmd);
		ft_free(temp);
		temp = NULL;
	}
	v->env = head;
	return (new_path);
}

static void	create_env_array_loop(t_big *v, char **env)
{
	char	*temp;
	int		i;

	i = -1;
	while (v->env)
	{
		temp = ft_strjoin(v->env->name, "=");
		env[++i] = ft_strjoin(temp, v->env->content);
		ft_free(temp);
		v->env = v->env->next;
		if (!v->env)
			break ;
	}
	env[++i] = NULL;
}

static char	**temp_env(t_big *v)
{
	t_dl_list	*head;
	char		**env;
	int			size;

	head = v->env;
	size = 0;
	while (v->env)
	{
		v->env = v->env->next;
		size++;
		if (!v->env)
			break ;
	}
	v->env = head;
	env = (char **)malloc(sizeof(char *) * (size + 1));
	create_env_array_loop(v, env);
	v->env = head;
	return (env);
}

/*
*   The path creation loop function is mainly used to cut down lines on the
*    execve function body. It will loop through all the possible path's found in
*    the env "PATH" ($PATH) and try to run each of them with the inputed cmd.
*/
static int	path_creation_loop(t_big *v, char **cmds, char **path, char *cmd)
{
	char	**env;
	char	*total;
	int		i;
	int		j;

	i = -1;
	j = -1;
	env = temp_env(v);
	while (path[++i])
	{
		total = path_creation(v, path[i], cmd);
		if ((execve(total, cmds, env) != -1))
			--j;
		ft_free(total);
		total = NULL;
		++j;
	}
	free_table(env);
	if (j == i)
		return (1);
	return (127);
}

/*
*   The execve function is used to execute various commands such as ls, wc, grep
*    etc. This commands are not mandatory but will improve the user experience
*    and they will help during the program evaluation.
*/
int	ft_execve(t_big *v, char **argv, int i)
{
	char	*path;
	char	**paths;
	int		j;

	if (!argv[i])
		return (0);
	path = return_env_content(v->env, "PATH");
	paths = ft_split((const char *)path, ':');
	v->str = NULL;
	j = path_creation_loop(v, argv, paths, argv[i]);
	if (j == 127)
	{
		printf("a\n");
		error_output(v, 'c', argv[0]);
	}
	return (j);
}
