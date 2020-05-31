/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:05:04 by vscabell          #+#    #+#             */
/*   Updated: 2020/05/31 02:47:21 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	replace_image(t_vars *vars, t_data *new_img)
{
	mlx_destroy_image(vars->mlx, vars->data->img);
	free(vars->data);
	vars->data = new_img;
}

int		new_position_player(int keycode, t_vars *vars)
{
	int	move_step;
	int	offset;
	int	next_posit_x;
	int	next_posit_y;

	move_step = vars->player->walk_direction * vars->player->move_speed;
	offset = cos(vars->player->rotation_angle) * move_step;
	next_posit_x = vars->player->x + offset;
	offset = sin(vars->player->rotation_angle) * move_step;
	next_posit_y = vars->player->y + offset;

	if((keycode == W_KEY || keycode == S_KEY) && !(is_wall(vars->map, next_posit_x, next_posit_y)))
	{
		vars->player->x = next_posit_x;
		vars->player->y = next_posit_y;
	}
	else if (keycode == A_KEY || keycode == D_KEY)
	{
		vars->player->rotation_angle += vars->player->turn_direction * vars->player->rotation_speed;
		vars->player->rotation_angle = ft_normalize_angle(vars->player->rotation_angle);
	}
	return(render(vars));
}

int	render(t_vars *vars)
{
	t_data	*img;

	img = create_image(vars->mlx, vars->map);
	replace_image(vars, img);
	put_map(vars);
	put_player(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	return(0);
}
