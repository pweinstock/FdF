/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 10:15:13 by pweinsto          #+#    #+#             */
/*   Updated: 2021/09/04 19:26:42 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



t_isopoint	to_isometric(int x, int y, int z)
{
	t_isopoint	point;
	float	a = 0; //rechte seite kippen
	float	b = 0; //verdrehen
	float	c = 0.1; //hinten kippen
	
	point.ix = (cos(a) * cos(b) * x) + (((cos(a) * sin(b) * sin(c)) - (sin(a) * cos(c))) * y) + (((cos(a) * sin(b) * cos(c)) + (sin(a) * sin(c))) * z);
	point.iy = (sin(a) * cos(b) * x) + (((sin(a) * sin(b) * sin(c)) + (cos(a) * cos(c))) * y) + (((sin(a) * sin(b) * cos(c)) - (cos(a) * sin(c))) * z);
	point.iz = (-sin(b) * x) + (cos(b) * sin(c) * y) + (cos(b) * cos(c) * z);
	point.ix = ((sqrt(2) / 2) * point.ix) + ((sqrt(2) / 2 * -1) * point.iy);
	point.iy = ((sqrt(6) / 6) * point.ix) + ((sqrt(6) / 6) * point.iy) + ((sqrt(6) / 3 * -1) * point.iz);
	/*point.ix = (((sqrt(3) * (1 / sqrt(6))) * point.ix) + (((-sqrt(3)) * (1 / sqrt(6))) * point.iz));
	point.iy = ((point.ix * (1 / sqrt(6))) + ((2 * (1 / sqrt(6))) * point.iy) + ((1 / sqrt(6)) * point.iz));*/
	/*printf("x: %d\ny: %d\nz: %d\n", point.ix, point.iy, point.iz);*/
	return (point);
}

/*void	my_mlx_grid_put(t_isopoint point_old, t_isopoint point_new)
{

}*/

void	my_mlx_matrix_put(int ***matrix, t_data img)
{
	int	x;
	int	y;
	t_isopoint	point_old;
	t_isopoint	point_new;

	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x])
		{
			point_new = to_isometric(x*2, y*2, matrix[y][x][0]*2);
			my_mlx_pixel_put(&img, point_new.ix+960, point_new.iy+540, matrix[y][x][1]);
			/*if (x > 0)
				my_mlx_grid_put(point_old, point_new);*/
			x++;
			point_old = point_new;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		fd;
	int		***matrix;

	argc = 0;
	fd = open(argv[1], O_RDONLY);
	matrix = ft_read_data(fd);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_matrix_put(matrix, img);
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
