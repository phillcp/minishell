/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:20 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/09 15:57:00 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"

static t_parse	*assign_error(t_parse *parse, int i)
{
	if (i != 0)
		parse->error = i;
	return (parse);
}

t_parse	*parse(t_big *v, const char *str)
{
	t_parse	*parse;

	if (ft_strisspace(str))
		return (NULL);
	parse = ft_calloc(1, sizeof(t_parse));
	if (!parse)
		return (NULL);
	if (!validate(str))
		return (assign_error(parse, 1));
	if (!make_tokens(parse, str))
		return (assign_error(parse, 2));
	if (!expand_tokens(parse, v))
		return (assign_error(parse, 3));
	parse->cmds = parse_cmd(parse->tokens);
	if (!parse->cmds)
		return (assign_error(parse, 4));
	return (parse);
}
