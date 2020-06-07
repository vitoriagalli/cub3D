/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 00:00:03 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/07 04:37:19 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**alocate_dynamic(char **map_buffer, int m)
{
	char	**new_map_buffer;
	char	**aux;
	int		i;

	if (!(new_map_buffer = alocate_memory(sizeof(char *) * (m + 2))))
	aux = map_buffer;
	i = 0;
	while(i < m)
	{
		new_map_buffer[i] = map_buffer[i];
		i++;
	}
	if (m > 0)
		free (map_buffer);
	return (new_map_buffer);
}

int		read_file_get_info(char *file, t_map *map)
{
	char	*line;
	int		fd;
	int		ismap;
	int		i = 0;
	int		n_col = 0;
	int		n_col_max = 0;

	fd = open(file, O_RDONLY);
	ismap = FALSE;
	int m = 0;
	while ((get_next_line(fd, &line)) == 1)
	{
		if (line[0] == ' ' || line[0] == '1')			//por enquanto aceita só espaço depois ver se trata tab tambem
		{
			ismap = TRUE;

			map->map_grid = alocate_dynamic(map->map_grid, m);
			if (!(n_col = parse_row_map(map, line, i)) || n_col < 0)
			{
				n_col_max = 0;
				break ;
			}
			n_col_max = n_col > n_col_max ? n_col : n_col_max;
			i++;
			m++;
		}
		else if (is_identifier(line) && !ismap)
			get_identifier(map, line);
		else if (!(is_empty_line(line)))
			break ;
		else
			free(line);
	}
	free(line);
	map->n_row = i;
	map->n_column = n_col_max;
	fill_columns(map);
	return (ft_error(map));
}

int main(int argc, char **argv)
{
	t_vars	vars;

	(void) argv;
	if (argc)
	{
		alocate_map(&vars);
		if (!read_file_get_info("map2.cub", vars.map))
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
