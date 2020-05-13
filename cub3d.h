#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define PI 3.1416

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_pixel(char *img, int x, int y, int color);

void	draw_circle(t_data *img);
void	draw_full_circle(t_data *img);
void	draw_full_circle_polar(t_data *img);
void	draw_line(t_data *img);
void	draw_line_dda(t_data *img);
void	draw_triangle(t_data *img);
void	draw_triangle_full(t_data *img);
void	draw_line_bresenham(t_data *img);
void	draw_triangle_bresenham(t_data *img);

#endif
