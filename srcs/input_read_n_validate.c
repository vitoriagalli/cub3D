/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read_n_validate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 06:53:34 by vscabell          #+#    #+#             */
/*   Updated: 2020/07/09 20:47:30 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (*line && line[i] == ' ')
		i++;
	if (line[i] != '\0')
	{
		free(line);
		return (0);
	}
	free(line);
	return (1);
}

static int	is_identifier(char *line)
{
	if (ft_c_is_in(line[0], "RCFS") ||
		(line[0] == 'N' && line[1] == 'O') ||
		(line[0] == 'W' && line[1] == 'E') ||
		(line[0] == 'E' && line[1] == 'A') ||
		(line[0] == 'S' && line[1] == '0'))
		return (1);
	return (0);
}

static int	check_lack_info(t_map *map)
{
	if (!(validate_map(map)))
		return (ft_error(map, -9));
	else if (!map->n_column || !map->n_row)
		return (ft_error(map, -10));
	else if (!map->width || !map->height)
		return (ft_error(map, -11));
	else if (map->color->ceilling < 0 || map->color->floor < 0)
		return (ft_error(map, -12));
	else if (!map->path[north] || !*map->path[north] || !map->path[south] ||
			!*map->path[south] || !map->path[east] || !*map->path[east] ||
			!map->path[west] || !*map->path[west] || !map->path[sprite] ||
			!*map->path[sprite])
		return (ft_error(map, -13));
	else if (!map->sprite_posit)
		return (ft_error(map, -14));
	else if (!map->init_posit)
		return (ft_error(map, -15));
	return (1);
}

static int	fill_columns(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->n_row && map->map_grid[i])
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

int			read_file(char *file, t_map *map)
{
	char	*line;
	int		fd;
	int		ismap;
	int		i;
	int		ret;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (ft_error(map, -5));
	ismap = FALSE;
	i = 0;
	while ((get_next_line(fd, &line)))
	{
		if (line[0] == ' ' || line[0] == '1')
		{
			ismap = TRUE;
			if ((ret = get_map_info(map, line, &i)) < 0)
				return (ft_error(map, ret));
		}
		else if (is_identifier(line) && !ismap)
			get_identifier(map, line);
		else if ((ismap && is_empty_line(line)) || !(is_empty_line(line)))
			return (ft_error(map, -8));
	}
	free(line);
	return (fill_columns(map));
}
