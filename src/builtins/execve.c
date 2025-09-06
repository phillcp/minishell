/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:54:28 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/06 10:17:59 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"
#include <signal.h>
#include "libft.h"

static char	*path_creation(t_big *v, char *path, char *cmd)
{
	char		*temp;
	char		*new_path;
	t_dl_list	*head;

	head = v->env;
	if (!ft_strncmp(cmd, "./", 2) || !ft_strcmp(cmd, "a.out"))
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
		if (!temp)
		{
			free_table(env);
			exit_child(v, 1);
		}
		env[++i] = ft_strjoin(temp, v->env->content);
		if (!env[i])
		{
			ft_free(temp);
			free_table(env);
			exit_child(v, 1);
		}
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
	if (!env)
		exit_child(v, 1);
	create_env_array_loop(v, env);
	v->env = head;
	return (env);
}

static int	path_creation_loop(t_big *v, char **cmds, char **path)
{
	char	**env;
	char	*total;
	int		i;

	i = -1;
	env = temp_env(v);
	while (path[++i])
	{
		total = path_creation(v, path[i], cmds[0]);
		execve(total, cmds, env);
		ft_free(total);
		total = NULL;
	}
	free_table(env);
	return (127);
}

int	ft_execve(t_big *v, char **argv)
{
	char	*path;
	char	**paths;

	if (!argv[0])
	{
		v->exit_status = 50;
		return (0);
	}
	path = return_env_content(v->env, "PATH");
	paths = ft_split((const char *)path, ':');
	if (!paths || paths[0] == NULL)
		exit_child(v, 1);
	path_creation_loop(v, argv, paths);
	free_table(paths);
	error_output(v, 'c', argv[0]);
	return (1);
}
