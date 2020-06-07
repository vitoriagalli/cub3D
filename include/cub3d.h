/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:58 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/07 02:02:58 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "util.h"
# include "get_next_line.h"
# include <math.h>
# include <stdio.h>


# define INT_MAX 2147483647
# define PI 3.14159265359

# define W_KEY 0x0077
# define S_KEY 0x0073
# define A_KEY 0x0061
# define D_KEY 0x0064
# define RIGHT_ARROW_KEY 0x00ff53
# define LEFT_ARROW_KEY 0x00ff51
# define M_KEY 0x006d
# define ESC_KEY 0x00ff1b

# define NORTH (3 * PI / 2)
# define SOUTH (PI / 2)
# define EAST 0
# define WEST PI

# define HORZ 0
# define VERT 1

# define FALSE 0
# define TRUE 1

# define WALL_2D_COLOR 0x000000
# define VOID_2D_COLOR 0xffffff

# define FOV 60 * PI / 180
# define WALL_WIDTH 1

# define MOVE_SPEED 20
# define ROTAT_SPEED 5 * PI / 180

# define MAP2D_SCALE 0.2

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
				west
}				t_text;

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
	float		rotation_angle;
	int			tile_x;
	int			tile_y;
	int			num_rays;
	t_color		*color;
	char		**path;
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

typedef struct	s_tex {
	t_data		*data;
	int			width;
	int			height;
}				t_tex;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_data		*data;
	t_map		*map;
	t_point		*point;
	t_player	*player;
	t_ray		**ray;
	t_tex		**tex;
	int			minimap;
}				t_vars;

/*
** validate and parse input functions
*/

void 		get_identifier(t_map *map, char *line);
char		*parse_path(char *path);
void		parse_resolution(char *str, t_map *map);
int			parse_color(char *str);
int			get_additive_color(char *str, int i, int *num);
int			parse_row_map(t_map *map, char *line, int row);
int			parse_player_location(t_map *map, char c, int row, int column);
int			is_identifier(char *line);
void		fill_columns(t_map *map);
int			is_empty_line(char *line);
int			validate_map(t_map *map);
int			ft_error(t_map *map);
int			free_map(t_map *map);

/*
** geometry and aux functions
*/

void			ft_circle(t_data *img, int *c, int radius, int color);
void			ft_rectangle(t_data *img, t_point point, int l_width, int l_height);
void		 	ft_line(t_data *img, int *p0, int *p1, int color);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
float			ft_normalize_angle(float angle);
int				ray_facing(float angle, int way);
float			dist_btw_points(float x0, float y0, float x1, float y1);
int				is_end_window(t_map *map, float x, float y);

/*
** color and texture functions
*/

t_tex			*get_texture(void *mlx_ptr, char *path);
int				store_texture(t_vars *vars, int y, int i, float *limit);
int				ft_rgb(int r, int g, int b);
int				shade_wall(float dist, int r, int g, int b);	//funcao migué -> arrumar
int				get_texture_color(t_tex *texture, int x, int y);

/*
** init and finish game functions
*/

void			create_vars(t_vars *vars);
void			init_game(t_vars *vars);
void			put_game(t_vars *vars);
void			clean_ray_struct(t_vars *vars);
int				close_program(t_vars *vars);

/*
** setup, crate and assign variables
*/

t_data			*create_image(void *mlx_ptr, t_map *map);
t_point			*create_point(int x, int y, int color);
t_player		*create_player(t_map *map, int move_speed, float rotation_speed);
t_tex			**create_texture(void *mlx_ptr, char **path);
void			assign_point(t_point *point, int x, int y, int color);
void			assign_player(t_player *player, int move_speed, float rotation_speed);
void			info_map_to_player(t_player *player, t_map *map);

/*
** mini map and player functions
*/

void			alocate_map(t_vars *vars);
void			assign_map(t_map *map);
void			put_minimap(t_vars *vars);
int				is_wall(t_map *map, int x, int y);
void			put_player_minimap(t_vars *vars);
void			ft_circle_player(t_data *img, t_player *player);

/*
** move player functions
*/

int				move_player_press(int keycode, t_vars *vars);
int				move_player_release(int keycode, t_vars *vars);
void			replace_image(t_vars *vars, t_data *new_img);
int				new_position_player(int keycode, t_vars *vars);
int				update_new_position(t_vars *vars);

/*
** raycast calculation
*/

t_ray			**ft_raycast(t_vars *vars);
void			check_closest_wall(t_vars *vars, t_ray *ray, float ray_angle);
void			assign_ray(t_ray *ray, t_point *collision, float dist_wall, int coord);
t_point			*cast_ray(t_vars *vars, float ray_angle, int coord);
t_point			*horz_interception(t_vars *vars, t_point *intercept, float ray_angle);
t_point			*vert_interception(t_vars *vars, t_point *intercept, float ray_angle);
void			put_rays(t_vars *vars);

/*
** render 3d map
*/

void			put_player_3dmap(t_vars *vars);
int				**get_pixel_info(t_vars *vars, int **buffer);
void			store_all_colors(t_vars *vars, int **buffer, float wall_proj_height, int i);
void			project_game(t_vars *vars, int **color_buf);

#endif
