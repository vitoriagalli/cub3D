/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bpm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:40:56 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/17 04:55:07 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		render_bpm(t_vars *vars)
{
	int		fd;
	int		bpm[vars->map->height][vars->map->width];
	int		x;
	int		y;

	if (!(fd = open("./img.bpm", O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 777)))
		return (0);
	bpm_header(vars, fd);
	y = vars->map->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < vars->map->width)
		{
			bpm[y][x] = store_color(vars, x, y);
			write(fd, &bpm[y][x], 4);
			x++;
		}
		y--;
	}
	close(fd);
	return (0);
}

void	bpm_header(t_vars *vars, int fd)
{
	unsigned char c[54];

	ft_bzero(&c, 54);
	c[0] = 'B';							//file type
	c[1] = 'M';							//file type
	little_endian(&c[10], 54, 4);		//pixel data offset
	little_endian(&c[14], 40, 4); 		//header size wich is 40
	little_endian(&c[18], vars->map->width, 4);		//width final image
	little_endian(&c[22], vars->map->height, 4);	//height final image
	little_endian(&c[26], 1, 2);		//numb of color planes
	little_endian(&c[28], 32, 2);		//numb of bits a pixel takes to represent a color
	write(fd, c, 54);
}

void	little_endian(unsigned char *addr, unsigned int value, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		addr[i] = (char)(value >> (i * 8));
		i++;
	}
}

int		store_color(t_vars *vars, int x, int y)
{
	unsigned int	color;
	unsigned char	addr_color[4];

	if (x >= 0 && vars->map->width && y >= 0 && y < vars->map->height)
	{
		color = *(unsigned int*)(vars->data->addr + (4 * vars->map->width * y) +
		(4 * x));
		little_endian(&addr_color[0], color, 4);
		return (*(unsigned int*)(addr_color));
	}
	return (0);
}
