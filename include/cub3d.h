/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:58 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/02 21:32:49 by vscabell         ###   ########.fr       */
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

# define W_KEY 0x0077
# define S_KEY 0x0073
# define A_KEY 0x0061
# define D_KEY 0x0064
# define RIGHT_ARROW_KEY 0x00ff53
# define LEFT_ARROW_KEY 0x00ff51
# define ESC_KEY 0x00ff1b

# define NORTH (3 * PI / 2)
# define SOUTH (PI / 2)
# define EAST 0
# define WEST PI

# define HORZ 0
# define VERT 1

# define WALL_2D_COLOR 0x000000
# define VOID_2D_COLOR 0xffffff

# define FOV 66 * PI / 180
# define WALL_WIDTH 1

# define MOVE_SPEED 30
# define ROTAT_SPEED 20 * PI / 180

# define MAP2D_SCALE 0.25

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

typedef struct	s_color {
	int			north_text;
	int			south_text;
	int			east_text;
	int			west_text;
	int			ceilling;
	int			floor;
}				t_color;

typedef struct	s_map {
	int			width;
	int			height;
	int			n_column;
	int			n_row;
	t_point		*init_posit;
	float		rotation_angle;
	int			tile_size;
	int			num_rays;
	t_color		*color;
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
	t_data		*data;
	t_map		*map;
	t_point		*point;
	t_player	*player;
	t_ray		**ray;
}				t_vars;

/*
** utilis functions
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
float	ft_normalize_angle(float angle);
int		ray_facing(float angle, int way);
void	ft_swap(int *a, int *b);
int		is_end_window(t_map *map,float x, float y);
float	dist_btw_points(float x0, float y0, float x1, float y1);
void	*alocate_memory(int sizeof_type);
int		**alocate_buffer(int n_arrays, int n_elem);
void	clean_buffer(int **buffer, int n_arrays);

/*
** geometry functions
*/
void	ft_circle(t_data *img, int *c, int radius, int color);
void	ft_rectangle(t_data *img, t_point point, int l_width, int l_height);
void 	ft_line(t_data *img, int *p0, int *p1, int color);

/*
** game functions
*/
void	init_game(t_vars *vars);
void	put_game(t_vars *vars);
int		close_program(t_vars *vars);

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
** mini map and player functions
*/
void	read_map(t_vars *vars);
t_map	*assign_map(void);
void	put_minimap(t_vars *vars);
int		is_wall(t_map *map, int x, int y);
void	put_player_minimap(t_vars *vars);
void	ft_circle_player(t_data *img, t_player *player);
// void	ft_direction_player(t_data *img, t_player *player);
// void	ft_fov(t_vars *vars);

/*
** move player functions
*/
int		move_player_press(int keycode, t_vars *vars);
int		move_player_release(int keycode, t_vars *vars);
void	replace_image(t_vars *vars, t_data *new_img);
int		new_position_player(int keycode, t_vars *vars);
int		update_new_position(t_vars *vars);

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
void	put_player_3dmap(t_vars *vars);
void	project_game(t_vars *vars, int **color_buf);
void	clean_structure(t_vars *vars);

/*
** color functions
*/
int		**store_pixel_info(t_vars *vars, int **buffer);
int		get_color(t_vars *vars, int n_ray, int column);


int		get_texture(t_vars *vars, int n_ray, int column);
unsigned int	ft_color(int i);
int 	ft_rgb(int r, int g, int b);
int		shade_wall(float dist, int r, int g, int b);	//funcao migué -> arrumar

#endif
