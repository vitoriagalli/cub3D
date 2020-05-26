#include "cub3d.h"

void	replace_image(t_vars *vars, t_data *new_img)
{
	mlx_destroy_image(vars->mlx, vars->data->img);
	free(vars->data);		//liberar o espaço alocado quando criou a imagem
	vars->data = new_img;
}

int		new_position_player(int keycode, t_vars *vars)
{
	float move_step;

	if(keycode == W_KEY || keycode == S_KEY)
	{
		move_step = vars->player->walk_direction * vars->player->move_speed;
		vars->player->x += sin(vars->player->rotation_angle) * move_step;
		vars->player->y += cos(vars->player->rotation_angle) * move_step;
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
