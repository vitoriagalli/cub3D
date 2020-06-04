/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:53 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/04 00:58:48 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_player_press(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
		vars->player->walk_direction = +1;
	else if (keycode == S_KEY)
		vars->player->walk_direction = -1;
	else if (keycode == D_KEY)
		vars->player->turn_direction = +1;
	else if (keycode == A_KEY)
		vars->player->turn_direction = -1;
	else if (keycode == RIGHT_ARROW_KEY)
		vars->player->rotation_angle = EAST;
	else if (keycode == LEFT_ARROW_KEY)
		vars->player->rotation_angle = WEST;
	else if (keycode == M_KEY)
		vars->minimap = vars->minimap == TRUE ? FALSE : TRUE;
	else if (keycode == ESC_KEY)
		return (close_program(vars));
	return (new_position_player(keycode, vars));
}

int	move_player_release(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
		vars->player->walk_direction = 0;
	else if (keycode == S_KEY)
		vars->player->walk_direction = 0;
	else if (keycode == D_KEY)
		vars->player->turn_direction = 0;
	else if (keycode == A_KEY)
		vars->player->turn_direction = 0;
	return (update_new_position(vars));			//******** VERIFICAR
}

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
	next_posit_x = vars->player->posit->x + offset;
	offset = sin(vars->player->rotation_angle) * move_step;
	next_posit_y = vars->player->posit->y + offset;
	if((keycode == W_KEY || keycode == S_KEY) && !(is_wall(vars->map, next_posit_x, next_posit_y)))
	{
		vars->player->posit->x = next_posit_x;
		vars->player->posit->y = next_posit_y;
	}
	else if (keycode == A_KEY || keycode == D_KEY)
	{
		vars->player->rotation_angle += vars->player->turn_direction * vars->player->rotation_speed;
		vars->player->rotation_angle = ft_normalize_angle(vars->player->rotation_angle);
	}
	return (update_new_position(vars));
}

int	update_new_position(t_vars *vars)
{
	t_data	*img;

	img = create_image(vars->mlx, vars->map);
	replace_image(vars, img);
	put_game(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	return (0);
}
