/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 22:35:55 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/13 00:15:16 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int		parse_row_map(t_map *map, char *line, int row)
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
			return (-2);
		if (ft_c_is_in(line[i], "NSEW"))
			if (parse_player_location(map, line[i], row, i) < 0)
				return (-3);
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

int		parse_player_location(t_map *map, char c, int row, int column)
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

int		fill_columns(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map_grid[i] && i < map->n_row)
	{
		j = 0;
		while (map->map_grid[i][j])
			j++;
		if (j < map->n_column)
			map->map_grid[i] = ft_strjoin_n_free(map->map_grid[i],
			ft_calloc_char(map->n_column - j, ' '));
		i++;
	}
	return (check_lack_info(map));
}

int		is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (*line && line[i] == ' ')
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

int		is_identifier(char *line)
{
	if (ft_c_is_in(line[0], "RCFS") ||
		(line[0] == 'N' && line[1] == 'O') ||
		(line[0] == 'W' && line[1] == 'E') ||
		(line[0] == 'E' && line[1] == 'A') ||
		(line[0] == 'S' && line[1] == '0'))
		return (1);
	return (0);
}
