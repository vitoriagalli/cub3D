#include "cub3d.h"

void	replace_image(t_vars *vars, t_data *new_img)
{
	mlx_destroy_image(vars->mlx, vars->data->img);
	free(vars->data);		//liberar o espaço alocado quando criou a imagem
	vars->data = new_img;
}

int		new_position_player(int keycode, t_vars *vars)
{
	int	move_step;
	int	offset;
	int	next_posit_x;
	int	next_posit_y;

	move_step = vars->player->walk_direction * vars->player->move_speed;
	offset = sin(vars->player->rotation_angle) * move_step;
	next_posit_x = vars->player->x + offset;
	offset = cos(vars->player->rotation_angle) * move_step;
	next_posit_y = vars->player->y + offset;

	if((keycode == W_KEY || keycode == S_KEY) && !(is_wall(next_posit_x, next_posit_y)))
	{
		vars->player->x = next_posit_x;
		vars->player->y = next_posit_y;
	}
	else if (keycode == A_KEY || keycode == D_KEY)
	{
		vars->player->rotation_angle += vars->player->turn_direction * vars->player->rotation_speed;
	}
	return(render(vars));
}

int	render(t_vars *vars)
{
	t_data	*img;

	img = create_image(vars->mlx);
	put_map(img, vars->point);
	put_player(img, vars->player);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	replace_image(vars, img);
	return(0);
}
