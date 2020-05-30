/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 16:39:57 by vscabell          #+#    #+#             */
/*   Updated: 2020/05/30 17:40:29 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	do_projection(t_data *img, float *rays)
{
	int		i;
	t_point	*p0;
	float	dist_proj_plane;
	float	wall_proj_height;

	p0 = create_point(0, 0, 0xFFcccccc);
	dist_proj_plane = (WIDTH / 2) / (tan(FOV / 2));
	i = 0;
	while (i < NUM_RAYS)
	{
		wall_proj_height = (TILE_SIZE / rays[i]) * dist_proj_plane;
		assign_point(p0, i * WALL_WIDTH, (HEIGHT / 2) - (wall_proj_height / 2), p0->color);

		ft_rectangle(img, *p0, WALL_WIDTH, wall_proj_height);
		i++;
	}
	free(rays);
	free(p0);
}
