/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar_funct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 06:04:13 by vscabell          #+#    #+#             */
/*   Updated: 2020/07/22 22:47:37 by vscabell         ###   ########.fr       */
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

double	ft_normalize_angle(double angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle += (2 * PI);
	return (angle);
}

double	dist_btw_points(double x0, double y0, double x1, double y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

int		ft_c_is_in(char c, char *str)
{
	size_t	i;
	size_t	len;

	if (!str)
		return (0);
	if (!*str)
		return (0);
	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

void	**allocate_dynamic(void **buffer, int size, int m)
{
	void	**new_buffer;
	int		i;

	new_buffer = ft_calloc(m + 2, size);
	i = 0;
	while (i < m)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	if (m > 0)
		free(buffer);
	return (new_buffer);
}
