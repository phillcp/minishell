/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:51:55 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/21 15:58:09 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "parser.h"

//CD cmd functions
int		ft_cd(t_big *v, char **argv);

//Echo cmd functions
void	ft_echo(char **argv);

//Env cmd functions
void	ft_env(t_dl_list *env);

//Export cmd functions
int		ft_export(t_big *v, char **argv);

//Execve cmd functions
int		ft_execve(t_big *v, char **argv, int i);

//PWD and Exit cmd functions
int		ft_pwd(void);
int		ft_exit(t_big *v, char **argv);

//Signal functions
void	get_signal(int signal);

//Unset cmd functions
void	ft_unset(t_dl_list *env, char **argv, int i);

#endif
