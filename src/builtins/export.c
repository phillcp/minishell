/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:54:56 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/09 08:22:42 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"
#include "commands.h"
#include "libft.h"

static void	print_env_export(t_env	*env)
{
	t_env	*cur;

	if (!env)
		return ;
	cur = env;
	sort_env(env);
	while (cur)
	{
		printf("declare -x ");
		printf("%s", (char *)cur->key);
		printf("=");
		printf("\"%s\"\n", (char *)cur->content);
		cur = cur->next;
	}
}

int	check_print_env_export(t_big *v, char **argv, bool in_pipe)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		print_env_export(v->env);
		v->exit_status = 0;
		return (1);
	}
	if (i > 1 && in_pipe == true)
		return (1);
	return (0);
}

static char	*get_key(char *str, char c)
{
	char	*name;
	int		i;

	i = -1;
	if (!str || !str[0] || str[0] == '=')
		return (NULL);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (NULL);
	while (str[++i] && str[i] != c)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (NULL);
	}
	name = ft_calloc((i + 1), sizeof(char));
	if (!ft_strlcpy(name, str, i + 1))
		return (NULL);
	return (name);
}

int	ft_export(t_big *v, char **av, bool in_pipe)
{
	char	*arr[2];
	int		check;

	if (check_print_env_export(v, av, in_pipe))
		return (1);
	arr[0] = get_key(av[1], '=');
	if (!arr[0])
	{
		export_wrong(v, av[0]);
		return (-1);
	}
	check = find_char(arr, av[1], '=');
	if (!check)
		return (-1);
	arr[1] = ft_substr(av[1], check + 1, ft_strlen(av[1]));
	if (!arr[1])
	{
		ft_free(arr[0]);
		return (-1);
	}
	if (check_env_key(v, arr[0], arr[1]))
		free_set(v, arr);
	else
		add_env(v, arr);
	return (1);
}
