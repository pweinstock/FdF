/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:13:37 by pweinsto          #+#    #+#             */
/*   Updated: 2021/09/15 15:01:13 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_fd_to_str(int fd)
{
	char	*str;
	char	*tmp;

	str = "";
	while (1)
	{
		tmp = get_next_line(fd, 501);
		if (!tmp)
			break ;
		str = ft_strjoin(str, tmp);
		free(tmp);
		tmp = NULL;
	}
	return (str);
}

int	ft_str_to_matrix_2(t_s *s, char **columns, int i, int j)
{
	s->matrix[i][j] = (int *)ft_calloc(2, sizeof(int));
	if (!s->matrix[i][j])
		exit(1);
	(s->matrix)[i][j][0] = ft_atoi(columns[j]);
	if (ft_strchr(columns[j], 'x'))
		(s->matrix)[i][j][1] = ft_get_color(columns[j]);
	else
		(s->matrix)[i][j][1] = 16777215;
	if ((s->matrix)[i][j][0] > s->k)
		s->k = (s->matrix)[i][j][0];
	return (1);
}

int	ft_str_to_matrix_1(t_s *s, char *str, int col)
{
	char	**lines;
	char	**columns;
	int		i;
	int		j;

	i = 0;
	lines = ft_split(str, '\n');
	while (lines[i])
	{
		columns = ft_split(lines[i], ' ');
		(s->matrix)[i] = (int **)ft_calloc(col * 2, sizeof(int *));
		if (!(s->matrix)[i])
			exit(1);
		j = 0;
		while (columns[j])
		{
			if (!ft_str_to_matrix_2(s, columns, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_read_data(int fd, t_s *s)
{
	char	*str;
	int		nl;
	int		col;

	str = ft_fd_to_str(fd);
	if (str[0] == 0)
		exit(1);
	error(str);
	nl = ft_count_nl(str);
	col = ft_count_col(str);
	s->i = col / 2;
	s->j = nl / 2;
	s->matrix = (int ***)ft_calloc(nl * col, sizeof(int **));
	if (!s->matrix)
		exit(1);
	ft_str_to_matrix_1(s, str, col);
}
