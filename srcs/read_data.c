/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:13:37 by pweinsto          #+#    #+#             */
/*   Updated: 2021/08/28 20:23:42 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*int	ft_count_nl(char *str)
{
	int	lines;
	
	lines = 0;
	while (*str)
	{
		if (*str == '\n')
			lines++;
		str++;
	}
	return (lines);
}

int	ft_count_col(char *str)
{
	int	points;

	points = 1;

	while (*str)
	{
		if (*str == ' ')
		{
			points++;
		}
		str++;
	}
	return (points);
}*/

char	*ft_fd_to_str(int fd)
{
	char	*str;
	char	*tmp;

	str = "";
	while (1)
	{
		tmp = get_next_line(fd, 1);
		if (!tmp)
			break;
		str = ft_strjoin(str, tmp);
		free(tmp);
		tmp = NULL;
	}
	return (str);
}

t_matrix	ft_str_to_matrix(char *str)
{
	t_matrix	matrix;
	char	**lines;
	char	**columns;
	/*int		x[nl * col];
	int		y[nl * col];
	int		z[nl * col];
	int		color[nl * col];*/
	int		i;
	int		j;

	i = 0;
	lines = ft_split(str, '\n');
	while (lines[i])
	{
		printf("line%d: %s\n", i, lines[i]);
		columns = ft_split(lines[i], ' ');
		j = 0;
		while (columns[j])
		{
			printf("%s ", columns[j]);
			j++;
		}
		printf("\n");
		i++;
	}
	/*i = 0;
	j = 0;
	while (i < nl)
	{
		columns = ft_split((lines)[i], ' ');
		while (j < col)
		{
			x = ft_create_point((columns)[j]);
			j++;
		}
		i++;
	}*/
	matrix.color = 0;
	return (matrix);
}

int	ft_read_data(int fd)
{
	char	*str;
	//int		nl;
	//int		col;
	t_matrix	matrix;

	str = ft_fd_to_str(fd);
	/*if (ft_error(str))
		return (0);*/
	//nl = ft_count_nl(str);
	//col = ft_count_col(str);
	matrix = ft_str_to_matrix(str);
	printf("%s\n", str);
	//printf("nl: %d\ncol: %d\n", nl, col);
	return (0);
}
