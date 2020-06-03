/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:26:11 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/03 20:39:19 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
