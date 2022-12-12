/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:46:18 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/11 09:46:24 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Adds new node to back of linked list
// if linked list is empty 
// make new node the head of linked list
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (*lst != NULL)
	{
		temp = *lst;
		while (temp->next != NULL && temp != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
	else
		*lst = new;
}
