/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 00:00:03 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/29 19:07:47 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	check_args(argc, argv);
	allocate_map(&vars);
	if (!read_file(argv[1], vars.map) || !(create_n_check(&vars)))
		return (0);
	init_game(&vars, argc);
	mlx_hook(vars.win, 2, (1l << 0), move_player_press, &vars);
	mlx_hook(vars.win, 17, (1l << 17), clean_before_close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
