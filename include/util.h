/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 19:18:42 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/12 02:22:12 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdlib.h>

size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dst, const void *src, int n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_isspace(int c);
int		ft_isdigit(int c);
void	*ft_calloc_char(size_t count, char c);
void	*ft_memset(void *b, int c, size_t len);
void	ft_swap(int *a, int *b);
char	*ft_strjoin_and_free(char *s1, char *s2);
void	*allocate_memory(int sizeof_type);
int		**allocate_buffer(int n_arrays, int n_elem);
void	clean_buffer(void **buffer, int n_arrays);

#endif
