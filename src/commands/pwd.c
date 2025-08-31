/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:55:46 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/01 00:15:10 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include "minishell.h"

int	ft_pwd(t_big *v)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		return (-1);
	printf("%s\n", pwd);
	v->exit_status = 0;
	return (1);
}

long long	ft_atoil(const char *s, int *j)
{
	int			neg;
	int			pos;
	long long	result;

	neg = 1;
	pos = 0;
	result = 0;
	if (*s && *s == '-')
		neg *= -1;
	if (*s && *s == '-')
		s++;
	if (*s && *s == '+')
		pos = 1;
	if (*s && *s == '+')
		s++;
	if ((neg == -1 && pos == 1) || !ft_isdigit(*s))
		return (*j = 1);
	while (ft_isdigit(*s))
		result = result * 10 + (*s++ - '0');
	if (result < 0)
		return (*j = 1);
	return (result * neg);
}

static void	err_exit(t_big *v, char *argv)
{
	v->exit_status = 2;
	v->exit_ccode = 0;
	write(2, "minishell: exit: ", 17);
	ft_putstr_fd(argv, 2);
	write(2, ": numeric argument required\n", 28);
}

int	check_exit(t_big *v, char *argv)
{
	int	i;
	int	j;

	i = 0;
	if (argv[i] == '+' || argv[i] == '-')
		i++;
	j = ft_strlen(argv);
	if (j > 19)
	{
		err_exit(v, argv);
		return (0);
	}
	while (argv[i] && (j && i < j - 1))
	{
		if (!ft_isdigit(argv[i]))
		{
			err_exit(v, argv);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_exit(t_big *v, char **argv)
{
	long long	i;
	int			j;

	i = 0;
	j = 0;
	while (argv[i])
		i++;
	if (i > 2)
		return (v->exit_status = 1, write(2, " too many arguments\n", 20));
	printf("exit\n");
	if (i == 2 && check_exit(v, argv[1]))
	{
		i = ft_atoil(argv[1], &j);
		if (j)
			err_exit(v, argv[1]);
		else
			v->exit_ccode = i;
	}
	v->exit = 1;
	return (1);
}
