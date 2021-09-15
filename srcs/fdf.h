/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:14:08 by pweinsto          #+#    #+#             */
/*   Updated: 2021/09/15 15:49:48 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include "../minilibx_macos/mlx.h"
# include "../includes/libft/libft.h"
# include "../includes/get_next_line/get_next_line.h"

typedef struct s_isopoint
{
	int	ix;
	int	iy;
	int	icolor;
}				t_isopoint;

typedef struct s_s
{
	int		zoom;
	float	a;
	float	b;
	float	c;
	int		x_shift;
	int		y_shift;
	int		***matrix;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		i;
	int		j;
	int		k;
	int		dx;
	int		dy;
	int		err;
	int		sx;
	int		sy;
	int		e2;
	int		x0;
	int		y0;
	int		x1;
	int		y1;

}				t_s;

//fdf.c
int			s_handler1(int keycode, t_s *s);
int			s_handler2(int keycode, t_s *s);
void		init(t_s *s);
void		my_mlx_matrix_put(t_s *s);

//plot_object.c
void		plot_line(t_isopoint point_old, t_isopoint point_new, t_s *s);
void		plot_line_loop(t_isopoint point_old, t_isopoint point_new, t_s *s);
int			calc_color(t_isopoint point_old, t_isopoint point_new, int y);
t_isopoint	to_isometric(int x, int y, t_s *s);
void		my_mlx_pixel_put(t_s *s, int color);

//read_data.c
void		ft_read_data(int fd, t_s *s);
int			ft_str_to_matrix_1(t_s *s, char *str, int col);
int			ft_str_to_matrix_2(t_s *s, char **columns, int i, int j);
char		*ft_fd_to_str(int fd);

//read_data_utils.c
int			ft_count_col(char *str);
int			ft_count_nl(char *str);
int			ft_get_color(char *str);
int			ft_hex_to_int(char c);

//free.c
void		free_matrix(t_s *s);
int			close_window(void);

//error.c
void		error(char *str);

#endif
