/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:38 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/13 02:15:11 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	allocate_map(t_vars *vars)
{
	vars->map = allocate_memory(sizeof(t_map));
	vars->map->init_posit = NULL;
	vars->map->color = allocate_memory(sizeof(t_color));
	vars->map->color->ceilling = -1;
	vars->map->color->ceilling = -1;
	vars->map->path = allocate_memory(sizeof(char *) * 5);
	vars->map->path[north] = NULL;
	vars->map->path[south] = NULL;
	vars->map->path[east] = NULL;
	vars->map->path[west] = NULL;
	vars->map->path[sprite] = NULL;
	vars->map->init_posit = NULL;
	vars->map->sprite_posit = NULL;
	vars->map->map_grid = NULL;
	vars->map->n_sprites = 0;
	vars->map->width = 0;
	vars->map->height = 0;
	vars->map->n_row = 0;
	vars->map->n_column = 0;
	vars->mlx = NULL;
}

int		read_file(char *file, t_map *map)
{
	char	*line;
	int		fd;
	int		ismap;
	int		i;
	int		ret;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (ft_error(map, -1));
	ismap = FALSE;
	i = 0;
	while ((get_next_line(fd, &line)))
	{
		if (line[0] == ' ' || line[0] == '1')
		{
			ismap = TRUE;
			ret = get_map_info(map, line, &i);
			if (ret < 0)
			{
				free(line);
				return (ft_error(map, ret));
			}
		}
		else if (is_identifier(line) && !ismap)
			get_identifier(map, line);
		else if (!(is_empty_line(line)) || (is_empty_line(line) && ismap))
		{
			free(line);
			return (ft_error(map, -4));
		}
		else
			free(line);
	}
	free(line);
	return (fill_columns(map));
}

int		get_map_info(t_map *map, char *line, int *row)
{
	int	n_col;
	int	i;

	i = *row;
	n_col = 0;
	map->map_grid = (char **)allocate_dynamic((void **)map->map_grid,
					sizeof(char *), i);
	if (!(n_col = parse_row_map(map, line, map->n_row)) || n_col < 0)
		return (n_col);
	map->n_column = n_col > map->n_column ? n_col : map->n_column;
	map->n_row++;
	i++;
	*row = i;
	return (n_col);
}
