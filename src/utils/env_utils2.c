/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:25:20 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/11 11:19:42 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "minishell.h"
#include "utilities.h"

static int	set_lvl(int lvl)
{
	if (lvl < 0)
		lvl = 0;
	if (lvl > 1000)
		lvl = 1;
	else
		lvl++;
	return (lvl);
}

static int	update_shlvl(t_big *v)
{
	t_env	*tmp;
	char	*tmp_lvl;
	int		lvl;

	tmp_lvl = get_env_value(v->env, "SHLVL");
	if (!tmp_lvl)
	{
		tmp = new_env_node(ft_strdup("SHLVL"), ft_strdup("1"));
		if (!tmp)
			return (0);
		add_env_node(&v->env, tmp);
		return (1);
	}
	lvl = set_lvl(ft_atoi(tmp_lvl));
	tmp_lvl = ft_itoa(lvl);
	if (!tmp_lvl)
		return (0);
	if (check_env_key(v, "SHLVL", tmp_lvl) < 0)
	{
		free(tmp_lvl);
		return (0);
	}
	free(tmp_lvl);
	return (1);
}

int	manual_env(t_big *v)
{
	char	cwd[PATH_MAX];
	char	*pwd;
	t_env	*tmp;

	if (getcwd(cwd, PATH_MAX))
		pwd = ft_strdup(cwd);
	else
		pwd = ft_strdup("");
	if (!pwd)
		return (0);
	tmp = new_env_node(ft_strdup("PWD"), pwd);
	if (!tmp)
		return (0);
	add_env_node(&v->env, tmp);
	if (!update_shlvl(v))
		return (0);
	return (1);
}

int	get_env(t_big *v, char **envp)
{
	t_env	*new_env;
	char	*key;
	char	*content;
	int		aux;
	int		i;

	if (!envp[0])
	{
		v->env = NULL;
		return (1);
	}
	i = -1;
	while (envp[++i])
	{
		aux = ft_strichr(envp[i], '=');
		key = ft_substr(envp[i], 0, aux);
		content = ft_substr(envp[i], aux + 1, ft_strlen(envp[i]) - aux);
		new_env = new_env_node(key, content);
		if (!new_env)
			return (0);
		add_env_node(&v->env, new_env);
	}
	if (!update_shlvl(v))
		return (0);
	return (1);
}

int	check_env_key(t_big *v, char *key, char *content)
{
	t_env	*cur;
	char	*tmp;

	if (!v->env || !content)
		return (0);
	cur = v->env;
	while (cur)
	{
		if (!ft_strcmp(key, cur->key))
		{
			tmp = ft_strdup(content);
			if (!tmp)
				return (-1);
			ft_free(cur->content);
			cur->content = tmp;
			cur = v->env;
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}
