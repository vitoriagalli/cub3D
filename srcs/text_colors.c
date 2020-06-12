/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:42:31 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/12 22:45:17 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		store_texture(t_vars *vars, int y, int i, float *limit)
{
	t_ray	*ray;
	float	ymin;
	float	ymax;

	ray = NULL;
	ymin = limit[0];
	ymax = limit[1];
	ray = vars->ray[i];
	if (ray_facing(ray->ray_angle, ray_up) && ray->coord == HORZ)
		return (get_texture_color(vars->tex[north],
				(int)ray->collision->x % vars->tex[north]->width,
				(y - ymin) * (vars->tex[north]->height - 0) / (ymax - ymin) + 0));
	else if (ray_facing(ray->ray_angle, ray_down) && ray->coord == HORZ)
		return (get_texture_color(vars->tex[south],
				(int)ray->collision->x % vars->tex[north]->width,
				(y - ymin) * (vars->tex[south]->height - 0) / (ymax - ymin) + 0));
	else if (ray_facing(ray->ray_angle, ray_right) && ray->coord == VERT)
		return (get_texture_color(vars->tex[east],
				(int)ray->collision->y % vars->tex[north]->width,
				(y - ymin) * (vars->tex[east]->height - 0) / (ymax - ymin) + 0));
	else if (ray_facing(ray->ray_angle, ray_left) && ray->coord == VERT)
		return (get_texture_color(vars->tex[west],
				(int)ray->collision->y % vars->tex[north]->width,
				(y - ymin) * (vars->tex[west]->height - 0) / (ymax - ymin) + 0));
	else
		return (-1);
}

//funcao que pega a cor do pixel da posicao data
int get_texture_color (t_tex *texture, int x, int y)
{
	int offset;
	int a;
	int r;
	int g;
	int b;

	offset = y * texture->data->size_line + x * (texture->data->bpp / 8);
	a = texture->data->addr[offset + 0];
	r = texture->data->addr[offset + 1];
	g = texture->data->addr[offset + 2];
	b = texture->data->addr[offset + 3];
	return (b << 24 | g << 16 | r << 8 | a);
}

int ft_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	shade_wall(float dist, int r, int g, int b)
{
	int		delta;
	int		delta_max;
	float	dist_max;

	dist_max = 1100;
	delta_max = 240;
	delta = dist * delta_max / dist_max;
	r -= r > delta? delta : 0;
	g -= g > delta? delta : 0;
	b -= b > delta? delta : 0;
	return (ft_rgb(r, g, b));
}

// função que puxa a imagem do diretório e a transforma em textura
t_tex	*get_texture(void *mlx_ptr, char *path)
{
	t_tex	*texture;
	t_data	*data;

	texture = allocate_memory(sizeof(t_tex));
	data = allocate_memory(sizeof(t_data));
	data->img = mlx_xpm_file_to_image(mlx_ptr, path, &texture->width,
	&texture->height);
	if (!(data->img))
	{
		free(data);
		free(texture);
		return (NULL);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
	&data->size_line, &data->endian);
	texture->data = data;
	return (texture);
}
