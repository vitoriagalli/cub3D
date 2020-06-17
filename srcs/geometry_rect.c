/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_rect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 03:11:15 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/14 23:08:22 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rectangle(t_data *img, t_point point, int width, int height)
{
	int x;
	int y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			my_mlx_pixel_put(img, point.x + x, point.y + y, point.color);
			y++;
		}
		x++;
	}
}
