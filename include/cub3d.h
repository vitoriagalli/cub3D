/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:58 by vscabell          #+#    #+#             */
/*   Updated: 2020/05/31 07:54:43 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define PI 3.14159265359
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define ESC_KEY 65307

# define NORTH (3 * PI / 2)
# define SOUTH (PI / 2)
# define EAST 0
# define WEST PI

# define FOV 60 * PI / 180
# define WALL_WIDTH 1

# define MAP2D_SCALE 0.2

typedef enum	e_playerface
{
				ray_up,
				ray_down,
				ray_left,
				ray_right
}				t_face;

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_data;

typedef struct	s_point {
	float		x;
	float		y;
	int			color;
}				t_point;

typedef struct	s_map {
	int			width;
	int			height;
	int			n_column;
	int			n_row;
	t_point		*posit_player;
	float		rotation_angle;
	int			tile_size;		// verificar necessidade
	int			num_rays;
}				t_map;

typedef struct	s_player {
	int			x;
	int			y;
	int			color;
	int			radius;
	int			turn_direction;
	int			walk_direction;
	float		rotation_angle;
	int			move_speed;
	float		rotation_speed;
}				t_player;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_map		*map;
	t_data		*data;
	t_point		*point;
	t_player	*player;
}				t_vars;

/*
** utilis functions
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
float	ft_normalize_angle(float angle);
int		ray_facing(float angle, int way);
int		is_end_window(t_map *map,float x, float y);
float	dist_btw_points(float x0, float y0, float x1, float y1);

/*
** geometry functions
*/
void	ft_circle(t_data *img, int xc, int yc, int radius, int color);
void	ft_arc_circle(t_data *img, t_player *center);
void	ft_rectangle(t_data *img, t_point point, int l_width, int l_height);
void 	ft_line(t_data *img, int x0, int y0, int x1, int y1, int color);

//void 	ft_line_f(t_data *img, int x0, int y0, int x1, int y1, int color);

/*
** setup, crate and assign variables
*/
void		setup_vars(t_vars *vars);
void		create_vars(t_vars *vars);
t_data		*create_image(void *mlx_ptr, t_map *map);
t_point		*create_point(int x, int y, int color);
t_player	*create_player(t_map *map, int color, int move_speed, float rotation_speed);
void		*alocate_memory(int sizeof_type);
void		assign_point(t_point *point, int x, int y, int color);
void		assign_player(t_player *player, int color, int move_speed, float rotation_speed);

/*
** create player and move functions
*/
void	put_player(t_vars *vars);
void	ft_circle_player(t_data *img, t_player *player);
void	ft_line_player(t_data *img, t_player *player);
void	ft_fov(t_vars *vars);

int		move_player_press(int keycode, t_vars *vars);
int		move_player_release(int keycode, t_vars *vars);
void	replace_image(t_vars *vars, t_data *new_img);
int		new_position_player(int keycode, t_vars *vars);

/*
** read and render map 2d and player
*/
void	read_map(t_vars *vars);
void	put_map(t_vars *vars);
int		render(t_vars *vars);
int		is_wall(t_map *map, int x, int y);
float	*calculate_rays(t_vars *vars);

/*
** raycast
*/
t_point	*cast_ray(t_vars *vars, float ray_angle, int coord);
t_point	*closest_wall(t_vars *vars, float ray_angle);
t_point	*horiz_inters(t_vars *vars, t_point *intercept, float ray_angle);
t_point	*vert_inters(t_vars *vars, t_point *intercept, float ray_angle);

/*
** render 3d map
*/
void	do_projection(t_vars *vars, float *rays);

/*
void	ft_init_posit(t_point *center, int x, int y, int color);
void	map_2d(void);
void	put_player(t_vars *vars);
void	ft_init_player(t_player *player, int x, int y, int color);
void	ft_circle_player(t_data *img, t_player center);
int		 ft_move_player(int keycode, t_vars *vars);
*/

#endif


// REVISAR FUNCAO MAPA
// -> NAO PRECISA DO *POINT
// REFAZER FUNCAO RETANGULO TAMBÉM

// VERIFICAR SE NAO EXISTE PAREDE NO LUGAR ONDE VAI COLOCAR O JOGADOR

// typedef enum	e_rayface
// {
// 				north,
// 				south,
// 				east,
// 				west
// }				t_face;

