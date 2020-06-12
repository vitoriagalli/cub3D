/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:57:59 by vscabell          #+#    #+#             */
/*   Updated: 2020/01/31 14:46:42 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*to_free;

	to_free = *lst;
	if (!*lst || !lst || !del)
		return ;
	while (to_free)
	{
		*lst = to_free->next;
		del(to_free->content);
		free(to_free);
		to_free = *lst;
	}
	*lst = NULL;
}
