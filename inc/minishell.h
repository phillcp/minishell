/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:52 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/01 20:55:56 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "color.h"
# include "parser.h"

# ifndef CHILD_MAX
#  define CHILD_MAX 512
# endif

typedef struct s_cd
{
	t_dl_list	*tmp;
	char		*pwd;
	char		*path1;
	char		*path2;
	char		*backup;
}				t_cd;

typedef struct s_big
{
	char		*temp_path;
	int			exit;
	int			exit_status;
	int			exit_ccode;
	int			last_pipe;
	char		**hdoc_files;
	int			empty_str;
	int			hdoc_counter;
	int			pid_counter;
	int			*pid_lst;
	int			stdin_hdoc;
	t_cd		*cd;
	t_commands	*cmd;
	t_dl_list	*env;
	t_dl_list	*head;
}				t_big;

typedef struct	s_global
{
	int signal;
}				t_global;

extern t_global g_global;

#endif
