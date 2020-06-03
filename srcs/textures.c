/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:42:31 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/03 18:52:13 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// função que puxa a imagem do diretório e a transforma em textura
t_tex *create_texture(void *mlx_ptr, char *path)
{
	t_tex *texture;
	t_data *img;

	texture = (t_tex *)malloc(sizeof(t_tex));
	img = (t_data *)malloc(sizeof(t_data));
	img->img = mlx_xpm_file_to_image(mlx_ptr, path, &texture->width,
	&texture->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
	&img->size_line, &img->endian);
	texture->data = img;
	return (texture);
}

//funcao que pega a cor do pixel da posicao data
int get_texture_color (t_tex *texture, int x, int y)
{
	int offset;
	int a;
	int r;
	int g;
	int b;

	offset = y * texture->data->size_line
	+ x * (texture->data->bpp / 8);
	a = texture->data->addr[offset + 0];
	r = texture->data->addr[offset + 1];
	g = texture->data->addr[offset + 2];
	b = texture->data->addr[offset + 3];
	return (b << 24 | g << 16 | r << 8 | a);
}
