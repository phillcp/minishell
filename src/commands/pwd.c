/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:55:46 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/21 11:04:40 by fheaton-         ###   ########.fr       */
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
	exit(0);
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

int	check_exit(char *argv)
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
			g_global.exit_ccode = 2;
			write(2, " numeric argument required\n", 27);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_exit(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (argv[2] && argv[2][0] != '\0')
	{
		g_global.exit_status = 1;
		write(2, " too many arguments\n", 20);
		return ;
	}
	g_global.exit = 1;
	if (argv[1] && check_exit(argv[1]))
	{
		i = ft_atoil(argv[1], &j);
		if (j)
		{
			g_global.exit_status = 2;
			write(2, " numeric argument required\n", 27);
		}
		else
			g_global.exit_ccode = i;
	}
	printf("exit\n");
}
