/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:03:57 by vscabell          #+#    #+#             */
/*   Updated: 2020/05/30 17:22:03 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "map 2d");
	vars->data = create_image(vars->mlx); 		//em funcao de width e lenght
	vars->point = create_point(0, 0, 0xFF00FFFF);
	vars->player = create_player();

}

void	setup_vars(t_vars *vars)
{
	create_vars(vars);
	put_map(vars->data, vars->point);
	put_player(vars->data, vars->player);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
}
