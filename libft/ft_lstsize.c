/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:02:56 by vscabell          #+#    #+#             */
/*   Updated: 2020/01/29 16:05:56 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = lst;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
