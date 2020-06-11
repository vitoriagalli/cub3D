/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 00:00:03 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/11 21:23:41 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		read_file_get_info(char *file, t_map *map)
{
	char	*line;
	int		fd;
	int		ismap;
	int		i;

	fd = open(file, O_RDONLY);
	ismap = FALSE;
	i = 0;
	while ((get_next_line(fd, &line)))
	{
		if (line[0] == ' ' || line[0] == '1')
		{
			ismap = TRUE;
			if (get_map_info(map, line, &i) < 0)
				break ;
		}
		else if (is_identifier(line) && !ismap)
			get_identifier(map, line);
		else if (!(is_empty_line(line)) || (is_empty_line(line) && ismap))
			break ;
		else
			free(line);
	}
	free(line);
	return (fill_columns(map));
}


int main(int argc, char **argv)
{
	t_vars	vars;

	(void) argv;
	if (argc)
	{
		alocate_map(&vars);
		if (!read_file_get_info("maps/map2.cub", vars.map))
		{
			write(STDOUT_FILENO, "\e[31mError\e[39m\n", 16);
			write(1, "\e[31mInvalid Map\e[39m\n", 22);
			return (0);
		}

		assign_map(vars.map);

		// int i = -1;
		// while (i++ < vars.map->n_row - 1)
		// 	printf("%d %s\n", i ,vars.map->map_grid[i]);

		init_game(&vars);
		mlx_hook(vars.win, 2, (1l << 0), move_player_press, &vars);

		// a função release deixa mais devagar pois processa todos os keycodes antes de update the position
		// a nao ser que mude para new_position player --> verificar diferenças
		//mlx_hook(vars.win, 3, (1l<<1), move_player_release, &vars); //verificar se faz diferença
		//mlx_expose_hook(vars.win, update_new_position, &vars);

		mlx_loop(vars.mlx);

	}

	return (0);
}
