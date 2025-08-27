/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:36 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/27 16:40:07 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utilities.h"
#include "minishell.h"
#include "readline.h"

void	exit_child(t_big *v)
{
	close(2);
	close(1);
	close(0);
	delete_temp(v, v->temp_path);
	free_command(v->cmd);
	exit_loop(v);
}

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

void	create_hdoc_and_pid_arrays(t_big *v)
{
	int	i;

	i = -1;
	v->hdoc_files = malloc(sizeof(char **) * (FD_MAX + 1));
	while (++i < FD_MAX)
		v->hdoc_files[i] = ft_itoa(i);
	v->hdoc_files[i] = NULL;
	v->pid_lst = malloc(sizeof(int *) * (CHILD_MAX + 1));
	i = -1;
	while (++i < CHILD_MAX)
		v->pid_lst[i] = -1;
	v->pid_lst[i] = '\0';
}

void	exit_loop(t_big *v)
{
	int	i;
	int	exit_ccode;

	exit_ccode = v->exit_ccode;
	if (!v->exit_ccode)
		exit_ccode = v->exit_status;
	free_dl_list(v->env);
	i = -1;
	while (++i < FD_MAX)
		ft_free(v->hdoc_files[i]);
	ft_free(v->hdoc_files);
	ft_free(v->pid_lst);
	ft_free(v->head);
	ft_free(v->temp_path);
	rl_clear_history();
	ft_free(v);
	exit(exit_ccode);
}
