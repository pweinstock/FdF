/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:06:15 by pweinsto          #+#    #+#             */
/*   Updated: 2021/09/15 11:04:11 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_s *s, int color)
{
	char	*dst;

	dst = s->addr + (s->y0 * s->ll + s->x0 * (s->bpp / 8));
	*(unsigned int *)dst = color;
}

t_isopoint	to_isometric(int x, int y, t_s *s)
{
	t_isopoint	point;
	float		a;
	float		b;
	float		c;
	int			z;

	a = s->a;
	b = s->b;
	c = s->c;
	point.icolor = (s->matrix)[y][x][1];
	z = ((s->matrix)[y][x][0]) * s->zoom;
	x = (x - s->i) * s->zoom;
	y = (y - s->i) * s->zoom;
	point.ix = (cos(a) * cos(b) * x);
	point.ix += (((cos(a) * sin(b) * sin(c)) - (sin(a) * cos(c))) * y);
	point.ix += (((cos(a) * sin(b) * cos(c)) + (sin(a) * sin(c))) * z);
	point.iy = (sin(a) * cos(b) * x);
	point.iy += (((sin(a) * sin(b) * sin(c)) + (cos(a) * cos(c))) * y);
	point.iy += (((sin(a) * sin(b) * cos(c)) - (cos(a) * sin(c))) * z);
	point.ix += s->i;
	point.iy += s->j;
	point.ix += s->x_shift;
	point.iy += s->y_shift;
	return (point);
}

int	calc_color(t_isopoint point_old, t_isopoint point_new, int y)
{
	int	dy;
	int	dcolor;
	int	color_step;

	dy = pow(point_new.ix - point_old.ix, 2);
	dy += pow(point_new.iy - point_old.iy, 2);
	dy = sqrt(dy);
	dcolor = abs(point_new.icolor - point_old.icolor);
	if (dcolor == 0 || dy == 0)
		return (point_new.icolor);
	color_step = dcolor / dy;
	return (point_new.icolor - (color_step * (y - point_new.iy)));
}

void	plot_line_loop(t_isopoint point_old, t_isopoint point_new, t_s *s)
{
	while (1)
	{
		if (s->x0 < 1920 && s->x0 >= 0 && s->y0 < 1080 && s->y0 >= 0)
			my_mlx_pixel_put(s, calc_color(point_old, point_new, s->y0));
		if (s->x0 == s->x1 && s->y0 == s->y1)
			break ;
		s->e2 = 2 * s->err;
		if (s->e2 >= s->dy)
		{
			s->err += s->dy;
			s->x0 += s->sx;
		}
		if (s->e2 <= s->dx)
		{
			s->err += s->dx;
			s->y0 += s->sy;
		}
	}
}

void	plot_line(t_isopoint point_old, t_isopoint point_new, t_s *s)
{
	s->x0 = point_old.ix;
	s->y0 = point_old.iy;
	s->x1 = point_new.ix;
	s->y1 = point_new.iy;
	s->dx = abs(s->x1 - s->x0);
	if (s->x0 < s->x1)
		s->sx = 1;
	else
		s->sx = -1;
	s->dy = -abs (s->y1 - s->y0);
	if (s->y0 < s->y1)
		s->sy = 1;
	else
		s->sy = -1;
	s->err = s->dx + s->dy;
	plot_line_loop(point_old, point_new, s);
}
