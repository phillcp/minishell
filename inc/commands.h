/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:51:55 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/11 11:36:32 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "parser.h"

int		ft_cd(t_big *v, char **argv, bool in_pipe);

void	ft_echo(t_big *v, char **argv);

void	ft_env(t_big *v, t_env *env, char **argv);

int		ft_exit(t_big *v, char **argv, bool in_pipe);

void	free_set(t_big *v, char **content);
int		check_print_env_export(t_big *v, char **argv, bool in_pipe);
int		ft_export(t_big *v, char **argv, bool in_pipe);

int		ft_pwd(t_big *v);

void	ft_unset(t_big *v, t_env **head, char **argv, bool in_pipe);

char	*path_creation(t_big *v, char *path, char *cmd);
char	**temp_env_arr(t_big *v);
int		ft_execve(t_big *v, char **argv);

#endif
