/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 22:35:55 by vscabell          #+#    #+#             */
/*   Updated: 2020/07/24 21:07:11 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_char(t_map *map, int i, int j)
{
	if (i > 0 && i < (map->n_row - 1) && j > 0 && j < (map->n_column - 1))
	{
		if (!(ft_c_is_in(map->map_grid[i - 1][j - 1], "012")) ||
			!(ft_c_is_in(map->map_grid[i][j - 1], "012")) ||
			!(ft_c_is_in(map->map_grid[i + 1][j - 1], "012")) ||
			!(ft_c_is_in(map->map_grid[i - 1][j], "012")) ||
			!(ft_c_is_in(map->map_grid[i + 1][j], "012")) ||
			!(ft_c_is_in(map->map_grid[i - 1][j + 1], "012")) ||
			!(ft_c_is_in(map->map_grid[i][j + 1], "012")) ||
			!(ft_c_is_in(map->map_grid[i + 1][j + 1], "012")))
			return (FALSE);
	}
	return (TRUE);
}

int			validate_map(t_map *map)
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
			if ((map->map_grid[i][j] == '0' || map->map_grid[i][j] == '2') &&
			((i == 0 || j == 0 || i == map->n_row - 1 || j == map->n_column - 1)
			|| !check_char(map, i, j)))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

static int	parse_player_location(t_map *map, char c, int row, int column)
{
	if (map->init_posit != NULL)
		return (-1);
	map->init_posit = create_point(column, row, 0);
	map->init_posit->x = map->init_posit->x * TILE_SIZE + 1;
	map->init_posit->y = map->init_posit->y * TILE_SIZE + 1;
	map->rotation_angle = (c == 'N') ? NORTH : 0;
	map->rotation_angle = (c == 'S') ? SOUTH : map->rotation_angle;
	map->rotation_angle = (c == 'E') ? EAST : map->rotation_angle;
	map->rotation_angle = (c == 'W') ? WEST : map->rotation_angle;
	map->map_grid[row][column] = '0';
	return (0);
}

static int	parse_row_map(t_map *map, char *line, int row)
{
	int	i;
	int	find_player;

	map->map_grid[row] = line;
	find_player = FALSE;
	i = -1;
	while (line[++i])
	{
		map->map_grid[row][i] = line[i];
		if (!(ft_c_is_in(line[i], "NSEW 012")))
			return (-6);
		if (ft_c_is_in(line[i], "NSEW"))
			if (parse_player_location(map, line[i], row, i) < 0)
				return (-7);
		if (line[i] == '2')
		{
			map->sprite_posit = (t_point **)allocate_dynamic(
				(void **)map->sprite_posit, sizeof(t_point *), map->n_sprites);
			map->sprite_posit[map->n_sprites] = create_point(i, row, 0);
			map->n_sprites++;
		}
	}
	return (i);
}

int			get_map_info(t_map *map, char *line, int *row)
{
	int	n_col;
	int	i;

	i = *row;
	n_col = 0;
	map->map_grid = (char **)allocate_dynamic((void **)map->map_grid,
					sizeof(char *), i);
	if (!(n_col = parse_row_map(map, line, map->n_row)) || n_col < 0)
	{
		free(line);
		return (n_col);
	}
	map->n_column = n_col > map->n_column ? n_col : map->n_column;
	map->n_row++;
	i++;
	*row = i;
	return (n_col);
}
