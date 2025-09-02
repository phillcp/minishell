/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:36 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/02 16:53:22 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utilities.h"
#include "minishell.h"
#include <readline/readline.h>

void	exit_child(t_big *v)
{
	close(2);
	close(1);
	close(0);
	free_data(v->cmd);
	exit_loop(v);
}

int	check_mask(char **pth)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while ((pth[0][++i]))
	{
		if (ft_isascii(pth[0][i] & 0x7F))
			j = 1;
	}
	if (j)
		unmask_str(*pth);
	return (j);
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

int	create_hdoc_and_pid_arrays(t_big *v)
{
	int	i;

	i = -1;
	v->hdoc_files = ft_calloc(sizeof(char *), (FD_MAX + 1));
	if (!v->hdoc_files)
		return (0);
	while (++i < FD_MAX)
	{
		v->hdoc_files[i] = ft_itoa(i);
		if (!v->hdoc_files)
			return (0);
	}
	v->hdoc_files[i] = NULL;
	v->pid_lst = ft_calloc(sizeof(int *), (CHILD_MAX + 1));
	if (!v->pid_lst)
		return (0);
	i = -1;
	while (++i < CHILD_MAX)
		v->pid_lst[i] = -1;
	v->pid_lst[i] = '\0';
	return (1);
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
