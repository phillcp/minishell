/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:28:07 by fporto            #+#    #+#             */
/*   Updated: 2025/08/14 16:43:20 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# define FD_MAX 4096

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>

int		get_next_line(int fd, char **line);
int		save_lines(char **lineread, char *buffer, char **line, \
ssize_t nreadbytes);

#endif
