/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:36 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/20 17:33:13 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utilities.h"
#include "minishell.h"
#include "readline.h"

void	check_mask(char **pth)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	while ((pth[0][++i] & 0x7F))
	{
		if (ft_isascii(pth[0][i]))
			j = 0;
	}
	if (j)
		unmask_str(*pth);
}

void	export_wrong(char *str)
{
	int	x;

	write(2, "export: '", 9);
	x = -1;
	while (str[++x] != 0)
		write(2, &str[x], 1);
	write(2, "': not a valid identifier\n", 26);
}

void	create_hdoc_and_pid_arrays(void)
{
	int	i;

	i = -1;
	g_global.hdoc_files = malloc(sizeof(char **) * (FD_MAX + 1));
	while (++i < FD_MAX)
		g_global.hdoc_files[i] = ft_itoa(i);
	g_global.hdoc_files[i] = NULL;
	g_global.pid_lst = malloc(sizeof(int *) * (CHILD_MAX + 1));
	i = -1;
	while (++i < CHILD_MAX)
		g_global.pid_lst[i] = -1;
	g_global.pid_lst[i] = '\0';
}

void	exit_loop(void)
{
	int	i;

	if (!g_global.exit_ccode)
	g_global.exit_ccode = g_global.exit_status;
	free_dl_list(g_global.env);
	i = -1;
	while (++i < FD_MAX)
		ft_free(g_global.hdoc_files[i]);
	ft_free(g_global.hdoc_files);
	ft_free(g_global.pid_lst);
	ft_free(g_global.head);
	ft_free(g_global.temp_path);
	rl_clear_history();
	exit(g_global.exit_ccode);
}
