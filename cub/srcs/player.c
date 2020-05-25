#include "cub3d.h"

void	ft_circle_player(t_data *img, t_player center)
{
	ft_circle(img, center.x, center.y, center.radius, center.color);
}

void	ft_line_player(t_data *img, int x0, int y0, double angle)
{
	int x1 = x0 + sin(angle) * 30;
	int y1 = y0 + cos(angle) * 30;

	ft_line(img, x0, y0, x1, y1, 0xffff00ff);
}

void	player(t_vars *vars)
{
	ft_circle_player(vars->data, *vars->player);
	ft_line_player(vars->data, vars->player->x, vars->player->y, vars->player->rotation_angle);
}

int	move_player(int keycode, t_vars *vars)
{
	if(keycode)
		vars->player->x = vars->player->x + 20;
	return(0);
}
