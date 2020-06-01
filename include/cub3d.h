/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:58 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/01 08:03:18 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define INT_MAX 2147483647
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

# define HORZ 0
# define VERT 1

// 2d map colors
# define WALL_2D_COLOR 0xff000000
# define VOID_2D_COLOR 0xffffffff
# define PLAYER_2D_COLOR

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
	t_point		*init_posit;
	float		rotation_angle;
	int			tile_size;
	int			num_rays;
}				t_map;

typedef struct	s_player {
	t_point		*posit;
	int			turn_direction;
	int			walk_direction;
	float		rotation_angle;
	int			move_speed;
	float		rotation_speed;
}				t_player;

typedef struct	s_ray {
	t_point		*collision;
	float		dist_wall;
	float		ray_angle;
	int			coord;
}				t_ray;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_map		*map;
	t_data		*data;
	t_point		*point;
	t_player	*player;
	t_ray		**ray;
}				t_vars;

/*
** utilis functions
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	*alocate_memory(int sizeof_type);
float	ft_normalize_angle(float angle);
int		ray_facing(float angle, int way);
int		is_end_window(t_map *map,float x, float y);
float	dist_btw_points(float x0, float y0, float x1, float y1);

/*
** geometry functions
*/
void	ft_circle(t_data *img, int xc, int yc, int radius, int color);
void	ft_rectangle(t_data *img, t_point point, int l_width, int l_height);
void 	ft_line(t_data *img, int x0, int y0, int x1, int y1, int color);

/*
** init game
*/
void	init_game(t_vars *vars);

/*
** setup, crate and assign variables
*/
void		create_vars(t_vars *vars);
t_data		*create_image(void *mlx_ptr, t_map *map);
t_point		*create_point(int x, int y, int color);
t_player	*create_player(t_map *map, int move_speed, float rotation_speed);
void		assign_point(t_point *point, int x, int y, int color);
void		assign_player(t_player *player, int move_speed, float rotation_speed);
void		info_map_to_player(t_player *player, t_map *map);

/*
** read and raycast map 2d and player
*/
void	read_map(t_vars *vars);
t_map	*assign_map(void);
void	put_2dmap(t_vars *vars);
int		is_wall(t_map *map, int x, int y);

/*
** move player functions
*/
void	put_player(t_vars *vars);
int		move_player_press(int keycode, t_vars *vars);
int		move_player_release(int keycode, t_vars *vars);
void	replace_image(t_vars *vars, t_data *new_img);
int		new_position_player(int keycode, t_vars *vars);
int		update_new_position(t_vars *vars);

/*
** player 2d map functions
*/
void	map2d_player(t_vars *vars);
void	ft_direction_player(t_data *img, t_player *player);
void	ft_circle_player(t_data *img, t_player *player);
void	ft_fov(t_vars *vars);

/*
** raycast
*/
t_ray	**ft_raycast(t_vars *vars);
void	check_closest_wall(t_vars *vars, t_ray *ray, float ray_angle);
void	assign_ray(t_ray *ray, t_point *collision, float dist_wall, int coord);
t_point	*cast_ray(t_vars *vars, float ray_angle, int coord);
t_point	*horz_interception(t_vars *vars, t_point *intercept, float ray_angle);
t_point	*vert_interception(t_vars *vars, t_point *intercept, float ray_angle);
void	put_rays(t_vars *vars);

/*
** render 3d map
*/
void		map3d_player(t_vars *vars);
void		projection(t_vars *vars);

#endif
