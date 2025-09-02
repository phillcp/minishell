/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:40 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/02 12:27:07 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "libft.h"

# include "parser.h"

# define CHAR_UNHANDLED 1
# define QUOTES_OPEN 2
# define MAX_FD 256

int			error_output(t_big *v, char type, char *str);
void		err_i(t_big *v, char *str);
void		err_c(t_big *v, char *str);
void		exit_child(t_big *v);
void		exit_loop2(t_big *v, int init);
void		signal_hdoc(int signal);

int			check_env_names(t_big *v, char *name, char *content);
void		print_env_content(t_dl_list *lst, char *name, char free_name);
char		*return_env_content(t_dl_list *lst, char *name);
char		*get_name(char *str, char c);
t_dl_list	*get_env(t_big *v, char **env);

void		free_list_nodes(t_dl_list *lst);
void		free_dl_list(t_dl_list *lst);
void		delete_temp(t_big *v, char *path);
void		free_table(char **table);

void		signal_handler(int signal);
void		clean_processes(t_big *v);
void		re_init(t_big *v);
int			create_hdoc_and_pid_arrays(t_big *v);
int			save_hdoc_for_del(t_big *v, t_tree *t);
void		exit_loop(t_big *v);
void		save_std_fds(int *in, int *out);
void		restore_std_fds(int in, int out);
int			go_read_lines(t_big *v, char *input, int output, char *eof_str);
void		print_env_export(t_dl_list	*env);
void		hdoc_call_extra(t_big *v, t_cmd *cmd, char *filename);
int			ft_strisspace(char *str);
void		input_loop_extra(t_big *v, t_commands *cmd);
char		*hdoc_filename(t_big *v, char *eof);

int			file_input(t_big *v, t_list *input, t_list *heredoc, t_list *in);
void		file_input_instruction(t_big *v, t_cmd *cmd);
int			builtin_input_i(t_big *v, t_cmd *cmd);
int			file_output(t_big *v, t_list *output, t_list *append,
				t_list *final_output);
void		file_output_instruction(t_big *v, t_cmd *cmd);
int			builtin_output_i(t_big *v, t_cmd *cmd);

int			screening_one(t_big *v, char **argv);
void		cmd_selector(t_big *v, char **argv);
int			builtin(t_big *v, t_cmd *cmd);
int			cmd_identifier(char **argv);

char		*temp_path(char *filename, char *path);
void		check_heredoc(t_big *v, t_tree *t);
void		export_wrong(char *str);
int			check_mask(char **pth);

#endif
