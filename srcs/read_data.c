/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:13:37 by pweinsto          #+#    #+#             */
/*   Updated: 2021/09/11 20:56:24 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_hex_to_int(char c)
{
	int	i;
	char	*HEX;
	char	*hex;

	i = 0;
	HEX = "0123456789ABCDEF";
	hex = "0123456789abcdef";
	while (HEX[i])
	{
		if (HEX[i] == c || hex[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_get_color(char *str)
{
	int	sum;
	int	i;

	sum = 0;
	str = ft_strchr(str, 'x') + 1;
	i = ft_strlen(str) - 1;
	
	while (*str)
	{
		sum += ft_hex_to_int(*str) * pow(16, i);
		str++;
		i--;
	}
	return (sum);
}

void	ft_print_array(int *array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf("%d ", array[i]);
		i++;
	}
	printf("\n");
}

/*void	ft_print_matrix(int ****matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[0][i])
	{
		j = 0;
		while (matrix[0][i][j])
		{
			printf("y=%d,x=%d(%d,%d) ", i, j,matrix[0][i][j][0], matrix[0][i][j][1]);
			j++;
		}
		printf("\n");
		i++;
	}
}*/

int	ft_count_nl(char *str)
{
	int	lines;
	int	i;
	
	lines = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] != '\0')
			lines++;
		i++;
	}
	return (lines + 1);
}

int	ft_count_col(char *str)
{
	int	points;
	int	i;

	points = 1;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != '\n')
	{
		if (str[i] == ' ' && str[i + 1] != '\n')
		{
			points++;
			while (str[i + 1] == ' ')
				i++;
		}
		i++;
	}
	return (points);
}

char	*ft_fd_to_str(int fd)
{
	char	*str;
	char	*tmp;

	str = "";

	while (1)
	{
		tmp = get_next_line(fd, 501);
		if (!tmp)
			break;
		str = ft_strjoin(str, tmp);
		free(tmp);
		tmp = NULL;
	}
	return (str);
}

int	ft_str_to_matrix_2(t_transfer *transfer, char **columns, int i, int j)
{
	transfer->matrix[i][j] = (int *)ft_calloc(2, sizeof(int));
	(transfer->matrix)[i][j][0] = ft_atoi(columns[j]);
	if (ft_strchr(columns[j], 'x'))
		(transfer->matrix)[i][j][1] = ft_get_color(columns[j]);
	else
		(transfer->matrix)[i][j][1] = 16777215;
	if ((transfer->matrix)[i][j][0] > transfer->k)
		transfer->k = (transfer->matrix)[i][j][0];
	return (1);
}

int	ft_str_to_matrix_1(t_transfer *transfer, char *str, int col)
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
		(transfer->matrix)[i] = (int **)ft_calloc(col * 2, sizeof(int *));
		j = 0;
		while (columns[j])
		{
			if (!ft_str_to_matrix_2(transfer, columns, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_read_data(int fd, t_transfer *transfer)
{
	char	*str;
	int		nl;
	int		col;

	str = ft_fd_to_str(fd);
	/*if (ft_error(str))
		return (0);*/
	nl = ft_count_nl(str);
	col = ft_count_col(str);
	transfer->i = col / 2;
	transfer->j = nl /2;
	transfer->matrix = (int ***)ft_calloc(nl * col, sizeof(int **));
	ft_str_to_matrix_1(transfer, str, col);
}
