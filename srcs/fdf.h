/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:14:08 by pweinsto          #+#    #+#             */
/*   Updated: 2021/09/04 16:57:40 by pweinsto         ###   ########.fr       */
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

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_isopoint
{
	int	ix;
	int	iy;
	int iz;
}				t_isopoint;

typedef struct	s_matrix
{
	int	*x;
	int	*y;
	int	*z;
	int	*color;
}				t_matrix;

int	***ft_read_data(int fd);
void	ft_print_matrix(int ****matrix);

#endif
