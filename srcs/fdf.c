/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 10:15:13 by pweinsto          #+#    #+#             */
/*   Updated: 2021/09/11 18:15:00 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_transfer *transfer, int x, int y, int color)
{
	char	*dst;

	dst = transfer->addr + (y * transfer->line_length + x * (transfer->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_isopoint	to_isometric(int x, int y, int z, int color, t_transfer *transfer)
{
	t_isopoint	point;
	float	a; //rechte seite kippen
	float	b; //verdrehen
	float	c; //hinten kippen
	
	a = transfer->a;
	b = transfer->b;
	c = transfer->c;
	point.icolor = color;
	x -= transfer->i;
	y -= transfer->j;
	//z -= transfer->k;
	x *= transfer->zoom;
	y *= transfer->zoom;
	z *= transfer->zoom;
	point.ix = (cos(a) * cos(b) * x) + (((cos(a) * sin(b) * sin(c)) - (sin(a) * cos(c))) * y) + (((cos(a) * sin(b) * cos(c)) + (sin(a) * sin(c))) * z);
	point.iy = (sin(a) * cos(b) * x) + (((sin(a) * sin(b) * sin(c)) + (cos(a) * cos(c))) * y) + (((sin(a) * sin(b) * cos(c)) - (cos(a) * sin(c))) * z);
	point.iz = (-sin(b) * x) + (cos(b) * sin(c) * y) + (cos(b) * cos(c) * z);
	point.ix += transfer->i;
	point.iy += transfer->j;
	//point.iz += transfer->k;
	point.ix += transfer->x_shift;
	point.iy += transfer->y_shift;
	/*point.ix = ((sqrt(2) / 2) * point.ix) + ((sqrt(2) / 2 * -1) * point.iy);
	point.iy = ((sqrt(6) / 6) * point.ix) + ((sqrt(6) / 6) * point.iy) + ((sqrt(6) / 3 * -1) * point.iz);*/
	return (point);
}

int	calc_color(t_isopoint point_old, t_isopoint point_new, int y)
{
	int	dy;
	int	dcolor;
	int	color_step;

	dy = sqrt(pow(point_new.ix - point_old.ix, 2) + pow(point_new.iy - point_old.iy, 2)); //abs(point_new.iy - point_old.iy);
	dcolor = abs(point_new.icolor - point_old.icolor);
	if (dcolor == 0 || dy == 0)
		return (point_new.icolor);
	color_step = dcolor / dy;
	/*if (point_new.iy > point_old.iy && point_new.icolor < point_old.icolor)
		return (point_new.icolor + (color_step * (y - point_new.iy)));*/
	/*else if (point_new.iz > point_old.iz && point_new.icolor > point_old.icolor)*/
		return (point_new.icolor - (color_step * (y - point_new.iy)));
	//else if (point_new.iz < point_old.iz && point_new.icolor > point_old.icolor)
	// 	return (point_new.icolor - (color_step * (y - point_new.iy)));
	// else /*if (point_new.iy < point_old.iy && point_new.icolor < point_old.icolor)*/
	// 	return (point_new.icolor + (color_step * (y - point_new.iy)));
}

