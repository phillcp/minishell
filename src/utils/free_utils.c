/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:54 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/06 12:56:04 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	delete_tmpfiles(t_big *v, char *path)
{
	char	*file_path;
	char	*nbr;
	int		i;

	if (!path)
		return ;
	i = -1;
	while (++i < (v->hdoc_counter + 1))
	{
		nbr = ft_itoa(i);
		if (ft_strcmp(v->hdoc_files[i], nbr))
		{
			file_path = ft_strjoin(path, v->hdoc_files[i]);
			unlink(file_path);
			ft_free(file_path);
			ft_free(v->hdoc_files[i]);
			v->hdoc_files[i] = ft_itoa(i);
		}
		ft_free(nbr);
	}
}

void	free_dl_list_node(t_dl_list *lst)
{
	t_dl_list	*temp;

	if (!lst)
		return ;
	while (lst)
	{
		temp = lst->next;
		ft_free(lst->content);
		ft_free(lst->name);
		free(lst);
		lst = temp;
	}
}

void	free_env_arr(char **env_arr)
{
	int	i;

	i = -1;
	if (!env_arr)
		return ;
	while (env_arr[++i])
	{
		free(env_arr[i]);
		env_arr[i] = NULL;
	}
	free(env_arr);
	env_arr = NULL;
}
