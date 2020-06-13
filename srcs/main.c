/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 00:00:03 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/13 01:40:20 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_vars	vars;

	if (argc == 2)
	{
		allocate_map(&vars);
		if (!read_file(argv[1], vars.map) || !(create_n_check(&vars)))
			return (0);
		init_game(&vars);
		mlx_hook(vars.win, 2, (1l << 0), move_player_press, &vars);
		mlx_loop(vars.mlx);
	}
	return (0);
}

			// write(STDOUT_FILENO, "\e[31mError\e[39m\n", 16);
			// write(1, "\e[31mInvalid Map\e[39m\n", 22);
