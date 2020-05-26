#include "cub3d.h"

void	ft_circle_player(t_data *img, t_player center)
{
	ft_circle(img, center.x, center.y, center.radius, center.color);
}

void	ft_line_player(t_data *img, t_player *player)
{
	int x1;
	int y1;

	x1 = player->x + sin(player->rotation_angle) * 30;
	y1 = player->y + cos(player->rotation_angle) * 30;

	ft_line(img, player->x, player->y, x1, y1, player->color);
}

void	put_player(t_data *img, t_player *player)
{
	ft_circle_player(img, *player);
	ft_line_player(img, player);
}

int	move_player_press(int keycode, t_vars *vars)
{
	if(keycode == W_KEY)
		vars->player->walk_direction = +1;
	else if(keycode == S_KEY)
		vars->player->walk_direction = -1;
	else if(keycode == D_KEY)
		vars->player->turn_direction = -1;
	else if(keycode == A_KEY)
		vars->player->turn_direction = +1;
	return(new_position_player(keycode, vars));
}

int	move_player_release(int keycode, t_vars *vars)
{
	if(keycode == W_KEY)
		vars->player->walk_direction = 0;
	else if(keycode == S_KEY)
		vars->player->walk_direction = 0;
	else if(keycode == D_KEY)
		vars->player->turn_direction = 0;
	else if(keycode == A_KEY)
		vars->player->turn_direction = 0;
	return(render(vars));
}
