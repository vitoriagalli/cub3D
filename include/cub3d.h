/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:58 by vscabell          #+#    #+#             */
/*   Updated: 2020/07/22 22:53:28 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <math.h>

# define INT_MAX 2147483647
# define PI 3.1416
# define W_KEY 0x0077
# define S_KEY 0x0073
# define A_KEY 0x0061
# define D_KEY 0x0064
# define RIGHT_ARROW_KEY 0x00ff53
# define LEFT_ARROW_KEY 0x00ff51
# define M_KEY 0x006d
# define ESC_KEY 0x00ff1b
# define NORTH 4.71
# define SOUTH 1.57
# define EAST 0
# define WEST PI
# define HORZ 0
# define VERT 1
# define FALSE 0
# define TRUE 1
# define WALL_2D_COLOR 0x4d4d33
# define RAYS_2D_COLOR 0xffff66
# define FOV 1.1
# define WALL_WIDTH 1
# define MOVE_SPEED 25
# define ROTAT_SPEED 0.12
# define MAP2D_SCALE 0.1
# define TILE_SIZE 64
# define OFFSET 8

typedef enum	e_playerface
{
	ray_up,
	ray_down,
	ray_left,
	ray_right
}				t_playerface;

typedef enum	e_text
{
	north,
	south,
	east,
	west,
	sprite
}				t_text;

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_data;

typedef struct	s_point {
	double		x;
	double		y;
	int			color;
}				t_point;

typedef struct	s_color {
	int			ceilling;
	int			floor;
}				t_color;

typedef struct	s_map {
	char		**map_grid;
	int			width;
	int			height;
	int			n_column;
	int			n_row;
	t_point		*init_posit;
	double		rotation_angle;
	int			num_rays;
	t_color		*color;
	char		**path;
	int			n_sprites;
	t_point		**sprite_posit;
}				t_map;

typedef struct	s_player {
	t_point		*posit;
	int			turn_direction;
	int			walk_direction;
	double		rotation_angle;
	int			move_speed;
	double		rotation_speed;
	double		dist_proj_plane;
}				t_player;

typedef struct	s_ray {
	t_point		*collision;
	double		dist_wall;
	double		ray_angle;
	int			coord;
}				t_ray;

typedef struct	s_tex {
	t_data		*data;
	int			width;
	int			height;
}				t_tex;

typedef struct	s_sprite
{
	t_point		*posit;
	double		angle;
	double		angle_dif;
	double		dist;
	double		height;
	double		width;
	int			ray_facing;
}				t_sprite;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_data		*data;
	t_map		*map;
	t_point		*point;
	t_player	*player;
	t_ray		**ray;
	t_tex		**tex;
	t_sprite	**sprite;
	int			minimap;
}				t_vars;

/*
** validate and parse input functions
*/

int				check_args(int argc, char **argv);
int				read_file(char *file, t_map *map);
int				get_map_info(t_map *map, char *line, int *row);
int				validate_map(t_map *map);
int				get_identifier(t_map *map, char *line);
int				ft_error(t_map *map, int i);
int				ft_path_error(t_vars *vars);
int				ft_arg_error(int i);

/*
** geometry and auxiliar functions
*/

void			ft_rectangle(t_data *img, t_point point, int width, int height);
void			ft_line(t_data *img, int *p0, int *p1, int color);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
double			ft_normalize_angle(double angle);
double			dist_btw_points(double x0, double y0, double x1, double y1);
int				ft_c_is_in(char c, char *str);
void			**allocate_dynamic(void **buffer, int size, int m);

/*
**  game functions
*/

int				init_game(t_vars *vars, int argc);
int				move_player_press(int keycode, t_vars *vars);
void			put_game(t_vars *vars);
int				update_new_position(t_vars *vars);
int				clean_before_close(t_vars *vars);
int				close_program(void);

/*
** setup, create and assign variables
*/

int				create_n_check(t_vars *vars);
t_point			*create_point(int x, int y, int color);
t_data			*create_image(void *mlx_ptr, t_map *map);
void			assign_point(t_point *point, int x, int y, int color);

/*
** render 2d and 3d functions
*/

int				is_wall(t_map *map, int x, int y, char identf);
int				is_end_window(t_map *map, double x, double y);
void			put_minimap(t_vars *vars);
void			put_rays(t_vars *vars);
void			put_3dmap(t_vars *vars);
void			put_sprites(t_vars *vars);
int				get_texture_color(t_tex *tex, int x, int y);

/*
** raycast calculation
*/

int				ray_facing(double angle, int way);
t_ray			**ft_raycast(t_vars *vars);
t_point			*cast_ray(t_vars *vars, double ray_angle, int coord,
				t_point *next);

/*
** clear data functions
*/

void			free_tex(void *mlx, t_tex **tex);
void			check_n_free(void *ptr);
int				free_map(t_map *map);
void			clean_buffer(void **buffer, int n_arrays);

/*
** convert to bmp function
*/

int				save_bmp_file(t_vars *vars);

#endif
