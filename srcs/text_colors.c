/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:42:31 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/13 16:57:23 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_texture_color (t_tex *texture, int x, int y)
{
	int offset;

	offset = y * texture->data->size_line + x * (texture->data->bpp / 8);
	return (texture->data->addr[offset + 3] << 24
			| texture->data->addr[offset + 2] << 16
			| texture->data->addr[offset + 1] << 8
			| texture->data->addr[offset + 0]);
}

int ft_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

t_tex	*get_texture(void *mlx_ptr, char *path)
{
	t_tex	*texture;
	t_data	*data;

	texture = ft_calloc(1, sizeof(t_tex));
	data = ft_calloc(1, sizeof(t_data));
	data->img = mlx_xpm_file_to_image(mlx_ptr, path, &texture->width,
	&texture->height);
	if (!(data->img))
	{
		check_n_free(data);
		check_n_free(texture);
		return (NULL);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
	&data->size_line, &data->endian);
	texture->data = data;
	return (texture);
}
