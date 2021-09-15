/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:15:43 by pweinsto          #+#    #+#             */
/*   Updated: 2021/09/15 14:50:42 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_hex_to_int(char c)
{
	int		i;
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
	while (str[i] != '\n' && str[i])
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
