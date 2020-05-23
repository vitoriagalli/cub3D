#include "cub3d.h"


void	ft_move_up(t_vars *vars)
{
	t_data	img;
	t_point	center;

	center.y = vars->pos->y - 10;
	vars->pos->y = center.y;
	img.img = mlx_new_image(vars->mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	ft_init_posit(&center, vars->pos->x, center.y, 0xff05cf00);
	ft_circle_fill(&img, center, 50);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);


	mlx_destroy_image(vars->mlx, vars->data->img);
	vars->data = &img;

}

void	ft_destroy(t_vars *vars)
{
	//mlx_destroy_image(vars->mlx, vars->data->img);
	mlx_destroy_window(vars->mlx, vars->win);
}

int	ft_move(int keycode, t_vars *vars)
{
	if (keycode == W_KEY || keycode == S_KEY | keycode == A_KEY | keycode == D_KEY)
	{
		t_data	img;
		t_point	center;
		int 	offset;

		offset = 20;
		if (keycode == W_KEY ||keycode == S_KEY)
		{
			center.y = keycode == W_KEY? vars->pos->y - offset: vars->pos->y + offset;
			center.x = vars->pos->x;
			vars->pos->y = center.y;
		}
		else if (keycode == A_KEY ||keycode == D_KEY)
		{
			center.x = keycode == A_KEY? vars->pos->x - offset: vars->pos->x + offset;
			center.y = vars->pos->y;
			vars->pos->x = center.x;
		}

		img.img = mlx_new_image(vars->mlx, 500, 500);
		img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
		ft_init_posit(&center, center.x, center.y, 0xff05cfff);
		ft_circle_fill(&img, center, 50);
		mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
		mlx_destroy_image(vars->mlx, vars->data->img);
		vars->data = &img;
	}
	else if (keycode == 65307)
		ft_destroy(vars);
	return (0);
}

void	ft_move_circle(void)
{
	t_vars	vars;
	t_data	img;
	t_point	center;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "new window");

	img.img = mlx_new_image(vars.mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);

	ft_init_posit(&center, 250, 250, 0xff05cfff);
	ft_circle_fill(&img, center, 50);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	vars.pos = &center;
	vars.data = &img;
	mlx_hook(vars.win, 2, (1l<<0), ft_move, &vars);

	mlx_loop(vars.mlx);
}

int main (void)
{
	ft_move_circle();
}

	//mlx_hook(vars.win, 3, (1L<<1), ft_print_str, &vars);	//release any key - print


/*

#define KeyPress		2
#define KeyRelease		3
#define ButtonPress		4
#define ButtonRelease	5
#define MotionNotify	6
#define EnterNotify		7

#define KeyPressMask			(1L<<0)
#define KeyReleaseMask			(1L<<1)
#define ButtonPressMask			(1L<<2)
#define ButtonReleaseMask		(1L<<3)
#define EnterWindowMask			(1L<<4)
*/
