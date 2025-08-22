/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:12 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/22 14:56:29 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utilities.h"
#include "minishell.h"

static int	heredoc_loop(t_big *v, t_list *heredoc, int input_hdoc)
{
	char	*pth;
	char	*i;
	int		fd;

	while (heredoc)
	{
		if (input_hdoc > 2)
			close(input_hdoc);
		i = ft_itoa(++v->hdoc_counter);
		pth = heredoc->content;
		pth = temp_path(pth, v->temp_path);
		fd = open(pth, O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			error_output(v, 'i', heredoc->content);
			ft_free(pth);
			return (-1);
		}
		input_hdoc = fd;
		ft_free(i);
		ft_free(pth);
		heredoc = heredoc->next;
	}
	return (input_hdoc);
}

static int	input_loop(t_big *v, t_list *input, int input_file)
{
	char	*pth;
	char	*content;
	int		fd;

	while (input)
	{
		if (input_file > 2)
			close(input_file);
		content = (char *)input->content;
		pth = ft_substr(content, 1, ft_strlen(content) - 1);
		check_mask(&pth);
		fd = open(pth, O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			error_output(v, 'i', input->content + 1);
			ft_free(pth);
			return (-1);
		}
		input_file = fd;
		ft_free(pth);
		input = input->next;
	}
	return (input_file);
}

int	file_input(t_big *v, t_list *input, t_list *heredoc, t_list *in)
{
	int		input_file;
	int		input_hdoc;

	input_file = 0;
	input_hdoc = 0;
	input_file = input_loop(v, input, input_file);
	input_hdoc = heredoc_loop(v, heredoc, input_hdoc);
	if (!ft_strncmp(in->content, "<<", 2))
	{
		if (input_file > 2)
			close(input_file);
		return (input_hdoc);
	}
	if (input_hdoc > 2)
		close(input_hdoc);
	return (input_file);
}

void	file_input_instruction(t_big *v, t_cmd *cmd)
{
	int	fd;

	fd = 0;
	if (!cmd->in.in)
		return ;
	fd = file_input(v, cmd->in.input, cmd->in.heredoc, cmd->in.in);
	if (fd < 0)
		exit(v->exit_status);
	dup2(fd, 0);
	close(fd);
}

int	builtin_input_i(t_big *v, t_cmd *cmd)
{
	int	fd;

	fd = 0;
	if (!cmd->in.in)
		return (1);
	fd = file_input(v, cmd->in.input, cmd->in.heredoc, cmd->in.in);
	if (fd < 0 || !cmd->in.in)
		return (0);
	dup2(fd, 0);
	close(fd);
	return (1);
}
