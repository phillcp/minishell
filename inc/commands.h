/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:51:55 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/06 09:19:14 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "parser.h"

int		ft_cd(t_big *v, char **argv);
void	ft_echo(t_big *v, char **argv);
void	ft_env(t_big *v, t_dl_list *env, char **argv);
int		ft_export(t_big *v, char **argv, bool in_pipe);
int		ft_execve(t_big *v, char **argv);
int		ft_pwd(t_big *v);
int		ft_exit(t_big *v, char **argv);
void	ft_unset(t_big *v, t_dl_list *env, char **argv, int i);

#endif
