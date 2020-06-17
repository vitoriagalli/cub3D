/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:58 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/17 04:41:12 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <math.h>
# include <stdio.h> // tirar depois

# define INT_MAX 2147483647
# define PI 3.1416
# define W_KEY 0x0077
# define S_KEY 0x0073
# define A_KEY 0x0061
# define D_KEY 0x0064
# define UP_ARROW_KEY 0x00ff52
# define DOWN_ARROW_KEY 0x00ff54
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
# define WALL_2D_COLOR 0x000000
# define VOID_2D_COLOR 0xffffff
# define SPRITE_2D_COLOR 0x0ff00f
# define RAYS_2D_COLOR 0xffff00
# define FOV 1.1
# define WALL_WIDTH 1
# define MOVE_SPEED 20
# define ROTAT_SPEED 0.1
# define MAP2D_SCALE 0.15
# define TILE_SIZE 64

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
void			get_identifier(t_map *map, char *line);
char			*parse_path(char *path);
void			parse_resolution(char *str, t_map *map);
int				parse_color(char *str);
int				get_additive_color(char *str, int i, int *num);
int				parse_row_map(t_map *map, char *line, int row);
int				parse_player_location(t_map *map, char c, int row, int column);
int				is_identifier(char *line);
int				fill_columns(t_map *map);
int				is_empty_line(char *line);
int				validate_map(t_map *map);
int				check_lack_info(t_map *map);

/*
** error functions
*/

char			*error_messeges(int i);
int				free_map(t_map *map);
int				ft_error(t_map *map, int i);
int				ft_path_error(t_vars *vars);
int				ft_arg_error(int i);

/*
** geometry and aux functions
*/

void			ft_rectangle(t_data *img, t_point point, int width, int height);
void		 	ft_line(t_data *img, int *p0, int *p1, int color);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
double			ft_normalize_angle(double angle);
double			dist_btw_points(double x0, double y0, double x1, double y1);
int				is_end_window(t_map *map, double x, double y);
int				ft_c_is_in(char c, char *str);
void			check_n_free(void *ptr);
void			**allocate_dynamic(void **buffer, int size, int m);
void			clean_buffer(void **buffer, int n_arrays);
void			free_tex(void *mlx, t_tex **tex);
int				**alocate_buffer(int n_arrays, int n_elem);


/*
** color and texture functions
*/

t_tex			*load_texture(void *mlx_ptr, char *path);
int				put_texture(t_vars *vars, int y, int i, double *limit);
int				ft_rgb(int r, int g, int b);
int				get_texture_color(t_tex *tex, int x, int y);

/*
** init and finish game functions
*/

int				create_n_check(t_vars *vars);
void			init_game(t_vars *vars, int argc);
void			put_game(t_vars *vars);
void			clean_ray_struct(t_vars *vars);
int				clean_before_close(t_vars *vars);
int				close_program(void);

/*
** setup, crate and assign variables
*/

t_data			*create_image(void *mlx_ptr, t_map *map);
t_point			*create_point(int x, int y, int color);
t_player		*create_player(t_map *map, int move_speed, double rotat_speed);
t_tex			**create_texture(void *mlx_ptr, char **path);
t_sprite 		**create_sprite(t_map *map);
void			assign_point(t_point *point, int x, int y, int color);

/*
** render 2d and 3d functions
*/

void			allocate_map(t_vars *vars);
void			put_minimap(t_vars *vars);
int				is_wall(t_map *map, int x, int y, char identf);
void			put_3dmap(t_vars *vars);
void			put_colors(t_vars *vars, double wall_proj_height, int i);

/*
** key move player functions
*/

int				move_player_press(int keycode, t_vars *vars);
void			replace_image(t_vars *vars, t_data *new_img);
int				new_position_player(int keycode, t_vars *vars);
int				update_new_position(t_vars *vars);

/*
** raycast calculation
*/

int				ray_facing(double angle, int way);
t_ray			**ft_raycast(t_vars *vars);
void			check_closest_wall(t_vars *vars, t_ray *ray, double ray_angle);
void			assign_ray(t_ray *ray, t_point *collision, double dist_wall,
				int coord);
t_point			*cast_ray(t_vars *vars, double ray_angle, int coord, t_point *next);
t_point			*horz_inter(t_vars *vars, t_point *intercept, double ray_angle);
t_point			*vert_inter(t_vars *vars, t_point *intercept, double ray_angle);
void			put_rays(t_vars *vars);

/*
** sprites functions
*/

void			put_sprites(t_vars *vars);
void			calculate_sprite(t_vars *vars, int s);
void			draw_sprite(t_vars *vars, int s, int x);
void			sort_sprite(t_vars *vars);

/*
** convert to bpm functions
*/

int				render_bpm(t_vars *vars);
void			bpm_header(t_vars *vars, int fd);
void			little_endian(unsigned char *addr, unsigned int value, size_t size);
int				store_color(t_vars *vars, int x, int y);

#endif
