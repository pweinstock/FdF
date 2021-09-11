/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:14:08 by pweinsto          #+#    #+#             */
/*   Updated: 2021/09/11 16:22:28 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h> //delete this !!!
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include "../minilibx_macos/mlx.h"
# include "../includes/libft/libft.h"
# include "../includes/get_next_line/get_next_line.h"

/*typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;*/

typedef struct	s_isopoint
{
	int	ix;
	int	iy;
	int iz;
	int icolor;
}				t_isopoint;

/*typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;*/

typedef struct	s_transfer
{
	int	zoom;
	float	a;
	float	b;
	float	c;
	int	x_shift;
	int	y_shift;
	int		***matrix;
	void	*mlx;
	void	*win;
	//t_data	img;
	//t_vars	vars;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int	i;
	int	j;
	int	k;

}				t_transfer;

void	ft_read_data(int fd, t_transfer *transfer);
void	ft_print_matrix(int ****matrix);

#endif
