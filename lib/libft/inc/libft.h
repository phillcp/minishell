/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:40:32 by fporto            #+#    #+#             */
/*   Updated: 2022/11/28 13:04:59 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <string.h>

# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_tree
{
	void			*content;
	int				lcount;
	struct s_tree	**leaves;
}				t_tree;

typedef struct s_dl_list
{
	void				*content;
	void				*name;
	struct s_dl_list	*prev;
	struct s_dl_list	*next;
}						t_dl_list;

/*
*	double_linked_list
*/

t_dl_list		*ft_lstnew_dl(char **content);
void			ft_lstadd_back_dl(t_dl_list **lst, t_dl_list *new);
t_dl_list		*ft_lstlast_dl(t_dl_list *lst);
void			*ft_listget_dl(const char *key, t_dl_list *l);
t_dl_list		*ft_lsthead_dl(t_dl_list *lst);
void			ft_lstprint(t_dl_list *lst, char type);
void			ft_lstnode_print(t_dl_list *lst, char *name);
void			ft_lstnode_print_dl(t_dl_list *lst);
t_dl_list		*ft_lstdup_dl(t_dl_list *lst);

/*
*	tree
*/
t_tree			*ft_treenew(void *content);
int				ft_treeadd(t_tree *tree, void *content);
int				ft_treeclear(t_tree *t, void (*del)(void *));

int				ft_atoi(const char *s);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isblank(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_realloc(void *ptr, size_t osize, size_t nsize);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s1);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
int				ft_strichr(const char *str, const char c);
char			*ft_strstr(const char *haystack, const char *needle);
int				ft_tolower(int c);
int				ft_toupper(int c);

char			*ft_itoa(long n);
char			*ft_uitoa(unsigned int n);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);

void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);

void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
					void (*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);

int				ft_abs(int n);
char			*ft_strcat_char(char *str, char c);
char			*ft_char_to_str(char c);
int				ft_isstrdigit(char *str);
void			ft_free(void *ptr);

#endif
