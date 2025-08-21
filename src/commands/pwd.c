/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:55:46 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/21 16:27:03 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include "minishell.h"

int	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		return (-1);
	printf("%s\n", pwd);
	return (1);
}

int	ft_atoil(const char *s, int *j)
{
	int	neg;
	int	pos;
	int	result;

	neg = 1;
	pos = 0;
	result = 0;
	if (*s && *s == '"')
		s++;
	if (*s && *s == '-')
		neg *= -1;
	if (*s && *s == '-')
		s++;
	if (*s && *s == '+')
		pos = 1;
	if (*s && *s == '+')
		s++;
	if (*s && *s == '"')
		s++;
	if ((neg == -1 && pos == 1) || !ft_isdigit(*s))
		return (*j = 1);
	while (ft_isdigit(*s))
		result = result * 10 + (*s++ - '0');
	return (result * neg);
}

int	check_exit(t_big *v, char *argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (argv[i] == '+' || argv[i] == '-')
		i++;
	j = ft_strlen(argv);
	if (argv[i] == '"' || argv[j - 1] == '"')
		i++;
	while (argv[i] && (j && i < j - 1))
	{
		if (!ft_isdigit(argv[i]))
		{
			v->exit_ccode = 2;
			write(2, " numeric argument required\n", 27);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_exit(t_big *v, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
		i++;
	if (i > 2)
		return (v->exit_status = 1, write(2, " too many arguments\n", 20));
	else if (i == 2 && check_exit(v, argv[1]))
	{
		i = ft_atoil(argv[1], &j);
		if (j)
		{
			v->exit_status = 2;
			write(2, " numeric argument required\n", 27);
		}
		else
			v->exit_ccode = i;
	}
	v->exit = 1;
	printf("exit\n");
	return (1);
}
