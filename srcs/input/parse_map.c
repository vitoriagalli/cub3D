/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 22:35:55 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/06 20:15:56 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_row_map(t_map *map, char *line, int row)
{
	int	i;
	int	find_player;

	map->map_grid[row] = line;
	i = 0;
	find_player = FALSE;
	while (line[i])
	{
		if (line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
		&& line[i] != ' ' && line[i] != '0' && line[i] != '1')
			return (0);
		map->map_grid[row][i] = line[i];
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' ||
		line[i] == 'W')
		{
			if (parse_player_location(map, line[i], row, i) < 0)
				return (-1);
		}
		i++;
	}
	return (i);
}

int		parse_player_location(t_map *map, char c, int row, int column)
{
	if (map->init_posit != NULL)
		return (-1);
	if (c == 'N')
	{
		map->init_posit = create_point(column, row, 0);
		map->rotation_angle = NORTH;
	}
	else if (c == 'S')
	{
		map->init_posit = create_point(column, row, 0);
		map->rotation_angle = SOUTH;
	}
	else if (c == 'E')
	{
		map->init_posit = create_point(column, row, 0);
		map->rotation_angle = EAST;
	}
	else if (c == 'W')
	{
		map->init_posit = create_point(column, row, 0);
		map->rotation_angle = WEST;
	}
	map->map_grid[row][column] = '0';
	return (0);
}

void	fill_columns(t_map *map)
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
			map->map_grid[i] = ft_strjoin_and_free(map->map_grid[i],
			ft_calloc_char(map->n_column - j, ' '));
		i++;
	}
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
	if (line[0] == 'R' || line[0] == 'C' || line[0] == 'F' || line[0] == 'S' ||
	(line[0] == 'N' && line[1] == 'O') || (line[0] == 'W' && line[1] == 'E') ||
	(line[0] == 'E' && line[1] == 'A') || (line[0] == 'S' && line[1] == '0'))
		return (1);
	return (0);
}
