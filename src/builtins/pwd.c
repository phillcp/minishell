/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:55:46 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/12 12:56:54 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include "minishell.h"
#include "utilities.h"

void	ft_pwd(t_big *v)
{
	char	pwd[PATH_MAX];

	if (g_signal)
		return ;
	if (v->pwd)
		printf("%s\n", v->pwd);
	else
	{
		if (!getcwd(pwd, PATH_MAX))
		{
			perror("pwd");
			v->exit_status = 1;
			return ;
		}
		printf("%s\n", pwd);
	}
	v->exit_status = 0;
}
