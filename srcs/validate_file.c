/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 06:53:34 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/05 06:21:58 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(t_map *map)
{
	if (!map->width || !map->height || map->color->ceilling < 0 ||
	map->color->floor < 0 || !map->path[north] || !*map->path[north] ||
	!map->path[south] || !*map->path[south] || !map->path[east] ||
	!*map->path[east] || !map->path[west] || !*map->path[west] ||
	!map->n_column || !map->n_row || !map->init_posit)
		return(free_map(map));
	return(1);
}

int	free_map(t_map *map)
{
	if (map->map_grid)
		clean_buffer_char(map->map_grid, map->n_row);
	if (map->init_posit)
		free(map->init_posit);
	// if (map->init_posit->x)
	// 	free(map->init_posit->y);
	clean_buffer_char(map->path, 4);
	free(map->color);
	free(map);
	return (0);
}
