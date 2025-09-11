/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:55:46 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/11 13:48:46 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include "minishell.h"
#include "utilities.h"

int	ft_pwd(t_big *v)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
	{
		perror("pwd");
		return (0);
	}
	if (!g_global.signal)
		printf("%s\n", pwd);
	v->exit_status = 0;
	return (1);
}
