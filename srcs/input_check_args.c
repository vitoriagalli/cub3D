/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:30:01 by vscabell          #+#    #+#             */
/*   Updated: 2020/06/17 04:45:09 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_is_cub(char *str)
{
	size_t	i;

	i = ft_strlen(str) - 4;
	if (ft_memcmp(&str[i], ".cub", 4))
		return (0);
	return (1);
}

int				check_args(int argc, char **argv)
{
	if (argc == 1)
		return (ft_arg_error(-1));
	else if (argc > 3)
		return (ft_arg_error(-2));
	else if (!(ft_is_cub(argv[1])))
		return (ft_arg_error(-3));
	else if (argc == 3 && ft_memcmp(argv[2], "--save", 6))
		return (ft_arg_error(-4));
	return (0);
}
