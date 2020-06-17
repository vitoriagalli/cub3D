/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_funct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:42:31 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/17 04:46:19 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->size_line + x * (data->bpp / 8));
	dst = data->addr + offset;
	*(unsigned int*)dst = color;
}

t_tex	*load_texture(void *mlx_ptr, char *path)
{
	t_tex	*tex;

	tex = ft_calloc(1, sizeof(t_tex));
	tex->data = ft_calloc(1, sizeof(t_data));
	if (!(tex->data->img = mlx_xpm_file_to_image(mlx_ptr, path, &tex->width,
	&tex->height)))
	{
		free(tex->data);
		free(tex);
		return (NULL);
	}
	tex->data->addr = mlx_get_data_addr(tex->data->img, &tex->data->bpp,
	&tex->data->size_line, &tex->data->endian);
	return (tex);
}

int	get_texture_color(t_tex *tex, int x, int y)
{
	int		offset;

	offset = (y * tex->data->size_line + x * (tex->data->bpp / 8));
	return (*(unsigned int *)(tex->data->addr + offset + 3) << 24 |
			*(unsigned int *)(tex->data->addr + offset + 2) << 16 |
			*(unsigned int *)(tex->data->addr + offset + 1) << 8 |
			*(unsigned int *)(tex->data->addr + offset + 0) << 0);
}
