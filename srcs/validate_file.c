/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 06:53:34 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/04 20:00:41 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	get_resolution(char *str, t_map *map)
{
	int nb[2];
	int	n;
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]) == 1)
			i++;
		if (!ft_isdigit(str[i]))
			break ;
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
	map->width = nb[0];
	map->height = nb[1];
}

int	get_color_info(char *str)
{
	int nb[3];
	int	n;
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]) == 1)
			i++;
		if (!ft_isdigit(str[i]))
			break ;
		n = str[i] - '0';
		i++;
		while (ft_isdigit(str[i]))
		{
			n = 10 * n + (str[i] - '0');
			i++;
		}
		i++;		//pular a virgula?
		nb[j] = n;
		j++;
	}

	// printf("%d %d %d\n", nb[0], nb[1], nb[2]);

	return (ft_rgb(nb[0], nb[1], nb[2]));
}


void		process_map_info(t_map *map, char **map_info, int n)
{
	int i = 0;
	while (i < 7) //mudar pra 8 quando colocar sprite
	{
		if (map_info[i][0] == 'R')
			get_resolution(&map_info[i][2], map);
		else if (map_info[i][0] == 'C')
			map->color->ceilling = get_color_info(&map_info[i][2]);
		else if (map_info[i][0] == 'F')
			map->color->floor = get_color_info(&map_info[i][2]);
		// else if (map_info[i][0] == 'S')
		// 	get_text();
		if (map_info[i][0] == 'N' && map_info[i][1] == 'O')
			map->path[north] = &map_info[i][3];
		else if (map_info[i][0] == 'S' && map_info[i][1] == 'O')
			map->path[south] = &map_info[i][3];
		else if (map_info[i][0] == 'W' && map_info[i][1] == 'E')
			map->path[west] = &map_info[i][3];
		else if (map_info[i][0] == 'E' && map_info[i][1] == 'A')
			map->path[east] = &map_info[i][3];
		i++;
	}
	map->n_column = ft_strlen(map_info[i]);
	map->n_row = n - 7;
	map->map_grid = malloc(sizeof(char *) * map->n_row);  //mudar para 8 quando colocar sprite
	int p = 0;
	while (p < map->n_row)
	{
		map->map_grid[p] = map_info[i];
		search_player(map, map_info[i], i);
		i++;
		p++;
	}
}

void	search_player(t_map *map, char *row, int n)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if(row[i] == 'N' || row[i] == 'S' || row[i] == 'E' || row[i] == 'W' )
		{
			if (row[i] == 'N')
			{
				map->init_posit = create_point(n, i, 0);
				map->rotation_angle = north;
			}
			else if (row[i] == 'S')
			{
				map->init_posit = create_point(n, i, 0);
				map->rotation_angle = south;
			}
			else if (row[i] == 'E')
			{
				map->init_posit = create_point(n, i, 0);
				map->rotation_angle = east;
			}
			else if (row[i] == 'W')
			{
				map->init_posit = create_point(n, i, 0);
				map->rotation_angle = west;
			}
			break;
		}
		i++;
	}

}
