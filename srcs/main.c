/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 00:00:03 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/05 06:29:16 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		read_file_get_info(char *file, t_map *map)
{
	map->map_grid = alocate_memory(sizeof(char *) * 200);			// TRATAR DEPOIS

	char	*line;
	int		fd;
	int		ismap;
	int		i = 0;
	int		n_col = 0;
	int		n_col_max = 0;

	fd = open(file, O_RDONLY);
	ismap = FALSE;
	while ((get_next_line(fd, &line)) == 1)
	{
		if (line[0] == ' ' || line[0] == '1')			//por enquanto aceita só espaço depois ver se trata tab tambem
		{
			ismap = TRUE;
			n_col = parse_row_map(map, line, i);
			n_col_max = n_col > n_col_max ? n_col : n_col_max;
			i++;
		}
		else
		{
			if (line[0] == 'R' && !ismap)
				parse_resolution(&line[1], map);
			else if (line[0] == 'C' && !ismap)
				map->color->ceilling = parse_color(&line[1]);
			else if (line[0] == 'F' && !ismap)
				map->color->floor = parse_color(&line[1]);
			// else if (line[0] == 'S' && !ismap)
			// 	get_text();
			if (line[0] == 'N' && line[1] == 'O' && !ismap)
				map->path[north] = parse_path(&line[2]);
			else if (line[0] == 'S' && line[1] == 'O' && !ismap)
				map->path[south] =  parse_path(&line[2]);
			else if (line[0] == 'W' && line[1] == 'E' && !ismap)
				map->path[west] =  parse_path(&line[2]);
			else if (line[0] == 'E' && line[1] == 'A' && !ismap)
				map->path[east] =  parse_path(&line[2]);
			free (line);
		}
	}
	free(line);
	map->n_row = i;
	map->n_column = n_col_max;

	return (ft_error(map));		// retorna o numero de linhas
}

int main(int argc, char **argv)
{
	t_vars	vars;
	char	**map_buf;

	map_buf = NULL;		 (void) argv;
	if (argc)
	{
		alocate_map(&vars);
		if (!read_file_get_info("map.cub", vars.map))
		{
			printf("Error\n");		//MODIFICAR para WRITE
			return (0);
		}


		assign_map(vars.map);

		// int i = -1;
		// while (i++ < vars.map->n_row - 1)
		// 	printf("%d %s\n", i ,vars.map->map_grid[i]);

		init_game(&vars);
		mlx_hook(vars.win, 2, (1l<<0), move_player_press, &vars);

		// a função release deixa mais devagar pois processa todos os keycodes antes de update the position
		// a nao ser que mude para new_position player --> verificar diferenças
		//mlx_hook(vars.win, 3, (1l<<1), move_player_release, &vars); //verificar se faz diferença
		//mlx_expose_hook(vars.win, update_new_position, &vars);

		mlx_loop(vars.mlx);

	}

	return (0);
}
