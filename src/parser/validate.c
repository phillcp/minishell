/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:06:42 by fiheaton          #+#    #+#             */
/*   Updated: 2025/08/31 20:24:58 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	skip_spaces(const char *line, int i)
{
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

static int	validate_check(const char *line, bool *in_q, bool *in_dq, int *i)
{
	if (line[*i] == '\'')
		*in_q = !*(in_q);
	if (line[*i] == '\"')
		*in_dq = !*(in_dq);
	if (*in_q || *in_dq)
		(*i)++;
	else if (line[*i] == '|')
	{
		(*i)++;
		*i = skip_spaces(line, *i);
		if (line[*i] == '\0')
			return (0);
		if (line[*i] == '|')
			return (0);
	}
	else
		(*i)++;
	return (1);
}

int	validate(const char *line)
{
	int		i;
	bool	in_q;
	bool	in_dq;

	i = 0;
	in_q = false;
	in_dq = false;
	i = skip_spaces(line, i);
	if (line[i] == '|')
		return (0);
	while (line[i])
	{
		if (!validate_check(line, &in_q, &in_dq, &i))
			return (0);
	}
	return (1);
}
