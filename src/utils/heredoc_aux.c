/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 12:39:21 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/09 08:29:59 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input(t_big *v, t_redir *cur, char **input)
{
	char	*tmp;

	if (cur->expand)
	{
		tmp = expand_word(v, *input);
		if (!tmp)
			return (0);
		(*input) = tmp;
	}
	return (1);
}

char	*temp_path(char *tmp, char *path)
{
	char	*filename;

	if (!tmp)
		return (NULL);
	filename = ft_strjoin(path, tmp);
	free(tmp);
	if (!filename)
		return (NULL);
	return (filename);
}

void	signal_hdoc(int signal)
{
	(void)signal;
	g_global.signal = 1;
	close(0);
}

char	*hdoc_filename(t_big *v, char *eof)
{
	char	*i;
	char	*filename;

	i = ft_itoa(++v->hdoc_counter);
	if (!i)
		return (NULL);
	filename = ft_strjoin(eof, i);
	ft_free(i);
	if (!filename)
		return (NULL);
	return (filename);
}
