/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:32:21 by pweinsto          #+#    #+#             */
/*   Updated: 2021/09/15 11:04:08 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_matrix(t_s *s)
{
	int	i;
	int	j;

	j = 0;
	while ((s->matrix)[j])
	{
		i = 0;
		while ((s->matrix)[j][i])
		{
			free((s->matrix)[j][i]);
			i++;
		}
		free((s->matrix)[j]);
		j++;
	}
	free(s->matrix);
}

int	close_window(void)
{
	exit(0);
}
