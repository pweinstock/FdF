/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 10:15:13 by pweinsto          #+#    #+#             */
/*   Updated: 2021/09/15 16:06:33 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_matrix_put(t_s *s)
{
	int			x;
	int			y;
	t_isopoint	point_new;
	t_isopoint	point_old;

	y = 0;
	while ((s->matrix)[y])
	{
		x = 0;
		while ((s->matrix)[y][x])
		{
			point_new = to_isometric(x, y, s);
			if (x > 0)
				plot_line(point_old, point_new, s);
			if (y > 0)
				plot_line(to_isometric(x, y - 1, s), point_new, s);
			point_old = point_new;
			x++;
		}
		y++;
	}
}

void	init(t_s *s)
{
	s->zoom = 1;
	s->a = 0;
	s->b = 0;
	s->c = 0;
	s->x_shift = 960 - (s->i / 2);
	s->y_shift = 540 - (s->j / 2);
}

int	s_handler2(int keycode, t_s *s)
{
	if (keycode == 13 && s->c < 2147483647)
		s->c += 0.1;
	if (keycode == 1 && s->c > -2147483648)
		s->c -= 0.1;
	if (keycode == 0 && s->a > -2147483648)
		s->a -= 0.1;
	if (keycode == 2 && s->a < 2147483647)
		s->a += 0.1;
	if (keycode == 12 && s->b > -2147483648)
		s->b -= 0.1;
	if (keycode == 3 && s->b < 2147483647)
		s->b += 0.1;
	mlx_destroy_image(s->mlx, s->img);
	s->img = mlx_new_image(s->mlx, 1920, 1080);
	s->addr = mlx_get_data_addr(s->img, &(s->bpp), &(s->ll), &(s->endian));
	my_mlx_matrix_put(s);
	mlx_put_image_to_window(s->mlx, s->win, s->img, 0, 0);
	return (0);
}

int	s_handler1(int keycode, t_s *s)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 69 && s->zoom < 2147483647)
		s->zoom += 1;
	if (keycode == 78 && s->zoom > 1)
		s->zoom -= 1;
	if (keycode == 126 && s->y_shift > -2147483648 + 10)
		s->y_shift -= 10;
	if (keycode == 125 && s->y_shift < 2147483647 - 10)
		s->y_shift += 10;
	if (keycode == 123 && s->x_shift > -2147483648 + 10)
		s->x_shift -= 10;
	if (keycode == 124 && s->x_shift < 2147483647 - 10)
		s->x_shift += 10;
	return (s_handler2(keycode, s));
}

int	main(int argc, char **argv)
{
	int	fd;
	t_s	s;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	ft_read_data(fd, &s);
	init(&s);
	s.mlx = mlx_init();
	s.win = mlx_new_window(s.mlx, 1920, 1080, "FdF");
	s.img = mlx_new_image(s.mlx, 1920, 1080);
	s.addr = mlx_get_data_addr(s.img, &(s.bpp), &(s.ll), &(s.endian));
	my_mlx_matrix_put(&s);
	mlx_put_image_to_window(s.mlx, s.win, s.img, 0, 0);
	mlx_hook(s.win, 2, 1L << 0, s_handler1, &s);
	mlx_hook(s.win, 17, 1L << 17, close_window, &s);
	mlx_loop(s.mlx);
	free_matrix(&s);
	return (0);
}