void	plot_line (t_isopoint point_old, t_isopoint point_new, t_transfer *transfer)
{
	int x0 = point_old.ix;
	int y0 = point_old.iy;
	int x1 = point_new.ix;
	int y1 = point_new.iy;
	int dx;
	int dy; 
	int err;
	int	sx;
	int	sy;
	int	e2;

	dx =  abs (x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs (y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = dx + dy; /* error value e_xy */
 
	while (1)
	{  /* loop */
		if (x0/*+transfer->x_shift*/ < 1920 && x0/*+transfer->x_shift*/ > 0 && y0/*+transfer->y_shift*/ < 1080 && y0/*+transfer->y_shift*/ > 0)
			my_mlx_pixel_put(transfer, x0/*+transfer->x_shift*/, y0/*+transfer->y_shift*/, calc_color(point_old, point_new, y0));
		//setPixel (x0,y0);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		} /* e_xy+e_x > 0 */
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		} /* e_xy+e_y < 0 */
	}
}

// int	y_len(t_transfer *transfer)
// {
// 	int	i;

// 	i = 0;
// 	while ((transfer->matrix)[i])
// 		i++;
// 	return (i);
// }

// int	x_len(t_transfer *transfer)
// {
// 	int	i;

// 	i = 0;
// 	while ((transfer->(*matrix))[i])
// 		i++;
// 	return (i);
// }

void	my_mlx_matrix_put(/*int ***matrix, t_data img,*/ t_transfer *transfer)
{
	int	x;
	int	y;
	// int	xl;
	// int	yl;
	t_isopoint	point_new;
	t_isopoint	point_old;

	// yl = y_len(transfer);
	// xl = x_len(transfer);
	y = 0;
	while ((transfer->matrix)[y])
	{
		x = 0;
		while ((transfer->matrix)[y][x])
		{
			point_new = to_isometric(x, y, (transfer->matrix)[y][x][0], (transfer->matrix)[y][x][1], transfer);
			
			// if (point_new.ix+960 < 1920 && point_new.ix+960 > 0 && point_new.iy < 1080 && point_new.iy > 0)
			// 	my_mlx_pixel_put(&img, point_new.ix+960, point_new.iy, point_new.icolor);
			if (x > 0)
				plot_line(point_old, point_new, transfer);
			if (y > 0)
				plot_line(to_isometric(x, (y-1), (transfer->matrix)[y-1][x][0], (transfer->matrix)[y-1][x][1], transfer), point_new, transfer);
			point_old = point_new;
			if ((transfer->matrix)[y][x][0] > transfer->k)
				transfer->k = (transfer->matrix)[y][x][0];
			x++;
		}
		y++;
	}
}	

void init(t_transfer *transfer)
{
	transfer->zoom = 1;
	transfer->a = 0;
	transfer->b = 0;
	transfer->c = 0;
	transfer->x_shift = 960 - (transfer->i / 2);
	transfer->y_shift = 540 - (transfer->j / 2);
}

int	transfer_handler(int keycode, t_transfer *transfer)
{
	if (keycode == 53)
		exit(0);
		//mlx_destroy_window(transfer->mlx, transfer->win);
	if (keycode == 69)
		transfer->zoom += 1;
	if (keycode == 78 && transfer->zoom > 0)
		transfer->zoom -= 1;
	if (keycode == 126)
		transfer->y_shift -= 10;
	if (keycode == 125)
		transfer->y_shift += 10;
	if (keycode == 123)
		transfer->x_shift -= 10;
	if (keycode == 124)
		transfer->x_shift += 10;
	if (keycode == 13)
		transfer->c += 0.1;
	if (keycode == 1)
		transfer->c -= 0.1;
	if (keycode == 0)
		transfer->a -= 0.1;
	if (keycode == 2)
		transfer->a += 0.1;
	if (keycode == 12)
		transfer->b -= 0.1;
	if (keycode == 3)
		transfer->b += 0.1;
	//printf("c: %d\n", transfer->c);
	//mlx_clear_window(transfer->vars.mlx, transfer->vars.win);
	mlx_destroy_image(transfer->mlx, transfer->img);
	transfer->img = mlx_new_image(transfer->mlx, 1920, 1080);
	transfer->addr = mlx_get_data_addr(transfer->img, &(transfer->bits_per_pixel), &(transfer->line_length),
								&(transfer->endian) );
	my_mlx_matrix_put(transfer);
	mlx_put_image_to_window(transfer->mlx, transfer->win, transfer->img, 0, 0);
	return (0);
}

/*int	ft_close(int keycode, t_transfer *transfer)
{
	 
	if (keycode == 53)
		mlx_destroy_window(transfer->mlx, transfer->win);
	return (0);
}*/

int	main(int argc, char **argv)
{
	//t_data	img;
	int		fd;
	//int		***matrix;
	//t_vars	vars;
	t_transfer	transfer;

	argc = 0;
	fd = open(argv[1], O_RDONLY);
	ft_read_data(fd, &transfer);
	init(&transfer);
	transfer.mlx = mlx_init();
	transfer.win = mlx_new_window(transfer.mlx, 1920, 1080, "Hello world!");
	transfer.img = mlx_new_image(transfer.mlx, 1920, 1080);
	transfer.addr = mlx_get_data_addr(transfer.img, &(transfer.bits_per_pixel), &(transfer.line_length),
								&(transfer.endian));
	my_mlx_matrix_put(&transfer);
	mlx_put_image_to_window(transfer.mlx, transfer.win, transfer.img, 0, 0);
	// sleep(30);
	// mlx_destroy_image(transfer.mlx, transfer.img);
	// transfer.img = mlx_new_image(transfer.mlx, 1920, 1080);
	// transfer.addr = mlx_get_data_addr(transfer.img, &(transfer.bits_per_pixel), &(transfer.line_length),
	// 							&(transfer.endian));
	// transfer.x_shift += 500;
	// my_mlx_matrix_put(&transfer);
	// mlx_put_image_to_window(transfer.mlx, transfer.win, transfer.img, 0, 0);
	mlx_hook(transfer.win, 2, 1L<<0, transfer_handler, &transfer);
	//mlx_hook(transfer.win, 2, 1L<<0, ft_close, &transfer);
	mlx_loop(transfer.mlx);
	return (0);
}
