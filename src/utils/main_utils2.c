/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:30 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/01 00:27:08 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utilities.h"
#include "parser.h"
#include <readline/readline.h>

void	exit_loop2(t_big *v)
{
	close(2);
	close(1);
	close(0);
	exit_loop(v);
}

void	save_std_fds(int *in, int *out)
{
	*in = dup(0);
	*out = dup(1);
}

void	restore_std_fds(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

static char	*expand_cmd2(t_big *v, char *s, int i)
{
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if ((s[i] & 0x7F) == '$')
		{
			if ((s[i + 1] & 0x7F) == '?')
				(expand_question(v, &s, i, 0));
			else
				(expand1(v, &s, i + 1));
		}
	}
	return (s);
}

int	go_read_lines(t_big *v, char *input, int output, char *eof_str)
{
	while (input && ft_strcmp(input, eof_str) != 1)
	{
		if (ft_strlen(input) > 0)
		{
			input = expand_cmd2(v, input, -1);
			if (!input)
				return (1);
			write(output, input, ft_strlen(input));
		}
		write(output, "\n", 1);
		ft_free(input);
		input = readline("heredoc> ");
	}
	return (0);
}
