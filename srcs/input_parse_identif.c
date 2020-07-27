/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse_identif.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 20:06:06 by vscabell          #+#    #+#             */
/*   Updated: 2020/07/27 03:04:05 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*parse_path(char *path)
{
	int i;

	i = 0;
	if (!path[i])
		return (ft_strdup("\0"));
	while (ft_isspace(path[i]))
		i++;
	if (path[i])
		return (ft_strdup(&path[i]));
	return (NULL);
}

static int	get_additive_color(char *str, int i, int *num)
{
	int n;

	n = 0;
	if (str[i])
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
	}
	*num = n;
	return (i);
}

static int	parse_color(char *str)
{
	int	nb[3];
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str[i])
		return (-2);
	while (str[i] && j < 3)
	{
		i = get_additive_color(&str[0], i, &nb[j]);
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == ',' && j < 2)
			i++;
		else if (str[i] != '\0')
			return (-1);
		j++;
	}
	if (nb[0] > 255 || nb[1] > 255 || nb[2] > 255 || j < 3 || str[i] != '\0')
		return (-1);
	return ((nb[0] << 16 | nb[1] << 8 | nb[2]));
}

static void	parse_resolution(char *str, t_map *map)
{
	int		nb[2];
	int		i;
	int		j;

	i = 0;
	j = 0;
	map->width = -1;
	if (!str)
		return ;
	while (str[i] && j < 2)
	{
		i = get_additive_color(&str[0], i, &nb[j]);
		j++;
	}
	if (j < 2 || str[i] != '\0')
		return ;
	map->width = nb[0];
	map->height = nb[1];
}

int			get_identifier(t_map *map, char *line)
{
	if (line[0] == 'R' && map->width == 0)
		parse_resolution(&line[1], map);
	else if (line[0] == 'C' && map->color_ceiling == -1)
		map->color_ceiling = parse_color(&line[1]);
	else if (line[0] == 'F' && map->color_floor == -1)
		map->color_floor = parse_color(&line[1]);
	else if (line[0] == 'S' && !map->path[sprite] && line[1] != 'O')
		map->path[sprite] = parse_path(&line[1]);
	else if (line[0] == 'N' && line[1] == 'O' && !map->path[north])
		map->path[north] = parse_path(&line[2]);
	else if (line[0] == 'S' && line[1] == 'O' && !map->path[south])
		map->path[south] = parse_path(&line[2]);
	else if (line[0] == 'W' && line[1] == 'E' && !map->path[west])
		map->path[west] = parse_path(&line[2]);
	else if (line[0] == 'E' && line[1] == 'A' && !map->path[east])
		map->path[east] = parse_path(&line[2]);
	else
	{
		free(line);
		return (ft_error(map, -18));
	}
	free(line);
	return (1);
}
