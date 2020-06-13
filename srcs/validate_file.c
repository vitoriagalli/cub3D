/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 06:53:34 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/13 03:01:35 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	free_tex(void *mlx, t_tex **tex)
{
	int i;

	i = north;
	while (i <= sprite)
	{
		if (tex[i])
		{
			mlx_destroy_image(mlx, tex[i]->data->img);
			free(tex[i]->data);
			free(tex[i]);
		}
		i++;
	}
	free(tex);
}

int		ft_path_error(t_vars *vars)
{
	ft_error(vars->map, -12);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

char		*error_messeges(int i)
{
	if (i == -1)
		return ("ERROR OPEN FILE");
	if (i == -2)
		return ("ERROR INVALID CHAR");
	if (i == -3)
		return ("ERROR 2 PLAYERS");
	if (i == -4)
		return ("ERROR CHECK LINES");
	if (i == -5)
		return ("ERROR INVALID MAP");
	if (i == -6)
		return ("ERROR CHECK RESOLUTION");
	if (i == -7)
		return ("ERROR CHECK COLOR INFO");
	if (i == -8)
		return ("ERROR CHECK TEXTURES PATH");
	if (i == -9)
		return ("ERROR CHECK SPRITES INFO");
	if (i == -10)
		return ("ERROR CHECK INIT POSIT PLAYER");
	if (i == -11)
		return ("ERROR NO MAP");
	if (i == -12)
		return ("ERROR THERE IS NO TEXTURE IN THIS PATH");
	return (NULL);
}

int		ft_error(t_map *map, int i)
{
	free_map(map);
	ft_putendl_fd(error_messeges(i), STDOUT_FILENO);
	return (0);
}

int	check_lack_info(t_map *map)
{
	if (!(validate_map(map)))
		return (ft_error(map, -5));
	else if (!map->width || !map->height)
		return (ft_error(map, -6));
	else if (map->color->ceilling < 0 || map->color->floor < 0)
		return (ft_error(map, -7));
	else if (!map->path[north] || !*map->path[north] || !map->path[south] ||
			!*map->path[south] || !map->path[east] || !*map->path[east] ||
			!map->path[west] || !*map->path[west])
		return (ft_error(map, -8));
	else if (!map->sprite_posit || !*map->path[sprite])
		return (ft_error(map, -9));
	else if (!map->init_posit)
		return (ft_error(map, -10));
	else if (!map->n_column || !map->n_row) //verificar qual é essa situação
		return (ft_error(map, -11));
	return (1);
}

void	check_n_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

int		free_map(t_map *map)
{
	check_n_free(map->path[north]);
	check_n_free(map->path[south]);
	check_n_free(map->path[east]);
	check_n_free(map->path[west]);
	check_n_free(map->path[sprite]);
	check_n_free(map->path);
	check_n_free(map->color);
	check_n_free(map->init_posit);
	if (map->sprite_posit)
		clean_buffer((void **)map->sprite_posit, map->n_sprites);
	if (map->map_grid)
		clean_buffer((void **)map->map_grid, map->n_row);
	check_n_free(map);
	return (0);
}

int	check_char(t_map *map, int i, int j)
{
	if (i > 0 && i < (map->n_row - 1) && j > 0 && j < (map->n_column - 1))
	{
		if (!(ft_c_is_in(map->map_grid[i - 1][j - 1], "012")) ||
			!(ft_c_is_in(map->map_grid[i][j - 1], "012")) ||
			!(ft_c_is_in(map->map_grid[i + 1][j - 1], "012")) ||
			!(ft_c_is_in(map->map_grid[i - 1][j], "012")) ||
			!(ft_c_is_in(map->map_grid[i + 1][j], "012")) ||
			!(ft_c_is_in(map->map_grid[i - 1][j + 1], "012")) ||
			!(ft_c_is_in(map->map_grid[i][j + 1], "012")) ||
			!(ft_c_is_in(map->map_grid[i + 1][j + 1], "012")))
			return (0);
	}
	return (1);
}

int	validate_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->n_row)
	{
		j = 0;
		while (j < map->n_column)
		{
			if (map->map_grid[i][j] == '0' && (i == 0 || j == 0 ||
			i == map->n_row - 1 || j == map->n_column - 1))
				return (0);
			else if (map->map_grid[i][j] == '0')
				if (!check_char(map, i, j))
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}
