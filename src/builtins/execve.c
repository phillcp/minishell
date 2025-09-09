/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:54:28 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/09 15:01:39 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"
#include "commands.h"
#include <signal.h>
#include "libft.h"

static int	execve_loop(t_big *v, char **argv, char **path)
{
	char	**env_arr;
	char	*total;
	int		i;

	i = -1;
	env_arr = temp_env_arr(v);
	if (!env_arr)
		return (-1);
	while (path[++i])
	{
		total = path_creation(v, path[i], argv[0]);
		if (!total)
			return (free_str_arr(env_arr), -1);
		execve(total, argv, env_arr);
		ft_free(total);
		total = NULL;
	}
	free_str_arr(env_arr);
	return (0);
}

void	execve_absolute_path(t_big *v, char **argv)
{
	char	**env_arr;

	if (ft_strchr(argv[0], '/'))
	{
		env_arr = temp_env_arr(v);
		if (!env_arr)
			exit_child(v, 1);
		execve(argv[0], argv, env_arr);
		free_str_arr(env_arr);
	}
	v->exit_status = 127;
	exit_child(v, 0);
}

int	ft_execve(t_big *v, char **argv)
{
	char	*path;
	char	**paths;
	int		check;

	if (!argv[0])
	{
		v->exit_status = 127;
		return (0);
	}
	path = get_env_value(v->env, "PATH");
	if (!path)
		execve_absolute_path(v, argv);
	paths = ft_split(path, ':');
	if (!paths || paths[0] == NULL)
		exit_child(v, 1);
	check = execve_loop(v, argv, paths);
	free_str_arr(paths);
	if (check)
		exit_child(v, 1);
	v->exit_status = 127;
	return (1);
}
