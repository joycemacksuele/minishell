/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfreitas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:38:00 by jfreitas          #+#    #+#             */
/*   Updated: 2021/02/18 00:51:53 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** Libaries
*/
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>

/*
** Macros
*/
# define FD_MAX 256
# define MAX_FD 25

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif


/*
** structure bonus libft
*/
typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_listjb
{
	void			*content;
	struct s_listjb	*next;
}					t_listjb;


int					ft_atoi(char const *str);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, void const *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(void const*s1, void const *s2, size_t n);
void				*ft_memcpy(void *dst, void const *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, void const *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				*ft_realloc(void *ptr, size_t size);
char				*ft_strcat(char *s1, char const *s2);
char				*ft_strchr(char const *s, int c);
size_t				ft_strclen(char const *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(char const *s1, char const *s2);
char				*ft_strcpy(char *dest, char const *src);
void				ft_strdel(char **as);
char				*ft_strdup(char const *s1);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, char const *src, size_t size);
size_t				ft_strlen(char const *s);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, char const *s2, size_t n);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
char				*ft_strncpy(char *dest, char const *src, size_t len);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(char const *haystack, char const *needle, size_t len);
char				*ft_strrchr(char const *s, int c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(char const *haystack, char const *needle);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
int					ft_tolower(int c);
int					ft_toupper(int c);

int					get_next_line(int fd, char **line);
int					get_next_line_jb(int fd, char **line);
int					join_newstr(char **str, const char *src);

int					add_prime_sum(unsigned int n);
size_t				ft_intlen(int n);
int					ft_islower(int c);
int					ft_isupper(int c);
int					is_prime(unsigned int n);
unsigned int		lcm(unsigned int a, unsigned int b);

void				ft_putstr_list(t_list *str);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst,	void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

//lists jb
void				ft_lstadd_back_jb(t_listjb **alst, t_listjb *new);
void				ft_lstadd_front_jb(t_listjb **alst, t_listjb *new);
t_listjb			*ft_lstlast_jb(t_listjb *lst);
t_listjb			*ft_lstnew_jb(void *content);
int					ft_lstsize_jb(t_listjb *lst);
void				ft_lstiter_jb(t_listjb *lst, void (*f)(void *));
void				ft_lstclear_jb(t_listjb **lst, void (*del)(void *));
void				ft_lstdelone_jb(t_listjb *lst, void (*del)(void *));
t_listjb			*ft_lstmap_jb(t_listjb *lst, void *(*f)(void *),
		void (*del)(void *));

#endif
