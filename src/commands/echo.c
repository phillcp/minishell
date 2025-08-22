/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:53:55 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/22 08:51:18 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	echo_flag(char **argv, int i, int j, int k)
{
	if (i > k)
	{
		j = k;
		while (i > j)
		{
			printf("%s", argv[j]);
			if (i > 1 + j++)
				printf(" ");
		}
		if (k == 1)
			printf("\n");
	}
}

void	ft_echo(t_big *v, char **argv)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 1;
	while (argv[i])
		i++;
	if (i >= 2 && ft_strcmp(argv[1], "-n"))
		k = 2;
	echo_flag(argv, i, j, k);
	v->exit_status = 0;
}
