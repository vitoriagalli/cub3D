#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define PI 3.1416
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define ESC_KEY 65307


typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_data;

typedef struct	s_point {
	int			x;
	int			y;
	int			color;
}				t_point;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_data		*data;
	t_point		*pos;
}				t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	ft_move_circle(void);
void	ft_circle(t_data *img, t_point center, int radius);
void	ft_circle_fill(t_data *img, t_point center, int radius);
void	ft_init_posit(t_point *center, int x, int y, int color);

void	ft_draw_line(void);
void	ft_line_bresenham(t_data *img, int x0, int y0, int x1, int y1, int color);


void	map_2d(void);
void	ft_rectangle(t_data *img, t_point point, int width, int height);

#endif
