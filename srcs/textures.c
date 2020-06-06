/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:42:31 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/06 00:55:52 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		store_texture(t_vars *vars, int y, int i, float *limit)
{
	t_ray	*ray;
	int		offset;
	float	ymin;
	float	ymax;
	float	ytext;

	ray = NULL;
	ymin = limit[0];
	ymax = limit[1];
	ray = vars->ray[i];
	offset = (ray->coord == HORZ) ?
		(int)ray->collision->x % vars->map->tile_x :
		(int)ray->collision->y % vars->map->tile_y;
	ytext = (y - ymin) * (vars->tex[0]->height - 0) / (ymax - ymin) + 0;
	if (ray_facing(ray->ray_angle, ray_up) && ray->coord == HORZ)
		return (get_texture_color(vars->tex[north], offset, ytext));
	else if (ray_facing(ray->ray_angle, ray_down) && ray->coord == HORZ)
		return (get_texture_color(vars->tex[south], offset, ytext));
	else if (ray_facing(ray->ray_angle, ray_right) && ray->coord == VERT)
		return (get_texture_color(vars->tex[east], offset, ytext));
	else if (ray_facing(ray->ray_angle, ray_left) && ray->coord == VERT)
		return (get_texture_color(vars->tex[west], offset, ytext));
	else
		return (-1);
}

// função que puxa a imagem do diretório e a transforma em textura
t_tex	*get_texture(void *mlx_ptr, char *path)
{
	t_tex *texture;
	t_data *img;

	texture = alocate_memory(sizeof(t_tex));
	img = alocate_memory(sizeof(t_data));
	img->img = mlx_xpm_file_to_image(mlx_ptr, path, &texture->width,
	&texture->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
	&img->size_line, &img->endian);
	texture->data = img;
	return (texture);
}
