/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:18:25 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/11 21:26:49 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Create a new linked list
// and apply function f to each node of old linked list
// and use delete when necessary 
// (i dont know when & i dont know what it wants).
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	new_lst = NULL;
	temp = NULL;
	while (lst != NULL)
	{
		temp = ft_lstnew(f(lst->content));
		if (temp == NULL)
			return (NULL);
		ft_lstadd_back(&new_lst, temp);
		if (ft_lstlast(new_lst) == NULL)
			ft_lstclear(&new_lst, del);
		lst = lst->next;
	}
	return (new_lst);
}
