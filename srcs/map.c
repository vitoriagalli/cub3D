#include "cub3d.h"

#define column 20
#define row 13
#define tile_size 20
#define height 260
#define width 400

int	map[row][column] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void	render_map(t_vars *vars)
{
	int i = 0;
	int j = 0;
	int x0;

	x0 = vars->pos->x;
	while (i < row)
	{
		j = 0;
		vars->pos->x = x0;
		while (j < column)
		{
			vars->pos->color = map[i][j]> 0? 0xff000029 : 0x2ff9fca7;
			ft_rectangle(vars->data, *vars->pos, tile_size, tile_size);
			vars->pos->x = vars->pos->x + tile_size;
			j++;
		}
		vars->pos->y = vars->pos->y + tile_size;
		i++;
	}
}

void	map_2d(void)
{
	t_vars	vars;
	t_data	img;
	t_point	point;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, width, height, "map");

	img.img = mlx_new_image(vars.mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian);

	ft_init_posit(&point, 0, 0, 0xff05cfff);

	vars.data = &img;
	vars.pos = &point;
	render_map(&vars);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
}
