/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_mng.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:45 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/21 12:48:35 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utilities.h"
#include "minishell.h"

int	error_output(t_big *v, char type, char *str)
{
	if (type == 'c')
	{
		write (2, "minishell: command not found: ", 30);
		ft_putstr_fd(str, 2);
		write (2, "\n", 1);
		v->exit_status = 127;
	}
	else if (type == 's')
	{
		write (2, "minishell: special char not defined: ", 37);
		ft_putstr_fd(str, 2);
		write (2, "\n", 1);
		v->exit_status = 33;
	}
	else if (type == 'i' || type == 'd')
	{
		write (2, "minishell: ", 11);
		ft_putstr_fd(str, 2);
		write (2, ": No such file or directory\n", 28);
		v->exit_status = 1;
	}
	return (v->exit_status);
}

static int	output_loop(t_list *output, int output_file)
{
	char	*path;

	while (output)
	{
		if (output_file > 2)
			close(output_file);
		path = ft_substr((char *)output->content, 1,
				ft_strlen((char *)output->content));
		check_mask(&path);
		output_file = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH);
		output = output->next;
		ft_free(path);
	}
	return (output_file);
}

static int	append_loop(t_list *append, int output_file)
{
	char	*path;

	while (append)
	{
		if (output_file > 2)
			close(output_file);
		path = ft_substr((char *)append->content, 2,
				ft_strlen((char *)append->content));
		output_file = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		append = append->next;
		ft_free(path);
	}
	return (output_file);
}

static int	final_output_loop(t_list *final_output, int output_file)
{
	char	*path;

	while (final_output)
	{
		if (output_file > 2)
			close(output_file);
		if (!ft_strncmp(final_output->content, ">>", 2))
		{
			path = ft_substr((char *)final_output->content, 2,
					ft_strlen((char *)final_output->content));
			output_file = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (!ft_strncmp(final_output->content, ">", 1))
		{
			path = ft_substr((char *)final_output->content, 1,
					ft_strlen((char *)final_output->content));
			output_file = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		ft_free(path);
		final_output = final_output->next;
	}
	return (output_file);
}

int	file_output(t_list *output, t_list *append, t_list *final_output)
{
	int	output_file;

	output_file = 0;
	output_file = output_loop(output, output_file);
	output_file = append_loop(append, output_file);
	output_file = final_output_loop(final_output, output_file);
	return (output_file);
}
