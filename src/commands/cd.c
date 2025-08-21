/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:52:41 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/21 16:49:37 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"
#include "utilities.h"
#include "libft.h"

static int	change_directory(t_big *v, t_dl_list *head, char *path)
{
	char	old_pwd[PATH_MAX];
	char	*tmp_path;
	int		ret;

	if (!getcwd(old_pwd, PATH_MAX))
		return (-1);
	if (path == NULL || ft_strcmp(path, "~") || !ft_strlen(path))
		tmp_path = ft_strdup(return_env_content(v->env, "HOME"));
	else if (path[0] == '~')
		tmp_path = ft_strjoin(return_env_content(v->env, "HOME"), path + 1);
	else if (ft_strcmp(path, "-"))
		tmp_path = ft_strdup(return_env_content(v->env, "OLDPWD"));
	else
		tmp_path = ft_strdup(path);
	ret = chdir(tmp_path);
	v->env = head;
	if (ret >= 0)
	{
		check_env_names(v, "PWD", tmp_path);
		check_env_names(v, "OLDPWD", tmp_path);
	}
	ft_free(tmp_path);
	return (ret);
}

int	ft_cd(t_big *v, char **argv)
{
	t_dl_list	*head;
	int			ret;
	int			i;

	head = v->env;
	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		v->exit_status = 1;
		return (-1);
	}
	ret = change_directory(v, head, argv[1]);
	if (ret < 0)
		error_output(v, 'd', argv[1]);
	return (ret);
}
