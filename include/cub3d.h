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


typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
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
	t_point		*pos;
	t_data		*data;
}				t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	ft_init_posit(t_point *center, int x, int y, int color);
void	ft_circle(t_data *img, t_point center, int radius);
void	ft_circle_fill(t_data *img, t_point center, int radius);


#endif
