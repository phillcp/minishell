/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:36 by fheaton-          #+#    #+#             */
/*   Updated: 2025/06/23 15:32:26 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utilities.h"
#include "minishell.h"
#include "readline.h"

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

	free_dl_list(g_global.env);
	i = -1;
	while (++i < FD_MAX)
		ft_free(g_global.hdoc_files[i]);
	ft_free(g_global.hdoc_files);
	ft_free(g_global.pid_lst);
	ft_free(g_global.head);
	ft_free(g_global.temp_path);
	rl_clear_history();
	exit(0);
}
