/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:52:41 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/11 14:10:31 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"
#include "utilities.h"
#include "libft.h"

static int	get_path_env(t_big *v, char *path, char **tmp_path)
{
	if (!path || !ft_strlen(path))
	{
		*tmp_path = get_env_value(v->env, "HOME");
		if (!tmp_path)
		{
			error_output(v, 'h', "HOME");
			return (0);
		}
		*tmp_path = ft_strdup(*tmp_path);
	}
	else if (!ft_strcmp(path, "-"));
	{
		*tmp_path = get_env_value(v->env, "OLDPWD");
		if (!tmp_path)
		{
			error_output(v, 'h', "OLDPWD");
			return (0);
		}
		*tmp_path = ft_strdup(*tmp_path);
	}
	return (1);
}

static	int	get_tmp_path(t_big *v, char *path, char *old_pwd, char **tmp_path)
{

	if (!getcwd(old_pwd, PATH_MAX))
	{
		perror("cd");
		return (0);
	}
	if (!path || !ft_strlen(path) || !ft_strcmp(path, "-"))
	{
		if (!get_path_env(v, path, tmp_path))
			return (0);
	}
	else
		*tmp_path = ft_strdup(path);
	if (!(*tmp_path) || !ft_strlen(*tmp_path))
		return (-1);
	return (1);
}

static int	change_dir(t_big *v, char *path, bool in_pipe)
{
	char	old_pwd[PATH_MAX];
	char	*tmp_path;
	int		ret;

	v->exit_status = 0;
	ret = get_tmp_path(v, path, old_pwd, &tmp_path);
	if (ret == 1 && !g_global.signal)
	{
		if (in_pipe)
		{
			ft_free(tmp_path);
			return (1);
		}
		ret = chdir(tmp_path);
		ft_free(tmp_path);
		if (ret >= 0)
		{
			if (check_env_key(v, "OLDPWD", old_pwd) == -1)
				return (-1);
			if (check_env_key(v, "PWD", getcwd(old_pwd, PATH_MAX)) == -1)
				return (-1);
		}
	}
	return (ret);
}

int	ft_cd(t_big *v, char **argv, bool in_pipe)
{
	int			ret;
	int			i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		v->exit_status = 1;
		return (1);
	}
	ret = change_dir(v, argv[1], in_pipe);
	if (ret == -1 && in_pipe)
		exit_child(v, 1);
	return (ret);
}
