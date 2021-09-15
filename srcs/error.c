/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:21:45 by pweinsto          #+#    #+#             */
/*   Updated: 2021/09/15 15:49:28 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(char *str)
{
	int	col;

	if (str[0] == 0)
		exit(1);
	col = ft_count_col(str);
	if (col == 1)
		exit(1);
	while (*str != '\n')
		str++;
	str++;
	while (*str)
	{
		if (ft_count_col(str) != col)
			exit (1);
		while (*str != '\n' && *str)
			str++;
		str++;
	}
}
