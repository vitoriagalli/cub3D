/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 22:35:55 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/06 07:25:37 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		*parse_path(char *path)
{
	int i;

	i = 0;
	if (!path[i])
		return (NULL);
	while (ft_isspace(path[i]))
		i++;
	if (path[i])
		return(ft_strdup(&path[i]));			//retorna /0 caso nao tenha o path
	return(NULL);
}

int			parse_color(char *str)
{
	int	nb[3];
	int	n;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str[i])
		return (0);			// nao tiver cor no arquivo
	while (str[i] && j < 3)
	{
		while (ft_isspace(str[i]))
			i++;
		if (!ft_isdigit(str[i]))
			return (-1);
		n = str[i] - '0';
		i++;
		while (ft_isdigit(str[i]))
		{
			n = 10 * n + (str[i] - '0');
			i++;
		}
		nb[j] = n;
		j++;
		i += (str[i] == ',') ? 1 : 0;
	}
	if (nb[0] > 255 || nb[1] > 255 || nb[2] > 255 || i < 2 ||
	(str[i] != ' ' && str[i] != '\0'))
		return (-1);
	return (ft_rgb(nb[0], nb[1], nb[2]));
}

void		parse_resolution(char *str, t_map *map)
{
	int	nb[2];
	int	n;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str[i])
		return ;			// nao tiver cor no arquivo
	while (str[i] && j < 2)
	{
		while (ft_isspace(str[i]))
			i++;
		if (!ft_isdigit(str[i]))
			return ;
		n = str[i] - '0';
		i++;
		while (ft_isdigit(str[i]))
		{
			n = 10 * n + (str[i] - '0');
			i++;
		}
		nb[j] = n;
		j++;
	}
	if (i < 2 || (str[i] != ' ' && str[i] != '\0'))
		return ;
	map->width = nb[0];
	map->height = nb[1];
}

int		parse_row_map(t_map *map, char *line, int row)
{
	int i;
	int	find_player;

	map->map_grid[row] = line;

	i = 0;
	find_player = FALSE;
	while (line[i])
	{
		if (line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
		&& line[i] != ' ' && line[i] != '0' && line[i]!= '1')
			return(0);
		map->map_grid[row][i] = line[i];
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			if (parse_player_location(map, line[i], row, i) < 0)
				return (-1);
		}
		i++;
	}
	return (i);
}

int	parse_player_location(t_map *map, char c, int row, int column)
{
	if (map->init_posit != NULL)
		return (-1) ;
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

int			is_identifier(char *line)
{
	if (line[0] == 'R' || line[0] == 'C' || line[0] == 'F' || line[0] == 'S' ||
	(line[0] == 'N' && line[1] == 'O') || (line[0] == 'W' && line[1] == 'E') ||
	(line[0] == 'E' && line[1] == 'A') || (line[0] == 'S' && line[1] == '0'))
			return (1);
	return (0);
}

int			is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (*line && line[i] == ' ')
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}
