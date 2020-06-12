/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 00:00:03 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/12 20:41:09 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		read_file_get_info(char *file, t_map *map)
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
				return(ft_error(map, ret));
			}
		}
		else if (is_identifier(line) && !ismap)
			get_identifier(map, line);
		else if (!(is_empty_line(line)) || (is_empty_line(line) && ismap))
		{
			free (line);
			return(ft_error(map, -4));
		}
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
		allocate_map(&vars);
		if (!read_file_get_info("maps/map3.cub", vars.map))
			return (0);
		assign_map(vars.map);
		if (!(create_n_check(&vars)))
			return (0);
		init_game(&vars);
		mlx_hook(vars.win, 2, (1l << 0), move_player_press, &vars);

		// a função release deixa mais devagar pois processa todos os keycodes antes de update the position
		// a nao ser que mude para new_position player --> verificar diferenças
		// mlx_hook(vars.win, 3, (1l<<1), move_player_release, &vars); //verificar se faz diferença
		// mlx_expose_hook(vars.win, update_new_position, &vars);
		mlx_loop(vars.mlx);
	}

	return (0);
}

			// write(STDOUT_FILENO, "\e[31mError\e[39m\n", 16);
			// write(1, "\e[31mInvalid Map\e[39m\n", 22);
