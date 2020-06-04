/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 00:00:03 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/04 03:43:51 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	// int fd;
	// int ret;
	// char *line;

	// (void) argv;
	// if (argc == 1)
	// {
	// 	fd = open("map.cub", O_RDONLY);
	// 	while ((ret = get_next_line(fd, &line)) == 1)
	// 		printf("%s\n", line);
	// }

	(void)argc; (void)argv;
	t_vars	vars;
	init_game(&vars);
	mlx_hook(vars.win, 2, (1l<<0), move_player_press, &vars);
	// a função release deixa mais devagar pois processa todos os keycodes antes de update the position
	// a nao ser que mude para new_position player --> verificar diferenças
	//mlx_hook(vars.win, 3, (1l<<1), move_player_release, &vars); //verificar se faz diferença
	//mlx_expose_hook(vars.win, update_new_position, &vars);
	mlx_loop(vars.mlx);
}
