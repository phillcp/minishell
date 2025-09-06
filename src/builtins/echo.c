/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:53:55 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/05 21:29:15 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	print_echo(char **argv, int i, int check)
{
	int	j;

	j = 0;
	if (check)
		j = 1;
	while (argv[++j])
	{
		printf("%s", argv[j]);
		if (i > j)
			printf(" ");
	}
	if (!check)
		printf("\n");
}

static int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	if (str[i] != 'n')
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

void	ft_echo(t_big *v, char **argv)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (argv[i])
		i++;
	if (i >= 2 && check_n(argv[1]))
		check = 1;
	print_echo(argv, i, check);
	v->exit_status = 0;
}
