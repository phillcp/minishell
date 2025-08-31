/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:46 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 13:44:06 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "libft.h"

typedef struct s_big	t_big;

# define S 1
# define D 2
# define Q 4
# define V 8

typedef struct s_commands
{
	int		error;
	char	*line;
	t_tree	*tree;
}				t_commands;

typedef struct s_input
{
	t_list	*in;
	t_list	*input;
	t_list	*heredoc;
	t_list	*out;
	t_list	*output;
	t_list	*append;
}				t_input;

typedef struct s_cmd
{
	char	*line;
	char	**cmd;
	t_input	in;
}				t_cmd;

t_commands	*parse(t_big *v, const char *str);
void		aux(const char *str, int i, char *q);
t_commands	*assign_error(t_commands *cmd, int i);
void		in_q_dq_assign(bool *in_q_dq, bool *skip, int *count);
t_list		*init_list(int key, char *in_out, char c);
void		set_false(bool *in_q, bool *in_dq, bool *in_var, bool *skip);
char		*process_quotes(char *str, int count);
int			split_cmd(t_tree *t, char *c, int i);
int			parse_op(t_tree *t);
int			expand(t_big *v, t_tree *t);
int			word_split(t_tree *t);
int			expand_question(t_big *v, char **str, int start, int i);
int			unmask(t_tree *t);
void		free_command(t_commands *cmd);
int			unmask_str(char *str);
int			ft_isspecial(char s);
void		lstsort(t_list **l);
void		get_in(char *s, int *skp, int *i, char **in);

#endif
