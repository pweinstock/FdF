/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:28:15 by pweinsto          #+#    #+#             */
/*   Updated: 2021/08/25 11:38:44 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd, int BUFFER_SIZE);
size_t	gft_strlen(const char *str);
char	*gft_strjoin(char *s1, char *s2);
char	*gft_strdup(const char *s1);
void	gft_bzero(void *s, size_t n);
int		gft_memmove(char *dst, char *src);
void	*gft_calloc(size_t count, size_t size);
char	*ft_readnjoin(int fd, char *buff, char *temp, int BUFFER_SIZE);
char	*ft_process(char *temp);
int		ft_empty(char *temp);

#endif