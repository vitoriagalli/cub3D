#include "cub3d.h"

int	ft_button(int button, int x, int y, t_vars *vars)
{
	(void) button;

	if (vars->pos->x == -1 && vars->pos->x == -1)
	{
		vars->pos->x = x;
		vars->pos->y = y;
	}
	else
	{
		ft_line_bresenham(vars->data, vars->pos->x, vars->pos->y, x, y);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
		vars->pos->x = x;
		vars->pos->y = y;
	}
	return (0);
}

void	ft_draw_line(void)
{
	t_data	img;
	t_vars	vars;
	t_point	posit;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "line");

	img.img = mlx_new_image(vars.mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	vars.data = &img;
	posit.x = -1; posit.y = -1;
	vars.pos = &posit;
	mlx_hook(vars.win, 4, (1l<<2), ft_button, &vars);

	mlx_loop(vars.mlx);
}
