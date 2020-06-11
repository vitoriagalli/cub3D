/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 06:53:34 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/09 16:19:31 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(t_map *map)
{
	if (!map->width || !map->height || map->color->ceilling < 0 ||
	map->color->floor < 0 || !map->path[north] || !*map->path[north] ||
	!map->path[south] || !*map->path[south] || !map->path[east] ||
	!*map->path[east] || !map->path[west] || !*map->path[west] ||
	!map->path[sprite] || !*map->path[sprite] || !map->sprite_posit ||
	!map->n_column || !map->n_row || !map->init_posit)
		return (free_map(map));
	else if (!(validate_map(map)))
		return (free_map(map));
	return (1);
}

int	free_map(t_map *map)
{
	if (map->map_grid)
		clean_buffer((void **)map->map_grid, map->n_row);
	if (map->init_posit)
		free(map->init_posit);
	clean_buffer((void **)map->path, 4);
	free(map->color);
	free(map);
	return (0);
}

int	ft_valid_char(char c)
{
	if (c == '0' || c == '1' || c == '2')
		return (1);
	return (0);
}

int	check_char(t_map *map, int i, int j)
{
	if (i > 0 && i < (map->n_row - 1) && j > 0 && j < (map->n_column - 1))
	{
		if (!(ft_valid_char(map->map_grid[i - 1][j - 1])) ||
			!(ft_valid_char(map->map_grid[i][j - 1])) ||
			!(ft_valid_char(map->map_grid[i + 1][j - 1])) ||
			!(ft_valid_char(map->map_grid[i - 1][j])) ||
			!(ft_valid_char(map->map_grid[i + 1][j])) ||
			!(ft_valid_char(map->map_grid[i - 1][j + 1])) ||
			!(ft_valid_char(map->map_grid[i][j + 1])) ||
			!(ft_valid_char(map->map_grid[i + 1][j + 1])))
			return (0);
	}
	return (1);
}

int	validate_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->n_row)
	{
		j = 0;
		while (j < map->n_column)
		{
			if (map->map_grid[i][j] == '0' && (i == 0 || j == 0 ||
			i == map->n_row - 1 || j == map->n_column - 1))
				return (0);
			else if (map->map_grid[i][j] == '0')
				if (!check_char(map, i, j))
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}
