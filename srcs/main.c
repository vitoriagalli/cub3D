/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 00:00:03 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/04 19:37:38 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		read_file_get_info(char *file, char **map_info)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	i = 0;
	while ((get_next_line(fd, &line)) == 1)
	{
		if (line[0] != '\0')
		{
			map_info[i] = line;
			i++;
		}
		else
			free(line);
	}
	return (i);
}

int main(int argc, char **argv)
{
	t_vars	vars;
	char	**map_info;
	int		n;

	n = 0;
	map_info = NULL;
	if (argc)
	{
		alocate_map(&vars);


		map_info = alocate_memory(sizeof(char *) * 100);
		n = read_file_get_info("map.cub", map_info); (void) argv;
		process_map_info(vars.map, map_info, n);

		assign_map(vars.map);

		// int i = -1;
		// while (i++ < vars.map->n_row - 1)
		// 	printf("%d %s\n", i ,vars.map->map_grid[i]);

		// t_vars	vars;

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
