/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:27:43 by pweinsto          #+#    #+#             */
/*   Updated: 2021/08/26 16:38:24 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	gft_bzero(ptr, count * size);
	return (ptr);
}

char	*ft_readnjoin(int fd, char *buff, char *temp, int BUFFER_SIZE)
{
	int	check;
	int	rt;
	int	i;

	rt = 0;
	check = 0;
	while (check == 0)
	{
		rt = read(fd, buff, BUFFER_SIZE);
		if (rt <= 0)
			break ;
		temp = gft_strjoin(temp, buff);
		i = 0;
		while (buff[i])
		{
			if (buff[i] == '\n')
				check = 1;
			i++;
		}
		gft_bzero(buff, BUFFER_SIZE + 1);
	}
	free(buff);
	return (temp);
}

int	ft_empty(char *temp)
{
	if (temp[0] == 0)
	{
		free(temp);
		return (1);
	}
	else
		return (0);
}

char	*ft_process(char *temp)
{
	int		nlpos;
	char	*line;

	nlpos = 0;
	while (temp[nlpos] != 0)
	{	
		if (temp[nlpos] == '\n' )
		{
			line = gft_strdup(temp);
			gft_memmove(temp, temp + nlpos + 1);
			return (line);
		}
		nlpos++;
	}
	return (0);
}

char	*get_next_line(int fd, int BUFFER_SIZE)
{
	char			*buff;
	static char		*temp;
	char			*line;
	static int		static_check;

	if (static_check == 1 || fd < 0 || BUFFER_SIZE < 1)
		return (0);
	if (!temp)
		temp = (char *)gft_calloc(BUFFER_SIZE, sizeof(char));
	buff = (char *)gft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp || !buff)
		return (0);
	temp = ft_readnjoin(fd, buff, temp, BUFFER_SIZE);
	if (ft_empty(temp) == 1)
	{
		temp = 0;
		return (0);
	}
	line = ft_process(temp);
	if (line)
		return (line);
	static_check = 1;
	line = gft_strdup(temp);
	free(temp);
	return (line);
}
