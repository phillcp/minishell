/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:06:42 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/15 18:19:37 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utilities.h"
#include <signal.h>
#include <readline/readline.h>

static int	skip_spaces(char *line, int i)
{
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

static int	check_in_out(char *line, int *i)
{
	(*i)++;
	if (line[*i] == line[(*i) - 1])
		i++;
	*i = skip_spaces(line, *i);
	if (line[*i] == '\0' || line[*i] == '|')
		return (0);
	if (line[*i] == '<' || line[*i] == '>')
		return (0);
	return (1);
}

static int	check_pipe(t_big *v, char **line, int *i)
{
	(*i)++;
	*i = skip_spaces(*line, *i);
	if ((*line)[*i] == '|')
		return (0);
	if ((*line)[*i] == '\0')
		if (!read_last_pipe(v, line))
			return (0);
	return (1);
}

int	validate(t_big *v, char **line)
{
	int		i;
	bool	in_q;
	bool	in_dq;

	i = 0;
	in_q = false;
	in_dq = false;
	i = skip_spaces(*line, i);
	if ((*line)[i] == '|')
		return (0);
	while ((*line)[i])
	{
		handle_quotes((*line)[i], &in_q, &in_dq);
		if (!in_q && !in_dq && (*line)[i] == '|')
		{
			if (!check_pipe(v, line, &i))
				return (0);
		}
		else if (!(in_q) && !(in_dq) && ((*line)[i] == '<' || (*line)[i] == '>'))
		{
			if (!check_in_out(*line, &i))
				return (0);
		}
		i++;
	}
	return (1);
}
