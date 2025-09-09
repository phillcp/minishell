/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:17:06 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/09 08:19:10 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"
#include "libft.h"

int	find_char(char **content, char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
	{
		ft_free(content[0]);
		return (0);
	}
	while (s[i] && s[i] != c)
		i++;
	if (s[i] != c)
	{
		ft_free(content[0]);
		return (0);
	}
	return (i);
}

void	free_set(t_big *v, char **content)
{
	ft_free(content[0]);
	ft_free(content[1]);
	v->exit_status = 0;
}

void	add_env(t_big *v, char **content)
{
	t_env	*tmp;

	tmp = new_env_node(content[0], content[1]);
	add_env_node(&v->env, tmp);
	v->exit_status = 0;
}
