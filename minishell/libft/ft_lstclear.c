/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:56:23 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/11 09:56:34 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Clear linked list
// Deletes content for every node
// and frees the node
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*rmv;

	temp = *lst;
	while (temp != NULL)
	{
		rmv = temp;
		temp = temp->next;
		del(rmv->content);
		free(rmv);
	}
	*lst = temp;
}
