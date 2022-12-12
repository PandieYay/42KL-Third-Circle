/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:43:42 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/11 09:43:50 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Get last node of linked list
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	temp = NULL;
	while (lst != NULL)
	{
		temp = lst;
		lst = lst->next;
	}
	return (temp);
}
