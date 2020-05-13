#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

	//int     offset = (y * line_length + x * (bits_per_pixel / 8));

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
    img.img = mlx_new_image(mlx, 500, 500);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	draw_triangle_bresenham(&img);

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}

