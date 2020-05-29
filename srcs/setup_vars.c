#include "cub3d.h"

void	create_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "map 2d");
	vars->data = create_image(vars->mlx); 		//em funcao de width e lenght
	vars->point = create_point();
	vars->player = create_player();

}

void	setup_vars(t_vars *vars)
{
	create_vars(vars);
	put_map(vars->data, vars->point);
	put_player(vars->data, vars->player);

	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
}
