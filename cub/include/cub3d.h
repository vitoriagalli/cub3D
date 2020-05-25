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

# define column 20
# define row 13
# define tile_size 20
# define height 260
# define width 400


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

typedef struct	s_player {
	int			x;
	int			y;
	int			color;
	int			radius;
	int			turn_direction;
	int			walk_direction;
	double		rotation_angle;
	int			move_speed;
	double		rotation_speed;
}				t_player;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_data		*data;
	t_point		*point;
	t_player	*player;
}				t_vars;


/*
** utilis functions
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/*
** geometry functions
*/
void	ft_circle(t_data *img, int xc, int yc, int radius, int color);
void	ft_arc_circle(t_data *img, t_player center);
void	ft_rectangle(t_data *img, t_point point, int l_width, int l_height);
void 	ft_line(t_data *img, int x0, int y0, int x1, int y1, int color);

/*
** setup, crate and assign variables
*/
void		setup_vars(t_vars *vars);
void		create_vars(t_vars *vars);
t_data		*create_image(void *mlx_ptr);
t_point		*create_point(void);
t_player	*create_player(void);
void		*alocate_memory(int sizeof_type);
void		assign_point(t_point *point, int x, int y, int color);
void		assign_player(t_player *player, int x, int y, int color);

/*
** render map 2d
*/
//int		map[row][column];
void	render_map(t_vars *vars);


/*
** create player and move functions
*/
void	player(t_vars *vars);
void	ft_circle_player(t_data *img, t_player center);
void	ft_line_player(t_data *img, int x0, int y0, double angle);
int		move_player(int keycode, t_vars *vars);

/*
void	ft_init_posit(t_point *center, int x, int y, int color);
void	map_2d(void);
void	put_player(t_vars *vars);
void	ft_init_player(t_player *player, int x, int y, int color);
void	ft_circle_player(t_data *img, t_player center);
int		 ft_move_player(int keycode, t_vars *vars);
*/

#endif
