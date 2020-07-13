/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 02:02:45 by vscabell          #+#    #+#             */
/*   Updated: 2020/07/13 03:51:53 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*error_messeges_continue(int i)
{
	if (i == -11)
		return ("\e[31mERROR\e[39m\nInvalid resolution");
	if (i == -12)
		return ("\e[31mERROR\e[39m\nInvalid color");
	if (i == -13)
		return ("\e[31mERROR\e[39m\nInvalid texture path");
	if (i == -14)
		return ("\e[31mERROR\e[39m\nNo sprite was set on the map");
	if (i == -15)
		return ("\e[31mERROR\e[39m\nNo player was set on the map");
	if (i == -16)
		return ("\e[31mERROR\e[39m\nMlx could not be initialized");
	if (i == -17)
		return ("\e[31mERROR\e[39m\nTexture could not be loaded");
	if (i == -18)
		return ("\e[31mERROR\e[39m\nDuplicate key");
	return (NULL);
}

static char	*error_messeges(int i)
{
	if (i == -1)
		return ("\e[31mERROR\e[39m\nNo argument");
	if (i == -2)
		return ("\e[31mERROR\e[39m\nToo many arguments");
	if (i == -3)
		return ("\e[31mERROR\e[39m\nFirst argument is not .cub");
	if (i == -4)
		return ("\e[31mERROR\e[39m\nSecond argument is invalid. Try --save");
	if (i == -5)
		return ("\e[31mERROR\e[39m\nFirst argument is invalid");
	if (i == -6)
		return ("\e[31mERROR\e[39m\nInvalid char in the cubfile");
	if (i == -7)
		return ("\e[31mERROR\e[39m\nMore than one player was set on the map");
	if (i == -8)
		return ("\e[31mERROR\e[39m\nInvalid line");
	if (i == -9)
		return ("\e[31mERROR\e[39m\nInvalid map");
	if (i == -10)
		return ("\e[31mERROR\e[39m\nNo map was set in the cubfile");
	else
		return (error_messeges_continue(i));
}

int			ft_error(t_map *map, int i)
{
	free_map(map);
	ft_putendl_fd(error_messeges(i), STDOUT_FILENO);
	return (close_program());
}

int			ft_path_error(t_vars *vars)
{
	ft_error(vars->map, -17);
	mlx_destroy_window(vars->mlx, vars->win);
	return (close_program());
}

int			ft_arg_error(int i)
{
	ft_putendl_fd(error_messeges(i), STDOUT_FILENO);
	return (close_program());
}
